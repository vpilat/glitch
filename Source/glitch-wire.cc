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

#include <QPainter>

#include "glitch-object.h"
#include "glitch-wire.h"

glitch_wire::glitch_wire(QGraphicsItem *parent):QGraphicsObject(parent)
{
}

glitch_wire::~glitch_wire()
{
}

QRectF glitch_wire::boundingRect(void) const
{
  return QRectF();
}

void glitch_wire::paint
(QPainter *painter, const QStyleOptionGraphicsItem *opt, QWidget *widget)
{
  if(painter)
    {
      painter->setRenderHints(QPainter::Antialiasing |
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
			      QPainter::HighQualityAntialiasing | // OpenGL?
#endif
			      QPainter::SmoothPixmapTransform |
			      QPainter::TextAntialiasing,
			      true);
    }
}

void glitch_wire::setLeftObject(glitch_object *object)
{
  if(!object)
    return;
  else if(m_leftObject || m_rightObject == object)
    return;

  connect(object,
	  &glitch_object::destroyed,
	  this,
	  &glitch_wire::deleteLater);
  m_leftObject = object;
}

void glitch_wire::setRightObject(glitch_object *object)
{
  if(!object)
    return;
  else if(m_leftObject == object || m_rightObject)
    return;

  connect(object,
	  &glitch_object::destroyed,
	  this,
	  &glitch_wire::deleteLater);
  m_rightObject = object;
}
