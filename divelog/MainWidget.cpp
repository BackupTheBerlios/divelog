/******************************************************************************
* Filename : mainwidget.cpp                                                   *
* CVS Id 	 : $Id: MainWidget.cpp,v 1.13 2001/09/11 17:34:31 markus Exp $       *
* --------------------------------------------------------------------------- *
* Files subject    : Contains the main widget of the divelog, i.e. most of the*
*                    other Widgets                                            *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Sun Aug 12 2001                                          *
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
static const char *mainwidget_cvs_id="$Id: MainWidget.cpp,v 1.13 2001/09/11 17:34:31 markus Exp $";

#include "mainwidget.h"
#include "profilefield.h"

#include <qapplication.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qmessagebox.h>
#include <qsplitter.h>
#include <qvbox.h>
#include <qlabel.h>
#include <qpointarray.h>

#include "dive104.dat"
#include "myscrollbar.h"

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

    m_main_mn = new QMenuBar( this );
    CHECK_PTR( m_main_mn );

    m_main_mn->insertItem( "&File", file_mn );
    m_main_mn->insertItem( "&Settings", settings_mn );
    m_main_mn->insertSeparator();
    m_main_mn->insertItem( "&Help", help_mn );
    m_main_mn->setSeparator( QMenuBar::InWindowsStyle );


    /*
    || Set up Splitters
    */

    m_s1 = new QSplitter( QSplitter::Vertical, this , "m_s1" );
    m_s2 = new QSplitter( QSplitter::Horizontal, m_s1 , "m_s2" );

    m_l1 = new QLabel( "", m_s1 );    // DEBUG
    m_l2 = new QLabel( "", m_s2 );    // DEBUG

    m_profileBox = new QVBox( m_s2 ,"m_profileBox" );
    m_profile = new ProfileField( m_profileBox, "m_profile", testdata );

    /*
    || Set up Scrollbars
    */

    m_offsetBar  = new MyScrollBar( MyScrollBar::Horizontal, m_profileBox, "m_offsetBar" );
    m_samplesBar = new MyScrollBar( MyScrollBar::Horizontal, m_profileBox, "m_samplesBar" );

    m_samplesBar->setMinValue( 3 );
    m_samplesBar->setMaxValue( m_profile->samples() );
    m_samplesBar->setFlip( TRUE );
    m_samplesBar->setValue( m_profile->samples() );

    m_offsetBar->setMinValue( 0 );
    m_offsetBar->setMaxValue( m_profile->samples() - m_samplesBar->value() );

    connect( m_samplesBar, SIGNAL( valueChanged( int ) ), m_profile, SLOT( setShowSamples( int ) ) );
    connect( m_profile   , SIGNAL( showSamplesChanged( int ) ), m_samplesBar, SLOT( setValue( int ) ) );

    connect( m_samplesBar, SIGNAL( valueChanged( int ) ), this, SLOT( adaptOffsetBar( int ) ) );
    connect( m_offsetBar , SIGNAL( valueChanged( int ) ), m_profile, SLOT( setTimeStart( int ) ) );

    m_l1->setText( "Depth="+QString::number( m_profile->depth() ) );       // DEBUG
    m_l2->setText( "Samples="+QString::number( m_profile->samples() ) );   // DEBUG

    setCentralWidget( m_s1 );

    // just to get rid of the warning: `const char * xxx_cvs_id' defined but not used
    mainwidget_cvs_id+=0;
}

/*
=================================================================
Slots
=================================================================
*/

void MainWidget::adaptOffsetBar( int v )
{
    m_offsetBar->setMaxValue( m_profile->samples()-v );
    if ( m_offsetBar->value() > m_offsetBar->maxValue() )
    {
        m_offsetBar->setValue( m_offsetBar->maxValue() );
    }
}

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

