#ifndef NEWDIVECOMPUTERFRM_H
#define NEWDIVECOMPUTERFRM_H
#include "newdivecomputerbasefrm.h"

class NewDiveComputerFrm : public NewDiveComputerBaseFrm
{ 
    Q_OBJECT

public:
    NewDiveComputerFrm( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~NewDiveComputerFrm();

protected slots:
    void showHelp();

};

#endif // NEWDIVECOMPUTERFRM_H
