/******************************************************************************
* Filename : newdiver.h                                                       *
* CVS Id   : $Id: NewDiverFrm.h,v 1.3 2001/11/08 08:35:18 markus Exp $                                                             *
* --------------------------------------------------------------------------- *
* Files subject    : Header file for newdiver.cpp                             *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Wed Oct 17 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
#ifndef NEWDIVERFRM_H
#define NEWDIVERFRM_H
#include "newdiverbasefrm.h"

class NewDiverFrm : public NewDiverBaseFrm
{ 
    Q_OBJECT

public:
    NewDiverFrm( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    NewDiverFrm( const QString& firstName , QWidget* parent = 0, const char* name = 0);

    ~NewDiverFrm();

protected slots:
    void showHelp();

private slots:
    void accept();

private:
    void init();
};

#endif // NEWDIVERFRM_H
