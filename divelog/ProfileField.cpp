/******************************************************************************
* Filename : profilefield.cpp                                                 *
* CVS Id 	 : $Id: ProfileField.cpp,v 1.12 2001/09/05 17:31:28 markus Exp $     *
* --------------------------------------------------------------------------- *
* Files subject    : Draw a graph with the dive-profile                       *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Tue Aug 14 2001                                          *
* Modified at      :                                                          *
* --------------------------------------------------------------------------- *
* To Do List : Zooming                                                        *
*							 Navigation                                             				*
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
static const char *mainwidget_cvs_id="$Id: ProfileField.cpp,v 1.12 2001/09/05 17:31:28 markus Exp $";

#include <qpainter.h>
#include <qpixmap.h>
#include <qpointarray.h>

#include "profilefield.h"

#define TIME_TEXT "Time"
#define DEPTH_TEXT "Depth"

#define TICK_SIZE 5
#define TICK_DISTANCE_FACTOR 3

#define RIGHT_MARGIN 10
#define BOTTOM_MARGIN 10

/*
|| Constructors
*/

ProfileField::ProfileField( QWidget *parent=0, const char* name=0 )
    : QWidget( parent, name )
{
    init();
}

ProfileField::ProfileField( QWidget *parent, const char* name, QPointArray profile )
    : QWidget( parent, name )
{
    init();
    setProfile( profile );
}

void ProfileField::init()
{
    // Some sane(?) settings
    m_depth=21.4; 			//meters
    m_samples=64;
    m_secsPerSample=60;

    m_timeStart=0;
    m_showSamples=m_samples;

    emit timeStartChanged( m_timeStart );
    emit showSamplesChanged( m_showSamples );

    m_numberFont = QFont( "Courier", 10, QFont::Light );
    m_numberFont.setFixedPitch( true );
    m_numberFm = new QFontMetrics( m_numberFont );

    m_legendFont = QFont( "Helvetica", 12, QFont::Light );
    m_legendFm = new QFontMetrics( m_legendFont );

    m_timeFormat = Minutes;

    CHECK_PTR( m_numberFm );
    CHECK_PTR( m_legendFm );

    m_backgroundColor = QColor( 250, 250, 200 );
    m_gridPenColor		= lightGray;
    m_axesPenColor		= black;
    m_graphPenColor		= black;
    m_graphBrushColor	= blue;
    m_legendColor			= black;
    m_numberColor			= black;

    setPalette( QPalette( m_backgroundColor ) ); // Background color
    setMinimumSize( minimumSize() );

    // Just to get rid of the warning: `const char * xxx_cvs_id' defined but not used
    mainwidget_cvs_id+=0;
}

/*
|| Slots
*/
void ProfileField::setDepth( float depth )
{
    if ( depth == m_depth )
    {
        return;
    }

    m_depth=depth;
    emit depthChanged( depth );
}

void ProfileField::setSamples( int samples )
{
    if ( samples == m_samples )
    {
        return;
    }

    m_samples=0;
    emit samplesChanged( samples );
}

void ProfileField::setSecsPerSample( int secsPerSample )
{
    if ( secsPerSample == m_secsPerSample )
    {
        return;
    }

    m_secsPerSample=secsPerSample;
    emit secsPerSampleChanged( secsPerSample );
}

void ProfileField::setTimeFormat( TimeFormat timeFormat )
{
    if ( timeFormat == m_timeFormat )
    {
        return;
    }

    m_timeFormat=timeFormat;
    emit timeFormatChanged( timeFormat );
}

void ProfileField::setProfile( QPointArray profile )
{
    m_profile=profile;
    repaint( FALSE );
}

void ProfileField::setTimeStart( int start )
{
    if ( start == m_timeStart )
    {
        return;
    }

    m_timeStart=start;
    emit timeStartChanged( start );
}

void ProfileField::setShowSamples( int showSamples )
{
    if ( showSamples == m_showSamples )
    {
        return;
    }

    m_showSamples=showSamples;
    emit timeStartChanged( showSamples );
    repaint( FALSE );
}

/*
|| other functions
*/

QSizePolicy ProfileField::sizePolicy() const
{
    return QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
}

QString ProfileField::sampleToTime( int sample )
{
    ASSERT( m_secsPerSample!=0 );

    int secs = sample * m_secsPerSample;

    QString timeString;
    QString hour,min,sec;

    int iMinutes = secs/60;
    if ( secs%60 > 30 )
    {
        iMinutes++;
    }

    int iHour = iMinutes/60;

    switch ( m_timeFormat )
    {
    case Minutes:
        min=QString::number( iMinutes );
        timeString=min.rightJustify( 2, '0' );
        break;
    case HourMinutes:
        hour=QString::number( iHour );
        min=QString::number(  iMinutes-iHour*60 );
        timeString=hour.rightJustify( 2, '0' )+":"+min.rightJustify( 2, '0' );
        break;
    default:
        // You shouldn't be here. Go away ;)
        qWarning( "Warning - unhandled time format in sampleToTime(): %d", m_timeFormat );
        qWarning( "          Substituting Minutes" );
        min=QString::number( iMinutes );
        timeString=min.rightJustify( 2, '0' );
    }

    return timeString;
}

void ProfileField::drawProfile( QPainter* p )
{
    ASSERT( m_depth!=0 );
    ASSERT( m_samples!=0 );
    ASSERT( m_showSamples>=3 );

    CHECK_PTR( p );
    ASSERT( !m_profile.isEmpty() );

    float depth_scale=(float) m_depthAxisRect.height()/(10*m_depth);   // a little helper
    float time_scale =(float) m_timeAxisRect.width()/(m_showSamples-1);    // dito

    qDebug( "time_scale=%f", time_scale );

    p->save();
    p->translate( m_origin.x(), m_origin.y() );
    p->scale( time_scale, depth_scale );
    p->setPen( m_graphPenColor );
    p->setBrush( m_graphBrushColor );
    p->drawPolyline( m_profile, 0, m_showSamples );
    p->restore();
}


void ProfileField::drawCoosy( QPainter* p )
{
    ASSERT( m_depth!=0 );
    ASSERT( m_samples!=0 );
    ASSERT( m_showSamples>=3 );

    float depth_scale=m_depthAxisRect.height()/m_depth;   // a little helper

    /*
    || Draw the Legend
    */

    p->setFont( m_legendFont );
    p->setPen( m_legendColor );

    p->drawText( m_timeAxisRect.x()
                +m_timeAxisRect.width()/2
                -m_legendFm->width( TIME_TEXT )/2,
                 m_legendFm->ascent(),
                 TIME_TEXT );

    // Rotate the coosy to draw vertical text

    p->save();                            	// save normal state

    p->translate( 0, rect().bottom() );   	// rotate about lower left corner
    p->rotate( -90 );

    p->drawText( m_depthAxisRect.height()/2      // draw the text
                -m_legendFm->width( DEPTH_TEXT )/2,
                 m_legendFm->ascent(),
                 DEPTH_TEXT );

    p->restore();                         	// restore normal state

    /*
    || Draw the axes
    */

    p->setPen( m_axesPenColor );
    p->drawLine( m_origin, QPoint( m_timeAxisRect.right(), m_origin.y() ) );
    p->drawLine( m_origin, QPoint( m_origin.x(), m_depthAxisRect.bottom() ) );


    /*
    || Draw Depth-Labels
    */

    // tick distance in "real-world-scale".
    // We round here to get sane labels like "5" in stead of "5.11"
    float   tick_unit = qRound( (float)m_numberFm->height() * TICK_DISTANCE_FACTOR / depth_scale );
    ASSERT( tick_unit>0 );

    // tick distance in screen-scale
    // We round "on demand" to get exact placement
    float tick_distance_pixel = tick_unit*depth_scale;

    p->setFont( m_numberFont );

    for ( int i=0; qRound( i*tick_distance_pixel ) < m_depthAxisRect.height(); i++ )
    {
        // Depth
        QString number = QString::number( i*tick_unit );
        p->setPen( m_numberColor );
        p->drawText( m_origin.x() - TICK_SIZE - m_numberFm->width( number ),
                     m_origin.y() + qRound( i*tick_distance_pixel ) +m_numberFm->height()/2 -1,
                     number );

        // Ticks
        p->setPen( m_axesPenColor );
        p->drawLine( m_origin.x() -TICK_SIZE,
                     m_origin.y() + qRound( i*tick_distance_pixel ),
                     m_origin.x() + 0,
                     m_origin.y() + qRound( i*tick_distance_pixel ) );

        // Grid
        if ( i!=0 )  // don't draw over the axes
        {
            p->setPen( m_gridPenColor );
            p->drawLine( m_origin.x() + 1,
                         m_origin.y() + qRound( i*tick_distance_pixel ),
                         m_origin.x() + m_timeAxisRect.width(),
                         m_origin.y() + qRound( i*tick_distance_pixel ) );
        }
    }

    /*
    || Draw Time-Labels ( quite as above... )
    */
    float time_scale=(float) m_timeAxisRect.width()/(m_showSamples-1);    // dito

    // one tick is each tick_unit
    tick_unit = (float)m_numberFm->width( sampleToTime( m_showSamples ) ) * TICK_DISTANCE_FACTOR / time_scale;
    qDebug( "m_showSamples\t=%i", m_showSamples );
    qDebug( "tick_unit\t=%f", tick_unit );
    ASSERT( tick_unit>0 );

    // tick distance in screen-scale
    // We round "on demand" to get exact placement
    tick_distance_pixel = tick_unit*time_scale;

    for ( int i=0; qRound( i*tick_distance_pixel ) < m_timeAxisRect.width(); i++ )
    {
        // Time
        QString number= sampleToTime( qRound( i*tick_unit ) );
        p->setPen( m_numberColor );
        p->drawText( m_origin.x() + qRound( i*tick_distance_pixel ) -m_numberFm->width( number )/2 -1,
                     m_origin.y() - TICK_SIZE,
                     number );

        // Ticks
        p->setPen( m_axesPenColor );
        p->drawLine( m_origin.x() + qRound( i*tick_distance_pixel ),
                     m_origin.y() - TICK_SIZE,
                     m_origin.x() + qRound( i*tick_distance_pixel ),
                     m_origin.y() + 0 );

        // Grid
        if ( i!=0 )  // don't draw over the axes
        {
            p->setPen( m_gridPenColor );
            p->drawLine( m_origin.x() + qRound( i*tick_distance_pixel ),
                         m_origin.y() + 1,
                         m_origin.x() + qRound( i*tick_distance_pixel ),
                         m_origin.y() + m_depthAxisRect.height() );
        }
    }
}

void ProfileField::paintEvent( QPaintEvent* )
{                                     
    QRect    canvasSize=rect();
    QPixmap  pix( size() );          		    // Pixmap for double-buffering
    pix.fill( this, canvasSize.topLeft() ); // fill with widget background
    QPainter p( &pix );

    drawCoosy( &p );
    drawProfile( &p );

    p.end();

    bitBlt( this, canvasSize.topLeft(), &pix );
}

void ProfileField::resizeEvent( QResizeEvent* )
{
    qDebug( "%s resized to %dx%d", name(), width(), height() );

    int textHeight = qRound( m_legendFm->height()+m_numberFm->height() );
    int textWidth  = qRound( m_legendFm->height()+m_numberFm->width( "999" ) );

    m_origin = QPoint( textWidth, textHeight );

    m_timeAxisRect  = QRect( m_origin.x(), 0, width()-m_origin.x()-RIGHT_MARGIN, textHeight+TICK_SIZE/2+1 );
    m_depthAxisRect = QRect( 0, m_origin.y(), m_origin.x()+TICK_SIZE/2+1, height()-m_origin.y()-BOTTOM_MARGIN );
}

QSize ProfileField::minimumSize() const
{
    QSize size( 6*m_legendFm->width( TIME_TEXT ),
                3*m_legendFm->width( DEPTH_TEXT ) );
    return size;
}

QSize ProfileField::sizeHint() const
{
    return minimumSize();
}
