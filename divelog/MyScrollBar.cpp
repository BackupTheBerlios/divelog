/******************************************************************************
* Filename : myscrollbar.cpp                                                  *
* CVS Id 	 : $Id: MyScrollBar.cpp,v 1.1 2001/09/08 09:26:03 markus Exp $                                                             *
* --------------------------------------------------------------------------- *
* Files subject    : Enhance the QScrollBar                                   *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Sat Sep 08 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List : Provide some given methods as slots                            *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
static const char *myscrollbar_cvs_id="$Id: MyScrollBar.cpp,v 1.1 2001/09/08 09:26:03 markus Exp $";

MyScrollBar::MyScrollBar( QWidget *parent, const char *name=0 )
    : QScrollBar( parent, name )
{
}

MyScrollBar::MyScrollBar( Orientation, QWidget *parent, const char *name=0 );
		: QScrollBar( Orientation, parent, const char *name=0 );
{
}

MyScrollBar::MyScrollBar( int minValue, int maxValue, int LineStep, int PageStep,
                 int value, Orientation,
                 QWidget *parent, const char *name=0 );
