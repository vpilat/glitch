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

#include "glitch-syntax-highlighter.h"

glitch_syntax_highlighter::glitch_syntax_highlighter(QTextDocument *document):
  QSyntaxHighlighter(document)
{
}

glitch_syntax_highlighter::~glitch_syntax_highlighter()
{
}

void glitch_syntax_highlighter::highlightBlock(const QString &text)
{
  foreach(const auto &rule, m_highlightingRules)
    {
      QRegularExpressionMatchIterator matchIterator
	(rule.pattern.globalMatch(text));

      while(matchIterator.hasNext())
	{
	  QRegularExpressionMatch match(matchIterator.next());

	  setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}

void glitch_syntax_highlighter::setKeywordsColors
(const QMap<QString, QColor> &map)
{
  HighlightingRule rule;
  QMapIterator<QString, QColor> it(map);
  QTextCharFormat format;

  while(it.hasNext())
    {
      it.next();
      format.setFontWeight(QFont::ExtraBold);
      format.setForeground(it.value());
      rule.format = format;
      rule.pattern = QRegularExpression
	(QStringLiteral("\\b%1\\b").arg(it.key()),
	 QRegularExpression::CaseInsensitiveOption);
      m_highlightingRules.append(rule);
    }

  format.setFontWeight(QFont::Normal);
  format.setForeground(Qt::darkGreen);
  rule.format = format;
  rule.pattern = QRegularExpression(QStringLiteral("'.*'"));
  m_highlightingRules.append(rule);
  rule.pattern = QRegularExpression(QStringLiteral("\".*\""));
  m_highlightingRules.append(rule);
}
