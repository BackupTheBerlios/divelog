/******************************************************************************
* Filename : mainwidget.cpp                                                   *
* CVS Id 	 : $Id: MainWidget.cpp,v 1.9 2001/09/04 16:56:48 markus Exp $       *
* --------------------------------------------------------------------------- *
* Files subject    : Contains the main widget of the divelog, i.e. most of the*
*                    other Widgets                                            *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Sun Aug 12 2001                                          *
* Modified at      :                                                          *
* --------------------------------------------------------------------------- *
* To Do List : improve menu                                                   *
*              improve splitters                                              *
*              add Profile                                                    *
*              add Dive List                                                  *
*              add Multi puropse field                                        *
*              lots to come !                                                 *
* --------------------------------------------------------------------------- *
* Notes : mn_ = menu                                                          *
******************************************************************************/
static const char *mainwidget_cvs_id="$Id: MainWidget.cpp,v 1.9 2001/09/04 16:56:48 markus Exp $";

#include "mainwidget.h"
#include "profilefield.h"

#include <qapplication.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qmessagebox.h>
#include <qsplitter.h>
#include <qvbox.h>
#include <qscrollbar.h>

#include <qlabel.h>

#include <qpointarray.h>

#include "dive104.dat"

MainWidget::MainWidget( QWidget* parent=0, const char* name=0 )
    : QMainWindow( parent, name )
{
    QPointArray testdata;
    testdata.setPoints( 64, points );

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

    s1 = new QSplitter( QSplitter::Vertical, this , "s1" );
    s2 = new QSplitter( QSplitter::Horizontal, s1 , "s2" );

    l1 = new QLabel( "", s1 );    // DEBUG
    l2 = new QLabel( "", s2 );    // DEBUG

    profileBox = new QVBox( s2 ,"profileBox" );
    profile = new ProfileField( profileBox, "profile", testdata );

    /*
    || Set up Scrollbars
    */

    offsetBar  = new QScrollBar( QScrollBar::Horizontal, profileBox, "offsetBar" );
    samplesBar = new QScrollBar( QScrollBar::Horizontal, profileBox, "samplesBar" );

    samplesBar->setMinValue( 3 );
    samplesBar->setMaxValue( profile->samples() );
    samplesBar->setValue( profile->samples() );
    connect( samplesBar, SIGNAL( valueChanged( int ) ), profile, SLOT( setShowSamples( int ) ) );

    offsetBar->setMinValue( 0 );
    offsetBar->setMaxValue( profile->samples() - samplesBar->value() );

    l1->setText( "Depth="+QString::number( profile->depth() ) );       // DEBUG
    l2->setText( "Samples="+QString::number( profile->samples() ) );   // DEBUG

    setCentralWidget( s1 );

    // just to get rid of the warning: `const char * xxx_cvs_id' defined but not used
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

