#ifndef NEWFILLINGSTATIONFRM_H
#define NEWFILLINGSTATIONFRM_H
#include "newfillingstationbasefrm.h"

class NewFillingStationFrm : public NewFillingStationBaseFrm
{ 
    Q_OBJECT

public:
    NewFillingStationFrm( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~NewFillingStationFrm();

protected slots:
    void showHelp();

};

#endif // NEWFILLINGSTATIONFRM_H
