/******************************************************************************
* Filename : mainwidget.cpp                                                   *
* CVS Id 	 : $Id: MainWidget.cpp,v 1.5 2001/08/20 14:18:02 markus Exp $       *
* --------------------------------------------------------------------------- *
* Files subject    : Contains the main widget of the divelog, i.e. most of the*
*                    other Widgets                                            *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Sun Aug 12 2001                                          *
* Modified at      :                                                          *
* --------------------------------------------------------------------------- *
* To Do List : improve mennu                                                  *
*              improve splitters                                              *
*              add Profile                                                    *
*              add Dive List                                                  *
*              add Multi puropse field                                        *
*              lots to come !                                                 *
* --------------------------------------------------------------------------- *
* Notes : mn_ = menu                                                          *
******************************************************************************/
static const char *mainwidget_cvs_id="$Id: MainWidget.cpp,v 1.5 2001/08/20 14:18:02 markus Exp $";

#include "mainwidget.h"
#include "profilefield.h"

#include <qapplication.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qmessagebox.h>
#include <qsplitter.h>

#include <qlabel.h>
// #include <qlayout.h>

MainWidget::MainWidget( QWidget* parent=0, const char* name=0 )
    : QMainWindow( parent, name )
{
    /*
    || Build up the Menu
    */

    QPopupMenu *file_mn = new QPopupMenu( this );
    CHECK_PTR( file_mn );
                                                
    file_mn->insertItem( "&Open", 	this, SLOT( fileOpen() ), CTRL+Key_O );
    file_mn->insertItem( "&New", 		this, SLOT( fileNew() ), CTRL+Key_N );
    file_mn->insertItem( "&Save", 	this, SLOT( fileSave() ), CTRL+Key_S );
    file_mn->insertItem( "&Close",	this, SLOT( fileClose()), CTRL+Key_W );
    file_mn->insertSeparator();
    file_mn->insertItem( "E&xit",  qApp, SLOT( quit() ), CTRL+Key_Q );

    QPopupMenu *settings_mn = new QPopupMenu( this );
    CHECK_PTR( settings_mn );

    settings_mn->insertItem( "&Communication", this, SLOT( settingsCommunication() ) );

    QPopupMenu *help_mn = new QPopupMenu( this );
    CHECK_PTR( help_mn );

    help_mn->insertItem( "&About", this, SLOT( about() ) );

    main_mn = new QMenuBar( this );
    CHECK_PTR( main_mn );

    main_mn->insertItem( "&File", file_mn );
    main_mn->insertItem( "&Settings", settings_mn );
    main_mn->insertSeparator();
    main_mn->insertItem( "&Help", help_mn );
    main_mn->setSeparator( QMenuBar::InWindowsStyle );


    /*
    || Set up Splitters
    */

    s1 = new QSplitter( QSplitter::Vertical, this );
    s2 = new QSplitter( QSplitter::Horizontal, s1 );

    l1 = new QLabel( "", s1 );    // DEBUG
    l2 = new QLabel( "", s2 );    // DEBUG

    profile = new ProfileField( s2, "profile field" );

    l1->setText( "Depth="+QString::number( profile->depth() ) );       // DEBUG
    l2->setText( "Samples="+QString::number( profile->samples() ) );   // DEBUG

    setCentralWidget( s1 );

    // just to get rid of the warning:
    mainwidget_cvs_id+=0;
}

/*
=================================================================
Slots
=================================================================
*/

void MainWidget::fileOpen()
{
    qWarning( "Not Implemented: MainWidget::fileOpen()");
}

void MainWidget::fileNew()
{
    qWarning( "Not Implemented: MainWidget::fileNew()");
}

void MainWidget::fileSave()
{
    qWarning( "Not Implemented: MainWidget::fileSave()");
}

void MainWidget::fileClose()
{
    qWarning( "Not Implemented: MainWidget::fileClose()");
}

void MainWidget::settingsCommunication()
{
    qWarning( "Not Implemented: MainWidget::settingsCommunication()");
}

void MainWidget::about()
{
    QMessageBox::about( this, "About","This is the Linux DiveLog" );
}

