#ifndef MAINWIDGET_H
#define MAINWIDGET_H
/******************************************************************************
* Filename : mainwidget.h                                                     *
* CVS Id 	 : $Id: MainWidget.h,v 1.6 2001/09/10 16:21:29 markus Exp $             *
* --------------------------------------------------------------------------- *
* Files subject    : Header for mainwidget.cpp                                *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Sun Aug 12 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes : Use #includes sparingly (see qt-tutorial) !                         *
******************************************************************************/

#include <qmainwindow.h>

class QMenuBar;
class QSplitter;
class QLabel;
class ProfileField;
class QVBox;
class MyScrollBar;

class MainWidget : public QMainWindow
{
    Q_OBJECT
public:
    MainWidget( QWidget* parent=0, const char* name=0 );

protected slots:
    /*
    ||  File Menu
    */
    void fileOpen();
    void fileNew();
    void fileSave();
    void fileClose();

    /*
    || Settings Menu
    */
    void settingsCommunication();

    /*
    || Help Menu
    */
    void about();

private:
    QMenuBar* main_mn;            // The main menu
    QSplitter* s1;
    QSplitter* s2;

    QLabel* l1;           // DEBUG Labels
    QLabel* l2;
    QLabel* l3;

    QVBox*  profileBox;
    ProfileField* profile;
    MyScrollBar*   samplesBar;
    MyScrollBar*   offsetBar;
};

#endif  // MAINWIDGET_H
