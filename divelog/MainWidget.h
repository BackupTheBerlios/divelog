#ifndef MAINWIDGET_H
#define MAINWIDGET_H
/******************************************************************************
* Filename : mainwidget.h                                                     *
* CVS Id 	 : $Id: MainWidget.h,v 1.16 2001/10/16 07:16:41 markus Exp $        *
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

// Forward define Classes used by this class.
// This avoids including header files and speeds
// up compiling (sometimes...)
class QMenuBar;
class QSplitter;
class QLabel;
class ProfileField;
class QVBox;
class QHBox;
class MyScrollBar;
class QSpacerItem;
class QString;
class QListView;

class MainWidget : public QMainWindow
{
    Q_OBJECT
public:
    MainWidget( QWidget* parent=0, const char* name=0 );

protected slots:

    /*
    ||  File Menu
    */
    void fileImport();
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
    QMenuBar*  m_main_mn;            // The main menu
    QSplitter* m_s1;                 // The vertical splitter
    QSplitter* m_s2;                 // The embedded horizontal splitter

    QLabel* m_l1;           // DEBUG Labels

    QVBox*  			m_profileBox;      // The vertical box for the profile area
    ProfileField* m_profile;         // The profile itself
    MyScrollBar*  m_samplesBar;      // Set the zoom factor for the profile
    MyScrollBar*  m_offsetBar;       // Set the offset for the profile

    QHBox*				m_profileMouseDataBox;    // the horizontal box for data
    																				// display at the mouse cursor
    QLabel*				m_profileMouseTimeLabel;  // Labels to show the data
    QLabel*				m_profileMouseDepthLabel;
    QLabel*				m_profileMouseTime;
    QLabel*				m_profileMouseDepth;

    QSpacerItem*  m_profileMouseDataSpacer; // a spacer which doesn't work :(

    QListView*     m_diveListView;

};

#endif  // MAINWIDGET_H
