#ifndef MYSCROLLBAR_H
#define MYSCROLLBAR_H
/******************************************************************************
* Filename : myscrollbar.h                                                    *
* CVS Id 	 : $Id: MyScrollBar.h,v 1.6 2001/09/23 12:36:49 markus Exp $                                                             *
* --------------------------------------------------------------------------- *
* Files subject    : Header for myscrollbar.cpp                               *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Sat Sep 08 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes : Use #includes sparingly (see qt-tutorial) !                         *
******************************************************************************/

#include <qscrollbar.h>

class MyScrollBar : public QScrollBar
{
    Q_OBJECT
public:
    /*
    || Constructors
    */
    MyScrollBar( QWidget *parent, const char *name=0 );
    MyScrollBar( Orientation, QWidget *parent, const char *name=0 );
    MyScrollBar( int minValue, int maxValue, int LineStep, int PageStep,
                 int value, Orientation,
                 QWidget *parent, const char *name=0 );

public slots:

    void setValue( int );
    void setMinValue( int );
    void setMaxValue( int );

private:
    void init();
};

#endif // MYSCROLLBAR_H
