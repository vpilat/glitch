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

#ifndef _glitch_source_preview_h_
#define _glitch_source_preview_h_

#include <QPointer>

#include "ui_glitch-source-preview.h"

class glitch_object;
class glitch_syntax_highlighter;

class glitch_source_preview: public QDialog
{
  Q_OBJECT

 public:
  glitch_source_preview(QWidget *parent);
  ~glitch_source_preview();
  void setKeywordsColors(const QMap<QString, QColor> &map);
  void setObject(glitch_object *object);

 public slots:
  void slotObjectChanged(void);

 private:
  QPalette m_originalFindPalette;
  QPointer<glitch_object> m_object;
  Ui_glitch_source_preview m_ui;
  glitch_syntax_highlighter *m_syntaxHighlighter;
  void setSource(const QString &text);

 private slots:
  void slotFind(void);
  void slotFindText(void);
};

#endif
