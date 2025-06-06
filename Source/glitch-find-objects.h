/*
** Copyright (c) 2015 - 10^10^10, Alexis Megas.
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
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

#ifndef _glitch_find_objects_h_
#define _glitch_find_objects_h_

#include <QPointer>
#include <QTimer>
#include <QVector>

#include "ui_glitch-find-objects.h"

class QTreeWidgetItem;
class glitch_collapse_expand_tool_button;
class glitch_find_objects_position_item;
class glitch_object;
class glitch_view;

class glitch_find_objects: public QDialog
{
  Q_OBJECT

 public:
  enum class Columns
  {
    Identifier = 1,
    Object = 0,
    Position = 2,
    Type = 3,
    TypeTotal = 4
  };

  glitch_find_objects(QWidget *parent);
  ~glitch_find_objects();

 public slots:
  void slotSynchronize(void);

 private:
  QHash<QString, int> m_typeTotals;
  QPointer<glitch_view> m_view;
  QVector<glitch_find_objects_position_item *> m_items;
  QTimer m_searchTimer;
  QTimer m_synchronizeTimer;
  Ui_glitch_find_objects m_ui;
  glitch_collapse_expand_tool_button *m_collapse;
  void find(QTreeWidgetItem *i, const QSet<qint64> &ids, glitch_object *object);
  void find(const QSet<qint64> &ids);

 private slots:
  void slotCustomContextMenuRequested(const QPoint &point);
  void slotFind(void);
  void slotItemDoubleClicked(QTreeWidgetItem *i, int column);
  void slotSearch(void);
  void slotSynchronizeImplementation(void);

 signals:
  void setTotals(const QHash<QString, int> &totals);
};

#endif
