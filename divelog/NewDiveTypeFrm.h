#ifndef NEWDIVETYPEFRM_H
#define NEWDIVETYPEFRM_H
#include "newdivetypebasefrm.h"

class NewDiveTypeFrm : public NewDiveTypeBaseFrm
{ 
    Q_OBJECT

public:
    NewDiveTypeFrm( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    NewDiveTypeFrm( const QString& diveType, QWidget* parent = 0, const char* name = 0);
    ~NewDiveTypeFrm();

protected slots:
    void showHelp();

private slots:
    void accept();

private:
    void init();
};

#endif // NEWDIVETYPEFRM_H
