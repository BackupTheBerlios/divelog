#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include "MainWidgetBaseFrm.h"

class MainWidget : public MainWidgetBaseFrm
{ 
    Q_OBJECT

public:
    MainWidget( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~MainWidget();

public slots:
    void helpIndex();
    void helpContents();
    void helpAbout();
    void dbImport();

protected slots:
    void dbLoadDiveList();
    void dbNewDiveComputer( const DiveComputerVO & diveComputer );
    void dbNewDiveComputer();
    void dbNewDiveType();
    void dbNewDiver();
    void dbNewFillingStation();
    void helpAboutQt();
    void settingCommunication();
    void helpAboutLicense();
    void diveSelected( QListViewItem * item );

};

#endif // MAINWIDGET_H
