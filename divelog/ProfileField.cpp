/******************************************************************************
* Filename : profilefield.cpp                                                 *
* CVS Id 	 : $Id: ProfileField.cpp,v 1.3 2001/08/16 21:33:31 markus Exp $             *
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
static const char *mainwidget_cvs_id="$Id: ProfileField.cpp,v 1.3 2001/08/16 21:33:31 markus Exp $";

#include <qpainter.h>
#include <qpixmap.h>
#include "profilefield.h"

#define TIME_TEXT "Time"
#define DEPTH_TEXT "Depth"

#define TICK_SIZE 10

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
    // Some sane settings
    m_depth=40.0; 			//meters
    m_samples=180;      // 180 samples with
    m_secsPerSample=20; //  20 secs/Samples = 1 hour

    m_numberFont = QFont( "Courier", 10, QFont::Light );
    m_legendFont = QFont( "Helvetica", 12, QFont::Light );

    QFontMetrics numberFm( m_numberFont );
    QFontMetrics legendFm( m_legendFont );

    int textHeight = qRound( ( legendFm.height()+numberFm.height() )*1.1 );
    int textWidth  = qRound( ( legendFm.height()+numberFm.width( "99" ) )*1.1 );

    m_origin = QPoint( textWidth, textHeight );

    m_timeAxisRect  = QRect( m_origin.x(), 0, width()-m_origin.x(), textHeight+TICK_SIZE/2 );
    m_depthAxisRect = QRect( 0, m_origin.y(), m_origin.x()+TICK_SIZE/2, height()-m_origin.y() );

    setPalette( QPalette( QColor( 250, 250, 200 ) ) ); // Background color
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

void ProfileField::paintEvent( QPaintEvent* )
{                                     
    QRect    canvasSize=QRect( 0, 0, width(), height() );
    QPixmap  pix( size() );          		// Pixmap for double-buffering
    pix.fill( this, canvasSize.topLeft() ); // fill with widget background
    QPainter p( &pix );
    p.drawRect( m_timeAxisRect );
    p.drawRect( m_depthAxisRect );
/*    p.translate( m_origin.x(), m_origin.y() );
    p.scale( depth()  );
    																		// when drawing on pixmap
    drawCoosy( &p );
*/

    p.end();

    bitBlt( this, canvasSize.topLeft(), &pix );

}


