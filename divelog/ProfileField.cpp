/******************************************************************************
* Filename : profilefield.cpp                                                 *
* CVS Id 	 : $Id: ProfileField.cpp,v 1.6 2001/08/20 20:10:40 markus Exp $     *
* --------------------------------------------------------------------------- *
* Files subject    : Draw a graph with the dive-profile                       *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Tue Aug 14 2001                                          *
* Modified at      :                                                          *
* --------------------------------------------------------------------------- *
* To Do List : Coordinate system                                              *
*              Graph                                                          *
*              Resizing,Zooming,Navigation                                    *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
static const char *mainwidget_cvs_id="$Id: ProfileField.cpp,v 1.6 2001/08/20 20:10:40 markus Exp $";

#include <qpainter.h>
#include <qpixmap.h>
#include "profilefield.h"

#define TIME_TEXT "Time"
#define DEPTH_TEXT "Depth"

#define TICK_SIZE 10
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

void ProfileField::init()
{
    // Some sane(?) settings
    m_depth=21.4; 			//meters
    m_samples=64;
    m_secsPerSample=60;

    m_numberFont = QFont( "Courier", 10, QFont::Light );
    m_numberFont.setFixedPitch( true );
    m_legendFont = QFont( "Helvetica", 12, QFont::Light );

    m_numberFm = new QFontMetrics( m_numberFont );
    m_legendFm = new QFontMetrics( m_legendFont );

    m_timeFormat = MinSec;

    CHECK_PTR( m_numberFm );
    CHECK_PTR( m_legendFm );

    setPalette( QPalette( QColor( 250, 250, 200 ) ) ); // Background color

    // Just to get rid of the warning:
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

    QString timeString;
    QString hour,min,sec;

    int iHour;
    int secs = sample * m_secsPerSample;

    switch ( m_timeFormat )
    {
    case MinSec:
        min=QString::number( secs/60 );
        sec=QString::number( secs%60 );
        timeString=min.rightJustify( 2, '0' )+":"+sec.rightJustify( 2, '0');
        break;
    case HourMinSec:
        iHour=secs/(3600);
        hour=QString::number( iHour );
        secs-=iHour*3600;
        min=QString::number( secs/60 );
        sec=QString::number( secs%60 );
        timeString=hour.rightJustify( 2, '0' )+":"+min.rightJustify( 2, '0' )+":"+sec.rightJustify( 2, '0' );
        break;
    default:
        // You shouldn't be here. Go away ;)
        qWarning( "Warning - unhandled time format in sampleToString(): %d", m_timeFormat );
        qWarning( "          Substituting mm:ss" );
        min=QString::number( secs/60 );
        sec=QString::number( secs%60 );
        timeString=min.rightJustify( 2, '0' )+":"+sec.rightJustify( 2, '0' );
    }

    return timeString;
}

void ProfileField::drawProfile( QPainter* p )
{
    ASSERT( m_depth!=0 );
    ASSERT( m_samples!=0 );
    ASSERT( !m_profile.isEmpty() );

    float depth_scale=m_depthAxisRect.height()/(10*m_depth);   // a little helper
    float time_scale=m_timeAxisRect.width()/m_samples;    // dito

    p->save();
    p->translate( m_origin.x(), m_origin.y() );
    p->scale( time_scale, depth_scale );
    p->setBrush( QBrush( blue ) );
    p->drawPolygon( m_profile );
    p->restore();
}


void ProfileField::drawCoosy( QPainter* p )
{   // FIXME : get fontMetrics from Painer !
    ASSERT( m_depth!=0 );
    ASSERT( m_samples!=0 );

    float depth_scale=m_depthAxisRect.height()/m_depth;   // a little helper
    float time_scale=m_timeAxisRect.width()/m_samples;    // dito

    /*
    || Draw the Labels
    */

    p->setFont( m_legendFont );
    p->drawText( m_timeAxisRect.x()
                +m_timeAxisRect.width()/2
                -m_legendFm->width( TIME_TEXT )/2,
                 m_legendFm->ascent(),
                 TIME_TEXT );

    // Rotate the coosy to draw vertical text

    p->save();                            // save normal state

    p->translate( 0, rect().bottom() );   // rotate about lower left corner
    p->rotate( -90 );

    p->drawText( m_depthAxisRect.height()/2      // draw the text
                -m_legendFm->width( DEPTH_TEXT )/2,
                 m_legendFm->ascent(),
                 DEPTH_TEXT );

    p->restore();                         // restore normal state

    /*
    || Draw the axes
    */
    p->drawLine( m_origin, QPoint( m_timeAxisRect.right(), m_origin.y() ) );
    p->drawLine( m_origin, QPoint( m_origin.x(), m_depthAxisRect.bottom() ) );


    /*
    || Draw Depth-Labels
    */

    // tick distance in "real-world-scale".
    // We round here to get sane labels like "5" in stead of "5.11"
    int   tick_distance_scaled = qRound( (float)m_numberFm->height() * TICK_DISTANCE_FACTOR / depth_scale );
    ASSERT( tick_distance_scaled>0 );

    // tick distance in screen-scale
    // We round "on demand" to get exact placement
    float tick_distance_pixel = tick_distance_scaled*depth_scale;

    p->setFont( m_numberFont );

    for ( int i=0; qRound( i*tick_distance_pixel ) < m_depthAxisRect.height(); i++ )
    {
        QString number = QString::number( i*tick_distance_scaled );
        p->drawText( m_origin.x() - TICK_SIZE/2 - m_numberFm->width( number ),
                     m_origin.y() + qRound( i*tick_distance_pixel ) +m_numberFm->height()/2 -1,
                     number );
        p->drawLine( m_origin.x() -TICK_SIZE/2,
                     m_origin.y() + qRound( i*tick_distance_pixel ),
                     m_origin.x() +TICK_SIZE/2,
                     m_origin.y() + qRound( i*tick_distance_pixel ) );
    }

    /*
    || Draw Time-Labels ( quite as above... )
    */

    // tick distance in "real-world-scale".
    // We round here to get sane labels like "5" in stead of "5.11"

    tick_distance_scaled = qRound( (float)m_numberFm->width( sampleToTime( m_samples ) ) * TICK_DISTANCE_FACTOR / time_scale );
    ASSERT( tick_distance_scaled>0 );

    // tick distance in screen-scale
    // We round "on demand" to get exact placement
    tick_distance_pixel = tick_distance_scaled*time_scale;

    for ( int i=0; qRound( i*tick_distance_pixel ) < m_timeAxisRect.width(); i++ )
    {
        QString number= sampleToTime( i*tick_distance_scaled );

        p->drawText( m_origin.x() + qRound( i*tick_distance_pixel ) -m_numberFm->width( number )/2 -1,
                     m_origin.y() - TICK_SIZE/2,
                     number );
        p->drawLine( m_origin.x() + qRound( i*tick_distance_pixel ),
                     m_origin.y() + -TICK_SIZE/2,
                     m_origin.x() + qRound( i*tick_distance_pixel ),
                     m_origin.y() + TICK_SIZE/2 );
    }
}

void ProfileField::paintEvent( QPaintEvent* )
{                                     
    QRect    canvasSize=rect();// QRect( 0, 0, width(), height() );
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

