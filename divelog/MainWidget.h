#ifndef MAINWIDGET_H
#define MAINWIDGET_H
/******************************************************************************
* Filename : mainwidget.h                                                     *
* CVS Id 	 : $Id: MainWidget.h,v 1.10 2001/09/15 16:12:14 markus Exp $         *
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
class QHBox;
class QScrollBar;
class QSpacerItem;
class QString;

class MainWidget : public QMainWindow
{
    Q_OBJECT
public:
    MainWidget( QWidget* parent=0, const char* name=0 );

protected slots:

    /*
    || QScrollBar has no slots for setValue, setMaxValue
    || etc. So we create adapter slots in this class for
    || the scrollbars who need it.
    */
    void adaptSamplesBarToOffsetBar( int );
    void adaptSamplesBarToProfile( int );
/*
    void adaptProfileToOffsetBar( int );
    void adaptProfileToSamplesBar( int );
*/
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
    QMenuBar*  m_main_mn;            // The main menu
    QSplitter* m_s1;
    QSplitter* m_s2;

    QLabel* m_l1;           // DEBUG Labels
    QLabel* m_l2;
    QLabel* m_l3;

    QVBox*  			m_profileBox;
    ProfileField* m_profile;
    QScrollBar*   m_samplesBar;
    QScrollBar*   m_offsetBar;

    QHBox*				m_profileMouseDataBox;
    QLabel*				m_profileMouseTimeLabel;
    QLabel*				m_profileMouseDepthLabel;
    QLabel*				m_profileMouseTime;
    QLabel*				m_profileMouseDepth;
    QSpacerItem*  m_profileMouseDataSpacer;

};

#endif  // MAINWIDGET_H
