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

/******************************************************************************
* Filename : DiveListViewItem.cpp                                             *
* CVS Id 	 : $Id: DiveListViewItem.cpp,v 1.5 2002/06/02 09:55:13 grunwalm Exp $*
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
static const char *DiveListViewItem_cvs_id="$Id: DiveListViewItem.cpp,v 1.5 2002/06/02 09:55:13 grunwalm Exp $";

#include "DiveListViewItem.h"
#include "DiveListVO.h"

DiveListViewItem::DiveListViewItem( DiveListVO &d, QListView *parent )
		: QListViewItem( parent )
{
    QListViewItem::setText( 0, QString::number( d.number() ) );
    QListViewItem::setText( 1,  d.date().c_str() );
    QListViewItem::setText( 2,  d.time().c_str() );
    QListViewItem::setText( 3,  d.place().c_str() );
}

QString DiveListViewItem::key ( int column, bool ascending ) const
{
    QString sort_key;
    switch ( column )
    {
    case 0:  // id
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

