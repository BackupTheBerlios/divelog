/******************************************************************************
* Filename : main.cpp                                                         *
* CVS Id 	 : $Id: main.cpp,v 1.3 2001/08/16 16:24:00 markus Exp $             *
* --------------------------------------------------------------------------- *
* Files subject    : Main class for divelog program (to be kept small)        *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Sun Aug 12 2001                                          *
* Modified at      :                                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes : Just generates a Main Widget                                        *
******************************************************************************/

#include <qapplication.h>
#include "mainwidget.h"

static const char *main_cvs_id="$Id: main.cpp,v 1.3 2001/08/16 16:24:00 markus Exp $";

int main( int argc, char* argv[] )
{
    QApplication a( argc, argv );

    MainWidget mw;
    mw.setGeometry( 1, 1, 800, 600 );
    mw.setMinimumSize( 800,600 );

    a.setMainWidget( &mw );
    mw.show();

    return a.exec();
}
