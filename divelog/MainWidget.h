/* Copyright (C) 2002 Markus Grunwald */
/* Copyright (C) 1995-2000 Trolltech AS.  All rights reserved. */
/* Copyright (C) 2000 MySQL AB & MySQL Finland AB & TCX DataKonsult AB */

/*************************************************************************
This file is part of divelog.

divelog is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

divelog is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with divelog; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**************************************************************************/

#ifndef MAINWIDGET_H
#define MAINWIDGET_H
/******************************************************************************
* Filename : mainwidget.h                                                     *
* CVS Id 	 : $Id: MainWidget.h,v 1.28 2002/06/02 09:55:13 grunwalm Exp $        *
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
class NewDiverFrm;
class NewFillingStationFrm;
class NewDiveTypeFrm;
class NewDiveComputerFrm;
class InfoAreaFrm;
class DiveComputerVO;
class QListViewItem;

class MainWidget : public QMainWindow
{
    Q_OBJECT
public:
    MainWidget( QWidget* parent=0, const char* name=0 );

protected slots:

    /*
    ||  DataBase Menu
    */
    void dbLoadDiveList();
    void dbImport();
    void dbNewDiver();
    void dbNewFillingStation();
    void dbNewDiveType();
    void dbNewDiveComputer();
    void dbNewDiveComputer( const DiveComputerVO& diveComputer );

    /*
    || Settings Menu
    */
    void settingsCommunication();

    /*
    || Help Menu
    */
    void about();
    void aboutQt();
    void aboutLicense();

    /*
    || Entry in the ListView
    */
    void diveSelected( QListViewItem * item );

private:
    QMenuBar*  m_main_mn;            // The main menu
    QSplitter* m_s1;                 // The vertical splitter
    QSplitter* m_s2;                 // The embedded horizontal splitter

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

    QListView*    m_diveListView;

    NewFillingStationFrm*	m_newFillingStationFrm;
    NewDiveTypeFrm*				m_newDiveTypeFrm;
    InfoAreaFrm*  				m_infoArea;
};

#endif  // MAINWIDGET_H
