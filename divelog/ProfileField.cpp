/* Copyright (C) 2002 Markus Grunwald */
/* Copyright (C) 1995-2000 Trolltech AS.  All rights reserved. */
/* Copyright (C) 2000 MySQL AB & MySQL Finland AB & TCX DataKonsult AB */

/*************************************************************************
This file is part of divelog.

divelog is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

divelog is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with divelog; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**************************************************************************/

/******************************************************************************
* Filename : profilefield.cpp                                                 *
* CVS Id 	 : $Id: ProfileField.cpp,v 1.32 2002/09/30 19:02:25 grunwalm Exp $    *
* --------------------------------------------------------------------------- *
* Files subject    : Draw a graph with the dive-profile                       *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Tue Aug 14 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List : Show DC Warnings                                       				*
*              Make graph solid                                               *
*              Show area to-be-zoomed by mouse as solid rectangle             *
*              Handle Dive Profile in its own class                           *
* --------------------------------------------------------------------------- *
* Notes : maybe put timescale in member Variable (more speed!)                *
******************************************************************************/
static char profilefield_cvs_id[]="$Id: ProfileField.cpp,v 1.32 2002/09/30 19:02:25 grunwalm Exp $";

#include <qpainter.h>
#include <qpixmap.h>
#include <qpointarray.h>

#include <vector>
#include <math.h>

#include "DiveProfileVO.h"
#include "ProfileField.h"

// Some constants which set the appearance.
// FIXME: move to a better place...
#define TIME_TEXT "Time"
#define DEPTH_TEXT "Depth"

#define TICK_SIZE 5
#define TICK_DISTANCE_FACTOR 3    // adjust how close the ticks are to each other

#define RIGHT_MARGIN 10
#define BOTTOM_MARGIN 10

/*
|| Constructors
*/
ProfileField::ProfileField( QWidget *parent=0, const char* name=0 )
    : QWidget( parent, name )
// -------------------------------------------------
// Use : Standard constructor. Just calls base class
//       constructor and init() function
// Parameters: parent= parent of the widget
//             name  = name of the widget
// -------------------------------------------------
{
    init();
}

/*
ProfileField::ProfileField( QWidget *parent, const char* name, QPointArray profile )
    : QWidget( parent, name )
// -------------------------------------------------
// Use : Profile initiaizing constructor
// Parameters: parent= parent of the widget
//             name  = name of the widget
//             profile = profile data to show
//                       Use an extra class for this sometime!
// -------------------------------------------------
{
    init();
    setProfile( profile );
}
*/

ProfileField::ProfileField( QWidget *parent, const char* name, const DiveProfileVO& profile )
    : QWidget( parent, name )
// -------------------------------------------------
// Use : Profile initiaizing constructor
// Parameters: parent= parent of the widget
//             name  = name of the widget
//             profile = profile data to show
// -------------------------------------------------
{
    init();
    setProfile( profile );
}

void ProfileField::init()
// -------------------------------------------------
// Use : Main initializing method. Called by every
//       constructor
// -------------------------------------------------
{
    // Some sane(?) settings
    m_depth=21.4; 						// meters
    m_samples=64;
    m_secsPerSample=60;       // seconds/samples
                              // time for the whole dive can be calculated
                              // as m_samples*m_secsPerSample

    m_timeStart=0;            // start at the beginning
    m_showSamples=m_samples;  // and show all samples

    // we just changed something important, so tell it to Qt
    emit timeStartChanged( m_timeStart );
    emit showSamplesChanged( m_showSamples );

    // set up font and font metrics
    m_numberFont = QFont( "Courier", 10, QFont::Light );
    m_numberFont.setFixedPitch( true );
    m_numberFm = new QFontMetrics( m_numberFont );

    m_legendFont = QFont( "Helvetica", 12, QFont::Light );
    m_legendFm = new QFontMetrics( m_legendFont );

    m_timeFormat = Minutes;

    CHECK_PTR( m_numberFm );      // better check if all worked fine...
    CHECK_PTR( m_legendFm );

    // set up colors
    m_backgroundColor = QColor( 250, 250, 200 );
    m_gridPenColor		= lightGray;
    m_axesPenColor		= black;
    m_graphPenColor		= black;
    m_graphBrushColor	= blue;
    m_legendColor			= black;
    m_numberColor			= black;
    m_dragColor				= blue;

    setPalette( QPalette( m_backgroundColor ) ); // Background color
    setMinimumSize( minimumSize() );

    setMouseTracking( TRUE );        // emit signals on every
                                     // mouse move to show mouse data
    m_validMousePress=FALSE;         // No mouse click up to now (to handle
                                     // zooming via mouse drag )
    m_mousePressSample=0;            // no mouse-click -> no sample selected

    m_mouseSelectionRect.setWidth( 0 );       // the size of the draging rectangle
    m_mouseSelectionRect.setHeight( 0 );

    // Just to get rid of the warning: `const char * xxx_cvs_id' defined but not used
    profilefield_cvs_id[0]+=0;
}

/*
|| Slots
*/

void ProfileField::setProfile( const DiveProfileVO& diveProfile )
// -------------------------------------------------
// Use : Set all dive profile data
// Parameters  : diveProfile: dive profile class
// Side-Effects: called methods emit several signals
//               (see there)
//               calls paintEvent
// -------------------------------------------------
{
    // FIXME: the order of the following method calls
    //        is important, allthough it shouldn't.
    //        With the wrong order, the displayed length
    //        of the dive is wrong.

    qDebug( "ProfileField::setProfile    diveProfile.maxDepth()=%f", diveProfile.maxDepth() );
    
    setDepth( diveProfile.maxDepth() );
    setSamples( diveProfile.samples() );
    setHideSamples( 0, false );
    setSecsPerSample( diveProfile.secsPerSample() );
    setTimeStart( 0, false );

    m_profile=diveProfile.profile();
    repaint( FALSE );
}


void ProfileField::setDepth( float depth )
// -------------------------------------------------
// Use : Change the absolute depth shown in the
//       profile
// Parameters  : depth - the depth to set
// Side-Effects: sets m_depth
//               emits depthChanged
// -------------------------------------------------
{
    if ( depth == m_depth )
    {
        return;
    }

    m_depth=depth;
    emit depthChanged( depth );
}

void ProfileField::setSamples( int samples )
// -------------------------------------------------
// Use : Change the number of samples shown in the
//       profile
// Parameters  : samples - samples to set
// Side-Effects: sets m_samples
//               emits samplesChanged
// -------------------------------------------------
{
    if ( samples == m_samples )
    {
        return;
    }

    m_samples=samples;
    emit samplesChanged( samples );
}

void ProfileField::setSecsPerSample( int secsPerSample )
// -------------------------------------------------
// Use : Change the duration of one sample in seconds
// Parameters  : secsPerSample - duration of one sample
//                               in seconds
// Side-Effects: sets m_secsPerSample
//               emits secsPerSampleChanged
// -------------------------------------------------
{
    if ( secsPerSample == m_secsPerSample )
    {
        return;
    }

    m_secsPerSample=secsPerSample;
    emit secsPerSampleChanged( secsPerSample );
}

void ProfileField::setTimeFormat( TimeFormat timeFormat )
// -------------------------------------------------
// Use : Change the display format of times
// Parameters  : timeFormat - Format to be used,
//               eg. h:mm
// Side-Effects: sets m_timeFormat
//               emits timeFormatChanged
// -------------------------------------------------
{
    if ( timeFormat == m_timeFormat )
    {
        return;
    }

    m_timeFormat=timeFormat;
    emit timeFormatChanged( timeFormat );
}

/*
void ProfileField::setProfile( QPointArray profile )
// -------------------------------------------------
// Use : set the data to be displayed
// Parameters  : profile - the profile to be set
// Side-Effects: sets m_profile
//               calls paintEvent
// -------------------------------------------------
{
    m_profile=profile;
    repaint( FALSE );
}
*/

void ProfileField::setTimeStart( int start )
{
    setTimeStart( start, TRUE );
}

void ProfileField::setTimeStart( int start, bool doRepaint )
// -------------------------------------------------
// Use : set the start of displayed time (offset)
// Parameters  : start - the first displayed sample
// Side-Effects: sets m_timeStart
//               emits timeStartChanged
//               calls paintEvent
// -------------------------------------------------
{
    if ( start == m_timeStart )
    {
        return;
    }

    m_timeStart=start;
    emit timeStartChanged( start );
    //qDebug( "SIGNAL %s->timeStartChanged( %i )",this->name() ,start );

    if ( doRepaint )
    {
        repaint( FALSE );
    }
}

void ProfileField::setShowSamples( int showSamples )
{
    setShowSamples( showSamples , TRUE );
}

void ProfileField::setShowSamples( int showSamples, bool doRepaint )
// -------------------------------------------------
// Use : set number of samples to show, thus
//       indirectly set zooming.
//       see setHideSamples()
// Parameters  : showSamples - samples to show
//               doRepaint   - true : signal a repaint
//                                    after work is done
//                             false: dont.
// Side-Effects: sets m_showSamples
//               emits showSamplesChanged and
//                 hideSamplesChanged which correspond
//                 to each other
//               calls paintEvent (if doRepaint)
// -------------------------------------------------
{
    if ( showSamples == m_showSamples )
    {
        return;
    }

    m_showSamples=showSamples;

    emit showSamplesChanged( showSamples );
    //qDebug( "SIGNAL %s->showSamplesChanged( %i )",this->name(), showSamples );

    // the hidden samples are all samples minus the shown ones... doh!
    emit hideSamplesChanged( samples()-showSamples );
    //qDebug( "SIGNAL %s->hideSamplesChanged( %i )",this->name(), samples()-showSamples );

    if ( doRepaint )
    {
       repaint( FALSE );
    }
}

void ProfileField::setHideSamples( int hideSamples )
{
    setHideSamples( hideSamples, TRUE );
}

void ProfileField::setHideSamples( int hideSamples, bool doRepaint )
// -------------------------------------------------
// Use : set number of samples to hide, thus
//       indirectly set zooming.
//       see setShowSamples()
//       shown samples are all samples minus the hidden ones
// Parameters  : hideSamples - samples to hide
//               doRepaint   - true : signal a repaint
//                                    after work is done
//                             false: dont.
// Side-Effects: sets m_showSamples (!)
//               emits showSamplesChanged and
//                 hideSamplesChanged which correspond
//                 to each other
//               calls paintEvent
// -------------------------------------------------
{
    setShowSamples( samples()-hideSamples, doRepaint );
}

/*
|| other functions
*/

QSizePolicy ProfileField::sizePolicy() const
{
    // the profile may be shrunken and expanded
    return QSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Expanding );
}

QString ProfileField::sampleToTime( int sample )
// -------------------------------------------------
// Use : convert a sample number to its corresponding
//       time representation
// Parameters  : sample - sample number
// Returns     : a string with the time corresponding
//               to the sample
// -------------------------------------------------
{
    ASSERT( m_secsPerSample!=0 ); // this would mean trouble...

    int secs = sample * m_secsPerSample;

    QString timeString;
    QString hour,min,sec;

    int iMinutes = secs/60;  // round minutes to half a minute
    if ( secs%60 > 30 )      // = 30 seconds
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
// -------------------------------------------------
// Use : draw the profile
// Parameters  : p - the painter on which the profile
//                   will be painted
// -------------------------------------------------
{
    ASSERT( m_depth!=0 );            // Assure sane values
    /*ASSERT( m_samples!=0 );*/// DEBUG
    ASSERT( m_showSamples>=3 );

    CHECK_PTR( p );

    if ( !m_profile.isEmpty() )
    {
        float depth_scale=(float) m_depthAxisRect.height()/(10*m_depth);    // a little helper
        float time_scale =(float) m_timeAxisRect.width()/(m_showSamples-1); // dito

        p->save();

        // move the first sample to upper left corner of the coosy
        p->translate( m_origin.x()-timeStart()*time_scale, m_origin.y() );

        // scale the coosy to match the profile
        p->scale( time_scale, depth_scale );

        p->setPen( m_graphPenColor );
        p->setBrush( m_graphBrushColor );

        // now draw the profile (at last!)
        p->drawPolyline( m_profile, timeStart(), m_showSamples );

        p->restore();
    }
}


void ProfileField::drawCoosy( QPainter* p )
// -------------------------------------------------
// Use : draw the coordinate system (coosy)
//       this means arrows, ticks and some
//       background lines
// Parameters  : p - the painter to paint on
// -------------------------------------------------
{
    ASSERT( m_depth!=0 );        // assure sane values
/*    ASSERT( m_samples!=0 ); */// DEBUG
    ASSERT( m_showSamples>=3 );

    qDebug( "ProfileField::drawCoosy    m_depth=%f", m_depth );

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

    vector< float > anSaneTickDistances;
    anSaneTickDistances.push_back( 0.5 );
    anSaneTickDistances.push_back( 1.0 );
    anSaneTickDistances.push_back( 2.0 );
    anSaneTickDistances.push_back( 3.0 );
    anSaneTickDistances.push_back( 5.0 );
    anSaneTickDistances.push_back( 7.5 );

    /*
    || Draw Depth-Labels
    */

    //int   nTickNumber = 10; // FIXME: Adjust to size
    int   nTickNumber = m_depthAxisRect.height() / (3*m_numberFm->height());
    float fCrooctTickDistance = m_depth / (float)nTickNumber;
    int   nTickDistanceDigits = (int) log10( fCrooctTickDistance );

    qDebug( "nTickNumber         = %i", nTickNumber );
    qDebug( "fCrooctTickDistance = %f", fCrooctTickDistance );
    qDebug( "nTickDistanceDigits = %i", nTickDistanceDigits );
    
    int   nMinDistIndex=0;
    float fMinDistance=10000;
    for ( uint i=0; i<anSaneTickDistances.size(); i++  )
    {
        float dist=fabs( pow( 10, nTickDistanceDigits )*anSaneTickDistances[i] -
                         fCrooctTickDistance );
        if ( fMinDistance > dist  )
        {
            fMinDistance = dist;
            nMinDistIndex = i;
        }
    }

    float fTickDistance=anSaneTickDistances[ nMinDistIndex ] *
        pow( 10, nTickDistanceDigits );

    qDebug( "fTickDistance       = %f", fTickDistance );
    
    float tick_unit=fTickDistance;
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
    float time_scale=(float) m_timeAxisRect.width()/(m_showSamples-1);

    // one tick is each tick_unit
    tick_unit = (float)m_numberFm->width( sampleToTime( m_showSamples ) ) * TICK_DISTANCE_FACTOR / time_scale;
    ASSERT( tick_unit>0 );

    // Adjust tick_unit. If it is <1 then there are multiple tick marks with the
    // same value. This looks ugly so we set it to 1 in this case.
    tick_unit = ( tick_unit<1) ? 1 : tick_unit;

    // tick distance in screen-scale
    // We round "on demand" to get exact placement
    tick_distance_pixel = tick_unit*time_scale;

    for ( int i=0; qRound( i*tick_distance_pixel ) < m_timeAxisRect.width(); i++ )
    {
        // Time
        QString number= sampleToTime( qRound( timeStart()+i*tick_unit ) );
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
// -------------------------------------------------
// Use : draw everything. The region passed in the
//       QPaintEvent is ignored
// Parameters  : QPaintEvent - ignored
// -------------------------------------------------
{
    QRect    canvasSize=rect();
    QPixmap  pix( size() );          		    // Pixmap for double-buffering
    pix.fill( this, canvasSize.topLeft() ); // fill with widget background
    QPainter p( &pix );

    // DEBUG qDebug( "%s->paintEvent", this->name() );

    if ( !m_mouseSelectionRect.isNull() )    // draw the selection rectangle
    {
        p.setPen( m_dragColor );
        p.setBrush( m_dragColor );
        p.drawRect( m_mouseSelectionRect );
    }

    drawCoosy( &p );
    drawProfile( &p );

    p.end();

    bitBlt( this, canvasSize.topLeft(), &pix );
}

void ProfileField::resizeEvent( QResizeEvent* )
// -------------------------------------------------
// Use : recalculate values which depend on the
//       widgets size
// Parameters  : QResizeEvent - ignored. We use
//                 the widgets methods to get the
//                 new values
// Side-Effects: sets m_origin, m_timeAxisRect,
//                    m_depthAxisRect and
//                    m_graphRect
// -------------------------------------------------
{

    // Space above the time axis for the text
    int textHeight = qRound( m_legendFm->height()+m_numberFm->height() );
    // Space left of the depth axis for the text
    int textWidth  = qRound( m_legendFm->height()+m_numberFm->width( "999" ) );

    m_origin = QPoint( textWidth, textHeight );

    m_timeAxisRect  = QRect( m_origin.x(), 0, width()-m_origin.x()-RIGHT_MARGIN, textHeight+TICK_SIZE/2+1 );
    m_depthAxisRect = QRect( 0, m_origin.y(), m_origin.x()+TICK_SIZE/2+1, height()-m_origin.y()-BOTTOM_MARGIN );
    m_graphRect     = QRect( m_origin.x(),
                             m_origin.y(),
                             m_timeAxisRect.width(),
                             m_depthAxisRect.height()
                           );
}

void ProfileField::mouseMoveEvent( QMouseEvent* e )
// -------------------------------------------------
// Use : emit the data corresponding to the mouse
//       position
// Parameters  : e - contains the mouse position
// Side-Effects: changes m_mouseSelectionRect
//               emits mouseTimeChanged and
//                     mouseDepthChanged
//               needs mouseTracking to be TRUE
// -------------------------------------------------
{

    if ( !m_profile.isEmpty() )
    {
        if ( m_graphRect.contains( e->pos() ) )
        {                                       // the mouse is in the graph area
            QString depth;

            float time_scale=(float) m_timeAxisRect.width()/(m_showSamples-1);
            int sample=qRound( (e->x()-m_origin.x() )/time_scale )+timeStart();

            // convert depth to string
            depth=QString::number( m_profile.point( sample ).y()/10.0, 'f', 1 );

            if ( m_validMousePress )
            {
                // show the selection rectangle
                // while mouse is pressed
                if ( abs( sample-m_mousePressSample ) >=3 )
                {
                    // show only if the mouse has moved for at least
                    // three samples (otherwise, we treat it as click)
                    m_mouseSelectionRect.setRight( e->x() );
                    repaint( FALSE );

                }
            }

            emit mouseTimeChanged( sampleToTime( sample )  );
            emit mouseDepthChanged( depth.rightJustify( 4 ) );
        }
        else
        {   // clear the fields when the mouse is outside the graph area
            emit mouseTimeChanged( "" );
            emit mouseDepthChanged( "" );
        }
    }
}

void ProfileField::mousePressEvent( QMouseEvent* e )
// -------------------------------------------------
// Use : mark valid mouse-press and according mouse
//       position for zooming with mouse-dragging
// Parameters  : e - contains mouse position
// Side-Effects: sets m_mousePressSample
//                    m_mouseSelectionRect
//                    m_validMousePress
// -------------------------------------------------
{
    if ( m_graphRect.contains( e->pos() ) )
    {
        float time_scale=(float) m_timeAxisRect.width()/(m_showSamples-1);

        // mark mouse-position on press
        m_mousePressSample=qRound( (e->x()-m_origin.x() )/time_scale )+timeStart();

        // adjust selection rectangle
        m_mouseSelectionRect.setLeft( e->x() );
        m_mouseSelectionRect.setTop( m_timeAxisRect.bottom() );
        m_mouseSelectionRect.setBottom( m_depthAxisRect.bottom() );

        // the mouse press was valid, handle following releases.
        m_validMousePress=TRUE;
    }
    else
    {
        // the mouse-press was invalid, ignore following releases
        m_validMousePress=FALSE;
    }
}

void ProfileField::mouseReleaseEvent( QMouseEvent* e)
// -------------------------------------------------
// Use : calculate number of shown samples for zooming
// Parameters  : e - contains mouse position
// Side-Effects: sets m_validMousePress,
//                    m_mouseSelectionRect
//               emits setShowSamples,
//                     setTimeStart
// -------------------------------------------------
{
    //qDebug( "%s->mouseReleaseEvent", this->name() );

    // Selection Rectangle gets invalid on button release
    m_mouseSelectionRect.setWidth( 0 );
    m_mouseSelectionRect.setHeight( 0 );

    if ( m_graphRect.contains( e->pos() ) )
    {
        float time_scale=(float) m_timeAxisRect.width()/(m_showSamples-1);

        int mouseReleaseSample=qRound( (e->x()-m_origin.x() )/time_scale )+timeStart();
        int mouseDragSamples=abs( mouseReleaseSample-m_mousePressSample );
        int new_start=QMIN( m_mousePressSample, mouseReleaseSample );

        if ( mouseDragSamples>=3 )
        {
            // Zoom in if mouse dragged over more then two samples
            setShowSamples( mouseDragSamples, FALSE );
            setTimeStart( new_start );
        }
        else
        {   // Else tread as single click and zoom out full
            setShowSamples( samples(), FALSE );
            setTimeStart( 0 );
        }
    }
    m_validMousePress=FALSE;
}


QSize ProfileField::minimumSize() const
// calculate the smallest sane size
{
    QSize size( 6*m_legendFm->width( TIME_TEXT ),
                3*m_legendFm->width( DEPTH_TEXT ) );
    return size;
}

QSize ProfileField::sizeHint() const
{
    return minimumSize();
}
