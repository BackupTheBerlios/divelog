#ifndef INFOAREAFRM_H
#define INFOAREAFRM_H
#include "infoareabasefrm.h"

class InfoAreaFrm : public InfoAreaBaseFrm
{ 
    Q_OBJECT

public:
    InfoAreaFrm( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~InfoAreaFrm();

private:
    void init();

};

#endif // INFOAREAFRM_H
