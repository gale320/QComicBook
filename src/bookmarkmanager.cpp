/*
 * This file is a part of QComicBook.
 *
 * Copyright (C) 2005 Pawel Stolowski <yogin@linux.bydg.org>
 *
 * QComicBook is free software; you can redestribute it and/or modify it
 * under terms of GNU General Public License by Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY. See GPL for more details.
 */

#include "bookmarkmanager.h"
#include "bookmarks.h"
#include <qlistview.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qmessagebox.h>

BookmarkManager::BookmarkManager(QWidget *parent, Bookmarks *b): QDialog(parent), bookmarks(b)/*{{{*/
{
	QVBoxLayout *box0 = new QVBoxLayout(this, 5, 5);
	lview = new QListView(this);
	lview->addColumn(tr("Name"));
	lview->addColumn(tr("Page"));
	lview->setSelectionMode(QListView::Multi);
	box0->addWidget(lview);
	
	QHBoxLayout *box1 = new QHBoxLayout(NULL, 0, 5);

	QPushButton *b_selall = new QPushButton(tr("Select all"), this);
	box1->addWidget(b_selall);
	box1->addStretch();
	
	QPushButton *b_selrev = new QPushButton(tr("Invert selection"), this);
	box1->addWidget(b_selrev);
	box1->addStretch(0);
		
	b_selinv = new QPushButton(tr("Select invalid"), this);
	box1->addWidget(b_selinv);
	box1->addStretch();
	
	QPushButton *b_selnone = new QPushButton(tr("Clear selection"), this);
	box1->addWidget(b_selnone);
	box1->addStretch(1);
	
	QPushButton *b_remsel = new QPushButton(tr("Remove selected"), this);
	box1->addWidget(b_remsel);
	box1->addStretch();

	QPushButton *b_ok = new QPushButton(tr("Close"), this);
	box1->addWidget(b_ok);
	box0->addLayout(box1);

	initBookmarkView();

	connect(b_remsel, SIGNAL(clicked()), this, SLOT(removeSelected()));
	connect(b_selinv, SIGNAL(clicked()), this, SLOT(selectInvalid()));
	connect(b_selall, SIGNAL(clicked()), this, SLOT(selectAll()));
	connect(b_selnone, SIGNAL(clicked()), this, SLOT(selectNone()));
	connect(b_selrev, SIGNAL(clicked()), lview, SLOT(invertSelection()));
	connect(b_ok, SIGNAL(clicked()), this, SLOT(close()));
}/*}}}*/

BookmarkManager::~BookmarkManager()/*{{{*/
{
}/*}}}*/

void BookmarkManager::initBookmarkView()/*{{{*/
{
	lview->clear();
	invalid.clear();
	QValueList<Bookmark> blist = bookmarks->get();
	for (QValueList<Bookmark>::iterator it = blist.begin(); it != blist.end(); it++)
	{
		QListViewItem *item = new QListViewItem(lview);
		item->setText(0, (*it).getName());
		item->setText(1, QString::number((*it).getPage() + 1));

		if (!(*it).isValid())
			invalid.append(item);
	}

	if (invalid.count() == 0)
		b_selinv->setDisabled(true);
}/*}}}*/

void BookmarkManager::removeSelected()/*{{{*/
{
	QPtrList<QListViewItem> todel;
	for (QListViewItemIterator it(lview, QListViewItemIterator::Selected); it.current(); ++it)
		todel.append(it.current());

	if (todel.count() && QMessageBox::question(this, tr("Deleting bookmarks"), tr("Delete selected bookmarks?"),
						   QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
	{
		for (QListViewItem *item = todel.first(); item; item = todel.next())
		{
			bookmarks->remove(item->text(0));
			delete item;
		}
	}
}/*}}}*/

void BookmarkManager::selectAll()/*{{{*/
{
	lview->selectAll(true);
}/*}}}*/

void BookmarkManager::selectNone()/*{{{*/
{
	lview->selectAll(false);
}/*}}}*/

void BookmarkManager::selectInvalid()/*{{{*/
{
	for (QListViewItem *item = invalid.first(); item; item = invalid.next())
		item->setSelected(true);
}/*}}}*/

