/******************************************************************************
* Filename : mainwidget.cpp                                                   *
* CVS Id 	 : $Id: MainWidget.cpp,v 1.26 2001/10/24 05:53:19 markus Exp $      *
* --------------------------------------------------------------------------- *
* Files subject    : Contains the main widget of the divelog, i.e. most of the*
*                    other Widgets.                                           *
*                    Supplies application with menus etc.                     *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Sun Aug 12 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List : improve menu                                                   *
*              improve splitters                                              *
*              add Dive List                                                  *
*              add Multi puropse field                                        *
*              lots to come !                                                 *
* --------------------------------------------------------------------------- *
* Notes : mn_ = menu                                                          *
******************************************************************************/
static const char *mainwidget_cvs_id="$Id: MainWidget.cpp,v 1.26 2001/10/24 05:53:19 markus Exp $";

// own headers
#include "mainwidget.h"
#include "profilefield.h"
#include "myscrollbar.h"
#include "dive104.dat"
#include "newdiverfrm.h"

// Qt
#include <qapplication.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qmessagebox.h>
#include <qsplitter.h>
#include <qvbox.h>
#include <qhbox.h>
#include <qlabel.h>
#include <qpointarray.h>
#include <qabstractlayout.h>
#include <qfiledialog.h>
#include <qlistbox.h>
#include <qheader.h>

// others

#define MOUSE_TIME_LABEL "Time: "       // Label for time at mouse cursor.
#define MOUSE_DEPTH_LABEL "Depth: "     // Label for depth at mouse cursor.
                                        // FIXME: Move to a better place

MainWidget::MainWidget( QWidget* parent=0, const char* name=0 )
    : QMainWindow( parent, name )
// -------------------------------------------------
// Use : Constructor.
//       Set up of all contained widgets
//       and connection of SIGNALS and SLOTS
// Parameters  : parent = parent of this widget.
//                null means root window
//               name = name of the widget
// -------------------------------------------------
{
    /*
    || Set up a test dataset. This has to be removed when
    || reading of real data is working.
    */

    QPointArray testdata;
    testdata.setPoints( 64, points );

    //---------------------------------------------------

    /*
    || Build up the Menu
    */

    QPopupMenu *file_mn = new QPopupMenu( this );   // make a file menu
    CHECK_PTR( file_mn );                           // better check if it worked...
                                                
    // now add items to the menu
    file_mn->insertItem( "&Import",    this, SLOT( fileImport() ) );
    file_mn->insertItem( "&New Diver", this, SLOT( fileNewDiver() ) );
    file_mn->insertItem( "&Save", 	this, SLOT( fileSave() ), CTRL+Key_S );
    file_mn->insertItem( "&Close",	this, SLOT( fileClose()), CTRL+Key_W );
    file_mn->insertSeparator();
    file_mn->insertItem( "E&xit",  qApp, SLOT( quit() ), CTRL+Key_Q );

    // same as above (see file menu)
    QPopupMenu *settings_mn = new QPopupMenu( this );
    CHECK_PTR( settings_mn );

    settings_mn->insertItem( "&Communication", this, SLOT( settingsCommunication() ) );

    QPopupMenu *help_mn = new QPopupMenu( this );
    CHECK_PTR( help_mn );

    help_mn->insertItem( "&About", this, SLOT( about() ) );

    // Now create the main menu and insert the submenus
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
    m_diveListView= new QListView( m_s2, "m_diveListView" );

    /*
    || Set up Profile Area
    */

    m_profileBox = new QVBox( m_s2 ,"m_profileBox" );
    m_profile = new ProfileField( m_profileBox, "m_profile", testdata );

    /*
    || Set up Scrollbars
    */

    // The offset bar sets the start of the displayed area in the profile field.
    m_offsetBar  = new MyScrollBar( MyScrollBar::Horizontal, m_profileBox, "m_offsetBar" );
    // The samples bar sets the zoom-factor
    m_samplesBar = new MyScrollBar( MyScrollBar::Horizontal, m_profileBox, "m_samplesBar" );

    // Handling of the samples bar is a bit weired:
    // The value means 'hide that much values',
    // i.e. 0=show all values
    m_samplesBar->setMinValue( 0 );
    m_samplesBar->setMaxValue( m_profile->samples()-3 );
    m_samplesBar->setValue( 0 );

    m_offsetBar->setMinValue( 0 );
    m_offsetBar->setMaxValue( 0 );

    // Cross connect the samples bar value to the profile field
    connect( m_samplesBar, SIGNAL( valueChanged( int ) ), m_profile, SLOT( setHideSamples ( int ) ) );
    connect( m_profile   , SIGNAL( hideSamplesChanged( int ) ), m_samplesBar, SLOT( setValue( int ) ) );

    // the offset bar's maximum value depends on the zoom factor=value of samples bar
    connect( m_samplesBar, SIGNAL( valueChanged( int ) ), m_offsetBar, SLOT( setMaxValue( int ) ) );

    // Cross connect the offset bar value to the profile field.
    connect( m_offsetBar , SIGNAL( valueChanged( int ) ), m_profile, SLOT( setTimeStart( int ) ) );
    connect( m_profile   , SIGNAL( timeStartChanged( int ) ), m_offsetBar, SLOT( setValue( int ) ) );

    /*
    || Set up the mouse data fields
    || how can the layout be change to something not equally spaced or
    || at least some more space in the middle... ???
    */
    m_profileMouseDataBox    = new QHBox( m_profileBox, "m_profileMouseDataBox" );

    m_profileMouseTimeLabel  = new QLabel( MOUSE_TIME_LABEL,  m_profileMouseDataBox );
    m_profileMouseTime       = new QLabel( "1:10",  m_profileMouseDataBox );
    m_profileMouseDepthLabel = new QLabel( MOUSE_DEPTH_LABEL, m_profileMouseDataBox );
    m_profileMouseDepth      = new QLabel( "20.5", m_profileMouseDataBox );

    // This doesn't work. Why ?
    m_profileMouseDataSpacer = new QSpacerItem( m_profileMouseTimeLabel->frameRect().width(),
                                                m_profileMouseTimeLabel->frameRect().height(),
                                                QSizePolicy::Fixed,
                                                QSizePolicy::Fixed
                                              );

    connect( m_profile, SIGNAL( mouseTimeChanged( const QString& ) ), m_profileMouseTime, SLOT( setText( const QString & ) ) );
    connect( m_profile, SIGNAL( mouseDepthChanged( const QString& ) ), m_profileMouseDepth, SLOT( setText( const QString & ) ) );


    /*
    || Set up Tabbed Area
    */
    m_l1->setText( "Depth="+QString::number( m_profile->depth() ) );       // DEBUG

    /*
    || Set up List Area
    */
    m_diveListView->addColumn( "#" );
    m_diveListView->addColumn( "Date" );
    m_diveListView->addColumn( "Time" );

    m_diveListView->setColumnWidthMode( 0, QListView::Maximum );
    m_diveListView->setColumnWidthMode( 1, QListView::Maximum );
    m_diveListView->setColumnWidthMode( 2, QListView::Maximum );

    m_diveListView->setAllColumnsShowFocus( TRUE );

    setCentralWidget( m_s1 );


    // just to get rid of the warning: `const char * xxx_cvs_id' defined but not used
    mainwidget_cvs_id+=0;
}

/*
=================================================================
Slots
=================================================================
*/

/*
|| Menu-slots : implement the menu functions
*/

void MainWidget::fileImport()
{
    QString s( QFileDialog::getOpenFileName( QString::null, "Universal Dive Computer Format (*.UDCF)", this ) );
    if ( !s.isEmpty() )
    {
        qDebug( "Filename: %s", s.latin1() );
    }
}

void MainWidget::fileNewDiver()
{
    int result=0;
    m_newDiverFrm= new NewDiverFrm( 0, 0, TRUE );

    result=m_newDiverFrm->exec();
    qDebug( "NewDiverFrm->result=%d", result );
    if ( result )
    {
        qDebug( "First Name:\t%s", m_newDiverFrm->FirstName->text().latin1() );
        qDebug( "Last Name:\t%s",  m_newDiverFrm->LastName->text().latin1() );
        qDebug( "Brevet:\t%s", m_newDiverFrm->Brevet->text().latin1() );
        qDebug( "Street:\t%s", m_newDiverFrm->Street->text().latin1() );
        qDebug( "Zip:\t%s", m_newDiverFrm->Zip->text().latin1() );
        qDebug( "PLace:\t%s", m_newDiverFrm->Place->text().latin1() );
        qDebug( "Phone:\t%s", m_newDiverFrm->Phone->text().latin1() );
        qDebug( "EMail:\t%s", m_newDiverFrm->EMail->text().latin1() );
    }
    delete m_newDiverFrm;
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

