#ifndef PROFILEFIELD_H
#define PROFILEFIELD_H
/******************************************************************************
* Filename : profilefield.h                                                   *
* CVS Id 	 : $Id: ProfileField.h,v 1.7 2001/08/22 14:52:06 markus Exp $       *
* --------------------------------------------------------------------------- *
* Files subject    : Header for profilefield.cpp                              *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Tue Aug 14 2001                                          *
* Modified at      :                                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes : Use #includes sparingly (see qt-tutorial) !                         *
******************************************************************************/

#include <qwidget.h>
#include <qpointarray.h>

class ProfileField : public QWidget
{
    Q_OBJECT
public:
    /*
    || Constructors
    */
    ProfileField( QWidget *parent=0, const char* name=0 );

    enum  TimeFormat{ ms, MinSec=ms, hms, HourMinSec=hms };

    /*
    || Setting methots
    */

    /*
    || Access methods
    */
    float depth() const { return m_depth; }
    int   samples() const { return m_samples; }
    int   secsPerSample() const { return m_secsPerSample; }
    TimeFormat timeFormat() const { return m_timeFormat; }

		/*
		|| other functions
		*/
    QSizePolicy sizePolicy() const;

public slots:

    /*
    || Slots
    */
    void setDepth( float depth );
    void setSamples( int samples );
    void setSecsPerSample( int secsPerSample );
    void setProfile( QPointArray profile );
    void setTimeFormat( TimeFormat timeFormat );

signals:

    /*
    || Signals
    */

    void depthChanged( float );
    void samplesChanged( int );
    void secsPerSampleChanged( int );
    void timeFormatChanged( TimeFormat );

protected:

    void paintEvent( QPaintEvent* );
    void resizeEvent( QResizeEvent* );

private:

    void  init();          // General Object initialisation

    void 	drawCoosy( QPainter *p );
    void  drawProfile( QPainter *p );

    QString sampleToTime( int sample );

    float m_depth;         // Profile depth in meters
    int   m_samples;       // Number of samples the computer made for this dive
    int   m_secsPerSample; // Number of seconds between two samples

    TimeFormat m_timeFormat;

    QPoint m_origin;

    QRect m_timeAxisRect;
    QRect m_depthAxisRect;

    QFont m_numberFont;
    QFont m_legendFont;

    QColor m_backgroundColor;
    QColor m_gridPenColor;
    QColor m_axesPenColor;
    QColor m_graphPenColor;
    QColor m_graphBrushColor;
    QColor m_legendColor;
    QColor m_numberColor;


    QFontMetrics *m_numberFm;
    QFontMetrics *m_legendFm;

    QPointArray m_profile;
};

#endif
