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

#include <QBrush>
#include <QGraphicsProxyWidget>
#include <QPen>
#include <QWidget>
#include <QtDebug>

#include "glitch-resize-widget.h"
#include "glitch-resize-widget-rectangle.h"
#include "glitch-scene.h"

glitch_resize_widget::glitch_resize_widget(QGraphicsItem *parent):
  QGraphicsItem(parent)
{
  m_parent = parent;

  if(!m_parent)
    qDebug() << "glitch_resize_widget::"
	     << "glitch_resize_widget(): "
	     << "parent is zero! Cannot create a complete resize widget.";
}

glitch_resize_widget::~glitch_resize_widget()
{
}

QRectF glitch_resize_widget::boundingRect(void) const
{
  auto rectangle(childrenBoundingRect());

  if(parentItem())
    rectangle |= parentItem()->boundingRect();

  return rectangle;
}

void glitch_resize_widget::paint
(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED(option);
  Q_UNUSED(painter);
  Q_UNUSED(widget);

  if(m_rectanges.isEmpty())
    return;

  QBrush brush((QColor(Qt::blue))); // (( -> CLANG

  if(m_parent)
    {
      auto scene = qobject_cast<glitch_scene *> (m_parent->scene());

      if(scene)
	brush.setColor(QColor(255 - scene->backgroundBrush().color().red(),
			      255 - scene->backgroundBrush().color().green(),
			      255 - scene->backgroundBrush().color().blue()));
    }

  QHashIterator<glitch_resize_widget_rectangle::RectangleLocations,
		glitch_resize_widget_rectangle *> it(m_rectanges);

  while(it.hasNext())
    {
      it.next();

      if(it.value())
	it.value()->setBrush(brush);
    }
}

void glitch_resize_widget::positionEdgeRectangles(void)
{
  QList<QRectF> rectangles;
  QList<glitch_resize_widget_rectangle::RectangleLocations> list;
  auto rectangle(m_parent ? m_parent->boundingRect() : boundingRect());
  auto squareSize = glitch_resize_widget_rectangle::SQUARE_SIZE;

  list << glitch_resize_widget_rectangle::BottomCenter
       << glitch_resize_widget_rectangle::BottomLeft
       << glitch_resize_widget_rectangle::BottomRight
       << glitch_resize_widget_rectangle::CenterLeft
       << glitch_resize_widget_rectangle::CenterRight
       << glitch_resize_widget_rectangle::TopCenter
       << glitch_resize_widget_rectangle::TopLeft
       << glitch_resize_widget_rectangle::TopRight;
  rectangles << QRectF(rectangle.x() + rectangle.width() / 2 - squareSize / 2,
		       rectangle.y() + rectangle.height() + 1,
                       squareSize,
		       squareSize)
	     << QRectF(rectangle.x() - squareSize - 1,
		       rectangle.y() + rectangle.height() + 1,
                       squareSize,
		       squareSize)
	     << QRectF(rectangle.x() + rectangle.width() + 1,
		       rectangle.y() + rectangle.height() + 1,
                       squareSize,
		       squareSize)
	     << QRectF(rectangle.x() - squareSize - 1,
		       rectangle.y() + rectangle.height() / 2 - squareSize / 2,
                       squareSize,
		       squareSize)
	     << QRectF(rectangle.x() + rectangle.width() + 1,
		       rectangle.y() + rectangle.height() / 2 - squareSize / 2,
                       squareSize,
		       squareSize)
	     << QRectF(rectangle.x() + rectangle.width() / 2 - squareSize / 2,
		       rectangle.y() - squareSize - 1,
                       squareSize,
                       squareSize)
	     << QRectF(rectangle.x() - squareSize - 1,
		       rectangle.y() - squareSize - 1,
                       squareSize,
                       squareSize)
	     << QRectF(rectangle.x() + rectangle.width() + 1,
		       rectangle.y() - squareSize - 1,
                       squareSize,
                       squareSize);
  prepareRectangles();

  for(int i = 0; i < list.size(); i++)
    {
      auto rectangle = m_rectanges.value(list.at(i));

      if(rectangle)
	rectangle->setRect(rectangles.value(i));
    }
}

void glitch_resize_widget::prepareRectangles(void)
{
  if(!m_parent)
    return;
  else if(!m_rectanges.isEmpty())
    return;

  QBrush brush((QColor(Qt::blue))); // (( -> CLANG

  if(m_parent)
    {
      auto scene = qobject_cast<glitch_scene *> (m_parent->scene());

      if(scene)
	brush.setColor(QColor(255 - scene->backgroundBrush().color().red(),
			      255 - scene->backgroundBrush().color().green(),
			      255 - scene->backgroundBrush().color().blue()));
    }

  QList<glitch_resize_widget_rectangle::RectangleLocations> list;
  QPen pen;

  list << glitch_resize_widget_rectangle::BottomCenter
       << glitch_resize_widget_rectangle::BottomLeft
       << glitch_resize_widget_rectangle::BottomRight
       << glitch_resize_widget_rectangle::CenterLeft
       << glitch_resize_widget_rectangle::CenterRight
       << glitch_resize_widget_rectangle::TopCenter
       << glitch_resize_widget_rectangle::TopLeft
       << glitch_resize_widget_rectangle::TopRight;
  pen.setWidthF(0.001);

  for(int i = 0; i < list.size(); i++)
    {
      auto rectangle = new glitch_resize_widget_rectangle(m_parent, list.at(i));

      rectangle->setBrush(brush);
      rectangle->setPen(pen);
      rectangle->setVisible(false);
      m_rectanges[list.at(i)] = rectangle;
    }
}

void glitch_resize_widget::showEdgeRectangles(const bool state)
{
  positionEdgeRectangles();

  QHashIterator<glitch_resize_widget_rectangle::RectangleLocations,
		glitch_resize_widget_rectangle *> it(m_rectanges);
  auto isParentSelected = true;

  if(parentItem())
    isParentSelected = parentItem()->isSelected();

  while(it.hasNext())
    {
      it.next();

      if(it.value())
	it.value()->setVisible(isParentSelected && state);
    }
}

void glitch_resize_widget::showEdgeRectanglesForLockedPosition
(const bool isParentSelected, const bool state)
{
  positionEdgeRectangles();

  QList<glitch_resize_widget_rectangle::RectangleLocations> list;

  list << glitch_resize_widget_rectangle::BottomCenter
       << glitch_resize_widget_rectangle::BottomLeft
       << glitch_resize_widget_rectangle::BottomRight
       << glitch_resize_widget_rectangle::CenterLeft
       << glitch_resize_widget_rectangle::CenterRight
       << glitch_resize_widget_rectangle::TopCenter
       << glitch_resize_widget_rectangle::TopLeft
       << glitch_resize_widget_rectangle::TopRight;

  for(int i = 0; i < list.size(); i++)
    {
      auto rectangle = m_rectanges.value(list.at(i));

      if(rectangle)
	switch(list.at(i))
	  {
	  case glitch_resize_widget_rectangle::BottomCenter:
	  case glitch_resize_widget_rectangle::BottomLeft:
	  case glitch_resize_widget_rectangle::BottomRight:
	  case glitch_resize_widget_rectangle::CenterRight:
	  case glitch_resize_widget_rectangle::TopRight:
	    {
	      rectangle->setParentLocked(state);
	      rectangle->setVisible(isParentSelected);
	      break;
	    }
	  default:
	    {
	      rectangle->setVisible(isParentSelected && !state);
	      break;
	    }
	  }
    }
}