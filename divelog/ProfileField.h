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

#ifndef PROFILEFIELD_H
#define PROFILEFIELD_H
/******************************************************************************
* Filename : profilefield.h                                                   *
* CVS Id 	 : $Id: ProfileField.h,v 1.21 2002/09/16 17:08:11 grunwalm Exp $      *
* --------------------------------------------------------------------------- *
* Files subject    : Header for profilefield.cpp                              *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Tue Aug 14 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes : Use #includes sparingly (see qt-tutorial) !                         *
******************************************************************************/

#include <qwidget.h>
#include <qpointarray.h>

class DiveProfileVO;

class ProfileField : public QWidget
{
    Q_OBJECT
public:
    /*
    || Constructors
    */
    ProfileField( QWidget *parent=0, const char* name=0 );
    //DEBUG: about to remove    ProfileField( QWidget *parent, const char* name, QPointArray profile );
    ProfileField( QWidget *parent, const char* name, const DiveProfileVO& profile );

    enum TimeFormat{ Minutes, HourMinutes };

    /*
    || Access methods
    */
    float depth() const { return m_depth; }
    int   samples() const { return m_samples; }
    int   secsPerSample() const { return m_secsPerSample; }
    TimeFormat timeFormat() const { return m_timeFormat; }
    int   timeStart() const { return m_timeStart; }
    int   showSamples() const { return m_showSamples; }
    int   hideSamples() const;

		/*
		|| other functions
		*/
    QSizePolicy sizePolicy() const;
    QSize minimumSize() const;
    QSize sizeHint() const;

public slots:

    /*
    || Slots
    */
    void setProfile( const DiveProfileVO& profile );

    void setDepth( float depth );
    void setSamples( int samples );
    void setSecsPerSample( int secsPerSample );
    // DEBUG: about to remove void setProfile( QPointArray profile );
    void setTimeFormat( TimeFormat timeFormat );

    void setTimeStart( int timeStart,     bool doRepaint );
    void setTimeStart( int timeStart );
    void setShowSamples( int showSamples, bool doRepaint );
    void setShowSamples( int showSamples );
    void setHideSamples( int hideSamples, bool doRepaint );
    void setHideSamples( int hideSamples );


signals:

    /*
    || Signals
    */

    void depthChanged( float );
    void samplesChanged( int );
    void secsPerSampleChanged( int );
    void timeFormatChanged( TimeFormat );
    void timeStartChanged( int );

    void showSamplesChanged( int );
    void hideSamplesChanged( int );

    void mouseTimeChanged( const QString& );
    void mouseDepthChanged( const QString& );

protected:

    void paintEvent( QPaintEvent* );
    void resizeEvent( QResizeEvent* );
    void mouseMoveEvent( QMouseEvent* e );
    void mousePressEvent( QMouseEvent* e );
    void mouseReleaseEvent( QMouseEvent* e);

private:

    void  init();          // General Object initialisation

    void 	drawCoosy( QPainter *p );
    void  drawProfile( QPainter *p );

    QString sampleToTime( int sample );

    // FIXME: exchange these three with one DiveProfileVO
    float m_depth;         // Profile depth in meters
    int   m_samples;       // Number of samples the computer made for this dive
    int   m_secsPerSample; // Number of seconds between two samples

    QPointArray m_profile;

    int   m_timeStart;     // start of displayed time (offset)
    int   m_showSamples;   // samples to show (for zooming)

    TimeFormat m_timeFormat;

    QPoint m_origin;

    QRect  m_timeAxisRect;
    QRect  m_depthAxisRect;
    QRect  m_graphRect;

    QFont  m_numberFont;
    QFont  m_legendFont;

    QColor m_backgroundColor;
    QColor m_gridPenColor;
    QColor m_axesPenColor;
    QColor m_graphPenColor;
    QColor m_graphBrushColor;
    QColor m_legendColor;
    QColor m_numberColor;
    QColor m_dragColor;

    QFontMetrics *m_numberFm;
    QFontMetrics *m_legendFm;

    bool m_validMousePress;
    int  m_mousePressSample;
    QRect m_mouseSelectionRect;
};

#endif // PROFILEFIELD_H
