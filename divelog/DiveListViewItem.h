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

#ifndef DIVELISTVIEWITEM_H
#define DIVELISTVIEWITEM_H
/******************************************************************************
* Filename : DiveListViewItem.h                                               *
* CVS Id 	 : $Id: DiveListViewItem.h,v 1.4 2002/06/02 09:55:13 grunwalm Exp $   *
* --------------------------------------------------------------------------- *
* Files subject    : Header for DiveListViewItem.cpp                          *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Mon Mar 25 2002                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes : Use #includes sparingly (see qt-tutorial) !                         *
******************************************************************************/

#include <qlistview.h>

class DiveListVO;

class DiveListViewItem : public QListViewItem
{

public:
    /*
    || Constructors
    */
    DiveListViewItem( DiveListVO& d, QListView *parent );

    QString key ( int column, bool ascending ) const;

    void init();

signals:

    /*
    || Signals
    */

    void clicked( DiveListViewItem * item );

};

#endif // DIVELISTVIEWITEM_H
