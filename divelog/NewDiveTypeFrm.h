#ifndef NEWDIVETYPEFRM_H
#define NEWDIVETYPEFRM_H
#include "newdivetypebasefrm.h"

class NewDiveTypeFrm : public NewDiveTypeBaseFrm
{ 
    Q_OBJECT

public:
    NewDiveTypeFrm( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~NewDiveTypeFrm();

protected slots:
    void showHelp();

};

#endif // NEWDIVETYPEFRM_H
