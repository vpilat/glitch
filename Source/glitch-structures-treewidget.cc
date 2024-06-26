/*
** Copyright (c) 2015 - 10^10^10, Alexis Megas.
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
** 3. The name of the author may not be used to endorse or promote products
**    derived from Glitch without specific prior written permission.
**
** GLITCH IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
** IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
** NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
** GLITCH, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <QApplication>
#include <QDrag>
#include <QMimeData>

#include "glitch-structures-treewidget.h"

glitch_structures_treewidget::glitch_structures_treewidget(QWidget *parent):
  QTreeWidget(parent)
{
  m_projectType = glitch_common::ProjectTypes::XYZProject;
  setDragDropMode(QAbstractItemView::DragOnly);
}

glitch_structures_treewidget::~glitch_structures_treewidget()
{
}

void glitch_structures_treewidget::setProjectType
(const glitch_common::ProjectTypes projectType)
{
  m_projectType = projectType;
}

void glitch_structures_treewidget::startDrag(Qt::DropActions supportedActions)
{
  Q_UNUSED(supportedActions);

  auto list(selectedItems());

  foreach(auto item, list)
    {
      if(!item)
	continue;

      auto drag = new QDrag(this);
      auto mimeData = new QMimeData();

      mimeData->setText(item->data(0, Qt::UserRole).toString());
      drag->setHotSpot(QPoint(24, 48));
      drag->setMimeData(mimeData);

      if(item->parent() && list.size() == 1)
	drag->setPixmap(item->parent()->icon(0).pixmap(QSize(48, 48)));

      drag->exec(Qt::CopyAction);
      QApplication::processEvents();
    }
}
