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

#include "imgcache.h"
#include <qptrcollection.h>

ImgCache::ImgCache(int size): QCache<QImage>(size)
{
        setAutoDelete(true);
}

ImgCache::~ImgCache()
{
}

void ImgCache::setSize(int size)
{
        if (size < 0)
                size = 0;
        setMaxCost(size);
}

QPtrCollection::Item ImgCache::newItem(QPtrCollection::Item d)
{
        QImage *img = new QImage(*(QImage *)d);
        img->detach();
        return img;
}

bool ImgCache::exists(const QString & key)
{
        return find(key) != NULL;
}

bool ImgCache::get(const QString &key, QImage &img)
{
        if (QImage *tmp = find(key))
        {
                img = tmp->copy(); //get deep copy
                return true;
        }
        return false;
}

QImage* ImgCache::find(const QString &k, bool ref)
{
        return QCache<QImage>::find(k, ref);
}

