#ifndef PROFILEFIELD_H
#define PROFILEFIELD_H
/******************************************************************************
* Filename : profilefield.h                                                   *
* CVS Id 	 : $Id: ProfileField.h,v 1.2 2001/08/16 16:24:00 markus Exp $             *
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

class ProfileField : public QWidget
{
    Q_OBJECT
public:
    /*
    || Constructors
    */
    ProfileField( QWidget *parent=0, const char* name=0 );

    /*
    || Setting methots
    */

    /*
    || Access methods
    */
    float depth() const { return m_depth; }
    int   samples() const { return m_samples; }
    int   secsPerSample() const { return m_secsPerSample; }

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

signals:

    /*
    || Signals
    */

    void depthChanged( float );
    void samplesChanged( int );
    void secsPerSampleChanged( int );

protected:

    void paintEvent( QPaintEvent* );

private:

    void  init();          // General Object initialisation

    float m_depth;
    int   m_samples;       // Number of samples the computer made for this dive
    int   m_secsPerSample; // Number of seconds between two samples
};
#endif
