/******************************************************************************
* Filename : mainwidget.cpp                                                   *
* CVS Id 	 : $Id: MainWidget.cpp,v 1.23 2001/10/05 17:48:39 markus Exp $      *
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
static const char *mainwidget_cvs_id="$Id: MainWidget.cpp,v 1.23 2001/10/05 17:48:39 markus Exp $";

#include "mainwidget.h"
#include "profilefield.h"

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
#include "myscrollbar.h"
#include "dive104.dat"

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
    file_mn->insertItem( "&Open", 	this, SLOT( fileOpen() ), CTRL+Key_O );
    file_mn->insertItem( "&New", 		this, SLOT( fileNew() ), CTRL+Key_N );
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

void MainWidget::fileOpen()
{
    QString s( QFileDialog::getOpenFileName( QString::null, "Universal Dive Computer Format (*.profile)", this ) );
    if ( !s.isEmpty() )
    {
        qDebug( "Filename: %s", s.latin1() );

        m_udcfData=UDCFReadFile( (char*) s.latin1() );
        CHECK_PTR( m_udcfData );

        qDebug( "Version:\t%ld", m_udcfData->version );
        qDebug( "Vendor:\t%s", m_udcfData->vendor );
        qDebug( "Model:\t%s", m_udcfData->model );
        qDebug( "Driver Version:\t%ld", m_udcfData->driverVersion );
        qDebug( "Personal Info:\t%s", m_udcfData->personalInfo );
        qDebug( "Total Dives:\t%ld", m_udcfData->totalDives );
        qDebug( "Serial ID:\t%s", m_udcfData->serialID );
        qDebug( "Group Size:\t%ld", m_udcfData->groupSize );
        qDebug( "Group Index:\t%ld", m_udcfData->groupIndex );

        m_udcfGroup = m_udcfData->groupList;
        int count=0;

        m_diveListView->clear();

        for ( int group=0; group<=m_udcfData->groupIndex; group++)
        {
            for ( int dive=0; dive<=m_udcfGroup[group].diveIndex; dive++ )
            {
                qDebug( "Group[%d].diveList[%d] %02d.%02d.%04d %02d:%02d",
                        group, dive,
                        m_udcfGroup[group].diveList[dive].day,
                        m_udcfGroup[group].diveList[dive].month,
                        m_udcfGroup[group].diveList[dive].year,
                        m_udcfGroup[group].diveList[dive].hour,
                        m_udcfGroup[group].diveList[dive].minute );

                count++;

                QString number;
                QString date;
                QString time;

                number.sprintf( "%03d", count );
                date.sprintf( "%02d.%02d.%04d", m_udcfGroup[group].diveList[dive].day, m_udcfGroup[group].diveList[dive].month, m_udcfGroup[group].diveList[dive].year );
                time.sprintf( "%02d:%02d", m_udcfGroup[group].diveList[dive].hour, m_udcfGroup[group].diveList[dive].minute );

                (void) new QListViewItem( m_diveListView, number, date, time );
            }
        }
        UDCFFree( m_udcfData );
    }
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

