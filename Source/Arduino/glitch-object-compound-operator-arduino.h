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

#ifndef _glitch_object_compound_operator_arduino_h_
#define _glitch_object_compound_operator_arduino_h_

#include "glitch-object.h"
#include "ui_glitch-object-compound-operator-arduino.h"

class glitch_object_compound_operator_arduino: public glitch_object
{
  Q_OBJECT

 public:
  enum class OperatorTypes
  {
    ADDITION_OPERATOR = 0,
    BITWISE_AND_OPERATOR,
    BITWISE_OR_OPERATOR,
    BITWISE_XOR_OPERATOR,
    DECREMENT_OPERATOR,
    DIVISION_OPERATOR,
    INCREMENT_OPERATOR,
    MODULO_OPERATOR,
    MULTIPLICATION_OPERATOR,
    SUBTRACTION_OPERATOR
  };

  glitch_object_compound_operator_arduino(const QString &operatorType,
					  QWidget *parent);
  ~glitch_object_compound_operator_arduino();
  QString code(void) const;
  QString compoundOperator(void) const;
  bool hasInput(void) const;
  bool hasOutput(void) const;
  bool isFullyWired(void) const;
  bool shouldPrint(void) const;
  glitch_object_compound_operator_arduino *clone(QWidget *parent) const;
  static bool isOperator(const QString &o);
  static glitch_object_compound_operator_arduino *createFromValues
    (const QMap<QString, QVariant> &values, QString &error, QWidget *parent);
  void addActions(QMenu &menu);
  void save(const QSqlDatabase &db, QString &error);
  void setOperatorType(const QString &op);

 private:
  glitch_object_compound_operator_arduino(QWidget *parent);
  glitch_object_compound_operator_arduino(const qint64 id, QWidget *parent);
  OperatorTypes m_operatorType;
  Ui_glitch_object_compound_operator_arduino m_ui;
  QSize preferredSize(void) const;
  void compressWidget(const bool state);
  void setOperatorType(const OperatorTypes operatorType);
  void setProperties(const QStringList &list);
  void setProperty(const Properties property, const QVariant &value);

 private slots:
  void slotAdjustSize(void);
  void slotCompoundOperatorChanged(void);
  void slotPreToggled(bool state);
};

#endif
