/******************************************************************************
* Filename : profilefield.cpp                                                 *
* CVS Id 	 : $Id: ProfileField.cpp,v 1.5 2001/08/20 14:15:32 markus Exp $     *
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
static const char *mainwidget_cvs_id="$Id: ProfileField.cpp,v 1.5 2001/08/20 14:15:32 markus Exp $";

#include <qpainter.h>
#include <qpixmap.h>
#include "profilefield.h"

#define TIME_TEXT "Time"
#define DEPTH_TEXT "Depth"

#define TICK_SIZE 10
#define TICK_DISTANCE_FACTOR 3

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
    m_depth=40.0; 			//meters
    m_samples=180;      // 180 samples with
    m_secsPerSample=20; //  20 secs/Samples = 1 hour

    m_numberFont = QFont( "Courier", 10, QFont::Light );
    m_legendFont = QFont( "Helvetica", 12, QFont::Light );

    m_numberFm = new QFontMetrics( m_numberFont );
    m_legendFm = new QFontMetrics( m_legendFont );

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

/*
|| other functions
*/
QSizePolicy ProfileField::sizePolicy() const
{
    return QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
}

void ProfileField::drawCoosy( QPainter* p )
{
    ASSERT( m_depth!=0 );
    float depth_scale=m_depthAxisRect.height()/m_depth;   // a little helper

    /*
    || Draw the Labels
    */

    p->setFont( m_legendFont );
    p->drawText( m_timeAxisRect.x()
                +m_timeAxisRect.width()/2
                -m_legendFm->width( TIME_TEXT )/2,
                 m_legendFm->ascent()-1,
                 TIME_TEXT );

    // Rotate the coosy to draw vertical text

    p->save();                            // save normal state

    p->translate( 0, rect().bottom() );   // rotate about lower left corner
    p->rotate( -90 );

    p->drawText( m_depthAxisRect.height()/2      // draw the text
                -m_legendFm->width( DEPTH_TEXT )/2,
                 m_legendFm->ascent()-1,
                 DEPTH_TEXT );

    p->restore();                         // restore normal state

    /*
    || Draw the axes
    */
    p->drawLine( m_origin, QPoint( m_timeAxisRect.right(), m_origin.y() ) );
    p->drawLine( m_origin, QPoint( m_origin.x(), m_depthAxisRect.bottom() ) );

    // tick distance in "real-world-scale".
    // We round here to get sane labels like "5" in stead of "5.11"
    int   tick_distance_scaled = qRound( (float)m_numberFm->height() * TICK_DISTANCE_FACTOR / depth_scale );
    ASSERT( tick_distance_scaled>0 );

    // crap. have to draw labels and ticks seperate
    // since even fonts are scaled below :(

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
    }

    // scale and translate coosy to use real-world-scale
    p->save();

    p->translate( m_origin.x(), m_origin.y() );
    p->scale( 1, depth_scale );

    for ( int i=0; i<m_depth; i+=tick_distance_scaled )
    {
        p->drawLine( -TICK_SIZE/2, i, TICK_SIZE/2, i);
    }

    p->restore();
}

void ProfileField::paintEvent( QPaintEvent* )
{                                     
    QRect    canvasSize=rect();// QRect( 0, 0, width(), height() );
    QPixmap  pix( size() );          		    // Pixmap for double-buffering
    pix.fill( this, canvasSize.topLeft() ); // fill with widget background
    QPainter p( &pix );

#ifdef DEBUG
    p.drawRect( m_timeAxisRect );
//    p.drawRect( m_depthAxisRect );
#endif

    drawCoosy( &p );
/*    p.translate( m_origin.x(), m_origin.y() );
    p.scale( depth()  );
    																		// when drawing on pixmap
*/

    p.end();

    bitBlt( this, canvasSize.topLeft(), &pix );
}

void ProfileField::resizeEvent( QResizeEvent* )
{
    int textHeight = qRound( ( m_legendFm->height()+m_numberFm->height() )*1.1 );
    int textWidth  = qRound( ( m_legendFm->height()+m_numberFm->width( "99" ) )*1.1 );

    m_origin = QPoint( textWidth, textHeight );

    m_timeAxisRect  = QRect( m_origin.x(), 0, width()-m_origin.x(), textHeight+TICK_SIZE/2+1 );
    m_depthAxisRect = QRect( 0, m_origin.y(), m_origin.x()+TICK_SIZE/2+1, height()-m_origin.y() );
}
