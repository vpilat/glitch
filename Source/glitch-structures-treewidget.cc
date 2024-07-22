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
#include <QMenu>
#include <QMimeData>
#include <QMouseEvent>
#include <QtDebug>

#include "glitch-structures-treewidget.h"
#include "ui_glitch-structures.h"

glitch_structures_treewidget::glitch_structures_treewidget(QWidget *parent):
  QTreeWidget(parent)
{
  connect(&m_pressAndHoldTimer,
	  &QTimer::timeout,
	  this,
	  &glitch_structures_treewidget::slotPressAndHoldTimeout);
  connect(this,
	  SIGNAL(customContextMenuRequested(const QPoint &)),
	  this,
	  SLOT(slotCustomContextMenuRequested(const QPoint &)));
  m_pressAndHoldTimer.setInterval(QApplication::startDragTime());
  m_pressAndHoldTimer.setSingleShot(true);
  m_projectType = glitch_common::ProjectTypes::XYZProject;
  setContextMenuPolicy(Qt::CustomContextMenu);
  setDragDropMode(QAbstractItemView::DragOnly);
}

glitch_structures_treewidget::~glitch_structures_treewidget()
{
}

void glitch_structures_treewidget::mousePressEvent(QMouseEvent *event)
{
  QTreeWidget::mousePressEvent(event);
  event ? event->accept() : (void) 0;
  event ? itemAt(event->pos()) ? itemAt(event->pos())->setSelected(true) :
    (void) 0 : (void) 0;
  m_pressAndHoldTimer.start();
}

void glitch_structures_treewidget::setProjectType
(const glitch_common::ProjectTypes projectType)
{
  m_projectType = projectType;
}

void glitch_structures_treewidget::slotCustomContextMenuRequested
(const QPoint &point)
{
  auto item = itemAt(point);

  if(item && item->childCount() > 0)
    {
      QMenu menu(this);

      menu.addSection(tr("glitch-structures-treewidget"));

      auto action = menu.addAction
	(tr("&Show category contents in new dialog..."),
	 this,
	 SLOT(slotFloatingCategoryDialog(void)));

      action->setData(point);
      menu.exec(mapToGlobal(point));
    }
}

void glitch_structures_treewidget::slotFloatingCategoryDialog(void)
{
  auto action = qobject_cast<QAction *> (sender());

  if(!action)
    return;

  auto item = itemAt(action->data().toPoint());

  if(!item)
    return;

  auto dialog = findChild<QDialog *> (item->text(0));

  if(!dialog)
    {
      Ui_glitch_structures ui;

      dialog = new QDialog(this);
      ui.setupUi(dialog);
      dialog->resize(500, 500);
      dialog->setObjectName(item->text(0));
      dialog->setWindowTitle(tr("Glitch: %1").arg(item->text(0)));
    }

  dialog->showNormal();
  dialog->activateWindow();
  dialog->raise();
}

void glitch_structures_treewidget::slotPressAndHoldTimeout(void)
{
  auto instance = qobject_cast<QGuiApplication *> (QApplication::instance());

  if(instance && instance->mouseButtons() & Qt::LeftButton)
    startDrag(Qt::CopyAction);
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
