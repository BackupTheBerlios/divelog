/******************************************************************************
* Filename : DiveListViewItem.cpp                                             *
* CVS Id 	 : $Id: DiveListViewItem.cpp,v 1.2 2002/03/26 10:41:21 markus Exp $*
* --------------------------------------------------------------------------- *
* Files subject    : Special List View Item for dives                         *
*                    - Sorting of number by number, not by string             *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Mon Mar 25 2002                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
static const char *DiveListViewItem_cvs_id="$Id: DiveListViewItem.cpp,v 1.2 2002/03/26 10:41:21 markus Exp $";

#include "DiveListViewItem.h"
#include "DiveListVO.h"

DiveListViewItem::DiveListViewItem( DiveListVO &d, QListView *parent )
		: QListViewItem( parent )
{
    QListViewItem::setText( 0, QString::number( d.number() ) );
    QListViewItem::setText( 1,  d.date().c_str() );
    QListViewItem::setText( 2,  d.time().c_str() );
}

QString DiveListViewItem::key ( int column, bool ascending ) const
{
    QString sort_key;
    switch ( column )
    {
    case 0:
        sort_key=QListViewItem::text( column ).rightJustify( 8, '0' );
        break;
    default:
        sort_key=QListViewItem::text( column );
        break;
    }

    return sort_key;
}
void DiveListViewItem::init()
{
    // Just to get rid of the warning: `const char * xxx_cvs_id' defined but not used
    DiveListViewItem_cvs_id+=0;
}

