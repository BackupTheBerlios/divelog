#ifndef NEWFILLINGSTATIONFRM_H
#define NEWFILLINGSTATIONFRM_H
#include "NewFillingStationBaseFrm.h"

class NewFillingStationFrm : public NewFillingStationBaseFrm
{ 
    Q_OBJECT

public:
    NewFillingStationFrm( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    NewFillingStationFrm( const QString& stationName , QWidget* parent = 0, const char* name = 0);
    ~NewFillingStationFrm();

protected slots:
    void showHelp();

private slots:
    void accept();

private:
    void init();
};

#endif // NEWFILLINGSTATIONFRM_H
