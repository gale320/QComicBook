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

#include "statusbar.h"
#include <qlabel.h>
#include <qstring.h>

StatusBar::StatusBar(QWidget *parent): QStatusBar(parent)/*{{{*/
{
	page = new QLabel(this);
	page->setFixedWidth(100);
	name = new QLabel(this);

	addWidget(page, 0);
	addWidget(name, 1);

	setPage(0, 0);
}/*}}}*/

StatusBar::~StatusBar()/*{{{*/
{
}/*}}}*/

void StatusBar::clear()/*{{{*/
{
	setPage(0, 0);
	setName(QString::null);
}/*}}}*/

void StatusBar::setPage(int n, int total)/*{{{*/
{
	page->setText(tr("Page") + " " + QString::number(n) + "/" + QString::number(total));
}/*}}}*/

void StatusBar::setName(const QString &n)/*{{{*/
{
	name->setText(n);
}/*}}}*/

