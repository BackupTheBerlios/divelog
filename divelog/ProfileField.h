#ifndef PROFILEFIELD_H
#define PROFILEFIELD_H
/******************************************************************************
* Filename : profilefield.h                                                   *
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

    ProfileField( QWidget *parent=0, const char* name=0 );

    QSizePolicy sizePolicy() const;

    float depth() const { return m_depth };
    int   samples() const { return m_samples };              // Number of samples the computer made for this dive
    int   secsPerSample() const { return m_secsPerSample };  // Number of seconds between two samples

public slots:

    void setDepth( float depth );
    void setSamples( int samples );
    void setSecsPerSample( int secsPerSample );

private:

    float m_depth;
    int   m_samples;
    int   secsPerSample
#endif
