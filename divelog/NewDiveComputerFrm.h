#ifndef NEWDIVECOMPUTERFRM_H
#define NEWDIVECOMPUTERFRM_H
#include "newdivecomputerbasefrm.h"

class NewDiveComputerFrm : public NewDiveComputerBaseFrm
{ 
    Q_OBJECT

public:
    NewDiveComputerFrm( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    NewDiveComputerFrm( const QString& serialNumber,
                        const QString& computerName=0,
                        QWidget* parent = 0, const char* name = 0);
    ~NewDiveComputerFrm();

protected slots:
    void showHelp();

private slots:
    void accept();

private:
    void init();

};

#endif // NEWDIVECOMPUTERFRM_H
