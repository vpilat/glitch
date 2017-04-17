/*
** Copyright (c) 2004 - 10^10^10, Alexis Megas.
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
**    derived from GlowBot without specific prior written permission.
**
** GLOWBOT IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
** IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
** NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
** GLOWBOT, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <limits>

#include "glowbot-alignment.h"
#include "glowbot-object.h"
#include "glowbot-proxy-widget.h"
#include "glowbot-scene.h"
#include "glowbot-view.h"

glowbot_alignment::glowbot_alignment(QWidget *parent):QDialog(parent)
{
  m_ui.setupUi(this);
  connect(m_ui.bottom_align,
	  SIGNAL(clicked(void)),
	  this,
	  SLOT(slotAlign(void)));
  connect(m_ui.horizontal_center_align,
	  SIGNAL(clicked(void)),
	  this,
	  SLOT(slotAlign(void)));
  connect(m_ui.left_align,
	  SIGNAL(clicked(void)),
	  this,
	  SLOT(slotAlign(void)));
  connect(m_ui.right_align,
	  SIGNAL(clicked(void)),
	  this,
	  SLOT(slotAlign(void)));
  connect(m_ui.top_align,
	  SIGNAL(clicked(void)),
	  this,
	  SLOT(slotAlign(void)));
  connect(m_ui.vertical_center_align,
	  SIGNAL(clicked(void)),
	  this,
	  SLOT(slotAlign(void)));
  setWindowModality(Qt::NonModal);
}

glowbot_alignment::~glowbot_alignment()
{
}

void glowbot_alignment::align(const AlignmentType alignmentType)
{
  glowbot_view *view = qobject_cast<glowbot_view *> (parentWidget());

  if(!view)
    return;

  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

  QPair<int, int> maxP;
  QPair<int, int> minP;
  int x = 0;
  int y = 0;

  switch(alignmentType)
    {
    case ALIGN_BOTTOM:
      {
	y = 0;
	break;
      }
    case ALIGN_CENTER_HORIZONTAL:
    case ALIGN_CENTER_VERTICAL:
      {
	maxP.first = maxP.second = 0;
	minP.first = minP.second = std::numeric_limits<int>::max();
	break;
      }
    case ALIGN_LEFT:
      {
	x = std::numeric_limits<int>::max();
	break;
      }
    case ALIGN_RIGHT:
      {
	x = 0;
	break;
      }
    case ALIGN_TOP:
      {
	y = std::numeric_limits<int>::max();
	break;
      }
    default:
      {
	QApplication::restoreOverrideCursor();
	return;
      }
    }

  QList<QGraphicsItem *> list(view->scene()->items(Qt::AscendingOrder));
  bool firstIteration = true;

 start_label:

  for(int i = 0; i < list.size(); i++)
    {
      glowbot_proxy_widget *proxy =
	qgraphicsitem_cast <glowbot_proxy_widget *> (list.at(i));

      if(!proxy || !proxy->isSelected())
	continue;

      bool movable = proxy->isMovable();
      glowbot_object *widget = qobject_cast<glowbot_object *> (proxy->widget());

      if(!widget)
	continue;

      switch(alignmentType)
	{
	case ALIGN_BOTTOM:
	  {
	    x = widget->pos().x();
	    y = qMax(y, widget->height() + widget->pos().y());
	    break;
	  }
	case ALIGN_CENTER_HORIZONTAL:
	case ALIGN_CENTER_VERTICAL:
	  {
	    maxP.first = qMax(maxP.first, widget->pos().x() + widget->width());
	    maxP.second = qMax
	      (maxP.second, widget->height() + widget->pos().y());
	    minP.first = qMin(minP.first, widget->pos().x());
	    minP.second = qMin(minP.second, widget->pos().y());
	    break;
	  }
	case ALIGN_LEFT:
	  {
	    x = qMin(x, widget->pos().x());
	    y = widget->pos().y();
	    break;
	  }
	case ALIGN_RIGHT:
	  {
	    x = qMax(x, widget->pos().x() + widget->width());
	    y = widget->pos().y();
	    break;
	  }
	case ALIGN_TOP:
	  {
	    x = widget->pos().x();
	    y = qMin(y, widget->pos().y());
	    break;
	  }
	default:
	  break;
	}

      if(firstIteration || !movable)
	continue;

      switch(alignmentType)
	{
	case ALIGN_BOTTOM:
	  {
	    if(y != widget->height() + widget->pos().y())
	      widget->move(x, y - widget->height());

	    break;
	  }
	case ALIGN_CENTER_HORIZONTAL:
	case ALIGN_CENTER_VERTICAL:
	  {
	    QRect rect(QPoint(minP.first, minP.second),
		       QPoint(maxP.first, maxP.second));

	    if(alignmentType == ALIGN_CENTER_HORIZONTAL)
	      widget->move
		(widget->pos().x(), rect.center().y() - widget->height() / 2);
	    else
	      widget->move
		(rect.center().x() - widget->width() / 2, widget->pos().y());

	    break;
	  }
	case ALIGN_RIGHT:
	  {
	    if(x != widget->pos().x() + widget->width())
	      widget->move(x - widget->width(), y);

	    break;
	  }
	default:
	  widget->move(x, y);
	}
    }

  if(firstIteration)
    {
      firstIteration = false;
      goto start_label;
    }

  QApplication::restoreOverrideCursor();
}

void glowbot_alignment::slotAlign(void)
{
  QToolButton *toolButton = qobject_cast<QToolButton *> (sender());

  if(m_ui.bottom_align == toolButton)
    align(ALIGN_BOTTOM);
  else if(m_ui.horizontal_center_align == toolButton)
    align(ALIGN_CENTER_HORIZONTAL);
  else if(m_ui.left_align == toolButton)
    align(ALIGN_LEFT);
  else if(m_ui.right_align == toolButton)
    align(ALIGN_RIGHT);
  else if(m_ui.top_align == toolButton)
    align(ALIGN_TOP);
  else if(m_ui.vertical_center_align == toolButton)
    align(ALIGN_CENTER_VERTICAL);
}

void glowbot_alignment::slotStack(void)
{
}

void glowbot_alignment::stack(const StackType stackType)
{
  Q_UNUSED(stackType);
}
