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

#include "glitch-object-logical-operator-arduino.h"
#include "glitch-scroll-filter.h"
#include "glitch-undo-command.h"

glitch_object_logical_operator_arduino::glitch_object_logical_operator_arduino
(QWidget *parent):glitch_object_logical_operator_arduino(1, parent)
{
}

glitch_object_logical_operator_arduino::glitch_object_logical_operator_arduino
(const QString &operatorType, QWidget *parent):
  glitch_object_logical_operator_arduino(1, parent)
{
  setOperatorType(operatorType);
  m_properties[Properties::LOGICAL_OPERATOR] =
    m_ui.logical_operator->currentText();
}

glitch_object_logical_operator_arduino::glitch_object_logical_operator_arduino
(const qint64 id, QWidget *parent):glitch_object(id, parent)
{
  m_operatorType = OperatorTypes::AND_OPERATOR;
  m_type = "arduino-logicaloperator";
  m_ui.setupUi(this);
  m_ui.logical_operator->installEventFilter(new glitch_scroll_filter(this));
  connect(m_ui.logical_operator,
	  SIGNAL(currentIndexChanged(int)),
	  this,
	  SLOT(slotLogicalOperatorChanged(void)));
  prepareContextMenu();
  setOperatorType(m_operatorType);
  m_properties[Properties::LOGICAL_OPERATOR] =
    m_ui.logical_operator->currentText();
}

glitch_object_logical_operator_arduino::
~glitch_object_logical_operator_arduino()
{
}

QString glitch_object_logical_operator_arduino::code(void) const
{
  switch(m_operatorType)
    {
    case OperatorTypes::NOT_OPERATOR:
      {
	return QString("(!(%1))").arg(inputs().value(0));
      }
    default:
      {
	QString string("(");
	auto list(inputs());

	for(int i = 0; i < list.size(); i++)
	  {
	    string.append(QString("(%1)").arg(list.at(i)));

	    if(i != list.size() - 1)
	      string.append
		(QString(" %1 ").arg(m_ui.logical_operator->currentText()));
	  }

	string = string.trimmed();
	string.append(")");
	return string;
      }
    }
}

QString glitch_object_logical_operator_arduino::logicalOperator(void) const
{
  return m_ui.logical_operator->currentText();
}

bool glitch_object_logical_operator_arduino::hasInput(void) const
{
  return true;
}

bool glitch_object_logical_operator_arduino::hasOutput(void) const
{
  return true;
}

bool glitch_object_logical_operator_arduino::isFullyWired(void) const
{
  switch(m_operatorType)
    {
    case OperatorTypes::NOT_OPERATOR:
      {
	return inputs().size() >= 1;
      }
    default:
      {
	return false;
      }
    }
}

bool glitch_object_logical_operator_arduino::shouldPrint(void) const
{
  return false;
}

glitch_object_logical_operator_arduino *glitch_object_logical_operator_arduino::
clone(QWidget *parent) const
{
  auto clone = new glitch_object_logical_operator_arduino(parent);

  clone->cloneWires(m_wires);
  clone->m_properties = m_properties;
  clone->resize(size());
  clone->setCanvasSettings(m_canvasSettings);
  clone->setOperatorType(m_operatorType);
  clone->setStyleSheet(styleSheet());
  return clone;
}

glitch_object_logical_operator_arduino *glitch_object_logical_operator_arduino::
createFromValues(const QMap<QString, QVariant> &values,
		 QString &error,
		 QWidget *parent)
{
  Q_UNUSED(error);

  auto object = new glitch_object_logical_operator_arduino
    (values.value("myoid").toLongLong(), parent);

  object->setProperties
    (values.value("properties").toString().split(s_splitRegularExpression));
  object->setStyleSheet(values.value("stylesheet").toString());
  return object;
}

void glitch_object_logical_operator_arduino::addActions(QMenu &menu)
{
  addDefaultActions(menu);
}

void glitch_object_logical_operator_arduino::save
(const QSqlDatabase &db, QString &error)
{
  glitch_object::save(db, error);

  if(!error.isEmpty())
    return;

  QMap<QString, QVariant> properties;

  properties["logical_operator"] = m_ui.logical_operator->currentText();
  glitch_object::saveProperties(properties, db, error);
}

void glitch_object_logical_operator_arduino::setOperatorType
(const QString &operatorType)
{
  if(operatorType.contains("!"))
    setOperatorType(OperatorTypes::NOT_OPERATOR);
  else if(operatorType.contains("||"))
    setOperatorType(OperatorTypes::OR_OPERATOR);
  else
    setOperatorType(OperatorTypes::AND_OPERATOR);
}

void glitch_object_logical_operator_arduino::setOperatorType
(const OperatorTypes operatorType)
{
  m_operatorType = operatorType;
  m_ui.logical_operator->blockSignals(true);

  switch(m_operatorType)
    {
    case OperatorTypes::NOT_OPERATOR:
      {
	m_ui.logical_operator->setCurrentIndex(1);
	break;
      }
    case OperatorTypes::OR_OPERATOR:
      {
	m_ui.logical_operator->setCurrentIndex(2);
	break;
      }
    default:
      {
	m_ui.logical_operator->setCurrentIndex(0);
	break;
      }
    }

  m_ui.logical_operator->blockSignals(false);
  setName(m_ui.logical_operator->currentText());
}

void glitch_object_logical_operator_arduino::setProperties
(const QStringList &list)
{
  glitch_object::setProperties(list);
  m_properties[Properties::LOGICAL_OPERATOR] = "&&";

  for(int i = 0; i < list.size(); i++)
    {
      auto string(list.at(i));

      if(string.simplified().startsWith("logical_operator = "))
	{
	  string = string.mid(string.indexOf('=') + 1);
	  string.remove("\"");
	  m_properties[Properties::LOGICAL_OPERATOR] = string.trimmed();
	}
    }

  setOperatorType(m_properties.value(Properties::LOGICAL_OPERATOR).toString());
}

void glitch_object_logical_operator_arduino::setProperty
(const Properties property, const QVariant &value)
{
  glitch_object::setProperty(property, value);

  switch(property)
    {
    case Properties::LOGICAL_OPERATOR:
      {
	setOperatorType(value.toString());
	break;
      }
    default:
      {
	break;
      }
    }
}

void glitch_object_logical_operator_arduino::slotLogicalOperatorChanged(void)
{
  setOperatorType(m_ui.logical_operator->currentText());

  if(!m_undoStack)
    return;

  auto undoCommand = new glitch_undo_command
    (m_ui.logical_operator->currentText(),
     m_properties.value(Properties::LOGICAL_OPERATOR).toString(),
     glitch_undo_command::PROPERTY_CHANGED,
     Properties::LOGICAL_OPERATOR,
     this);

  m_properties[Properties::LOGICAL_OPERATOR] =
    m_ui.logical_operator->currentText();
  undoCommand->setText
    (tr("logical operator changed (%1, %2)").
     arg(scenePos().x()).arg(scenePos().y()));
  m_undoStack->push(undoCommand);
  emit changed();
}
