#ifndef DIVELISTVIEWITEM_H
#define DIVELISTVIEWITEM_H
/******************************************************************************
* Filename : DiveListViewItem.h                                               *
* CVS Id 	 : $Id: DiveListViewItem.h,v 1.1 2002/03/25 15:26:21 markus Exp $   *
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

};

#endif // DIVELISTVIEWITEM_H
