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

#ifndef _glitch_object_serial_arduino_h_
#define _glitch_object_serial_arduino_h_

#include "glitch-object-simple-text-arduino.h"

class glitch_object_serial_arduino: public glitch_object_simple_text_arduino
{
  Q_OBJECT

 public:
  glitch_object_serial_arduino(const QString &serialType, QWidget *parent);
  ~glitch_object_serial_arduino();
  QString code(void) const;
  bool hasInput(void) const;
  bool hasOutput(void) const;
  bool isFullyWired(void) const;
  bool shouldPrint(void) const;
  glitch_object_serial_arduino *clone(QWidget *parent) const;
  static glitch_object_serial_arduino *createFromValues
    (const QMap<QString, QVariant> &values, QString &error, QWidget *parent);
  void save(const QSqlDatabase &db, QString &error);

 private:
  enum class Type
  {
    AVAILABLE = 0,
    AVAILABLE_FOR_WRITE,
    BEGIN,
    END,
    FIND,
    FIND_UNTIL,
    FLUSH,
    PARSE_FLOAT,
    PARSE_INT,
    PEEK,
    PRINT,
    PRINTLN,
    READ,
    READ_BYTES,
    READ_BYTES_UNTIL,
    READ_STRING,
    READ_STRING_UNTIL,
    SET_TIMEOUT,
    WRITE
  };

  glitch_object_serial_arduino(const qint64 id, QWidget *parent);

  QString description(void) const
  {
    switch(stringToSerialType(m_text))
      {
      case Type::AVAILABLE:
      default:
	{
	  return "int available(void)";
	}
      case Type::AVAILABLE_FOR_WRITE:
	{
	  return "int availableForWrite(void)";
	}
      case Type::BEGIN:
	{
	  return "void begin(unsigned long baudrate) / "
	    "void begin(unsigned long baudrate, uint16_t config)";
	}
      case Type::END:
	{
	  return "void end(void)";
	}
      case Type::FIND:
	{
	  return "bool find(const char *target) / "
	    "bool find(const char *target, size_t length)";
	}
      case Type::FIND_UNTIL:
	{
	  return "bool findUntil(const char *target, const char *terminator)";
	}
      case Type::FLUSH:
	{
	  return "void flush(void)";
	}
      case Type::PARSE_FLOAT:
	{
	  return "float parseFloat(LookaheadMode lookahead = SKIP_ALL, "
	    "char ignore = NO_IGNORE_CHAR)";
	}
      case Type::PARSE_INT:
	{
	  return "long parseInt(LookaheadMode lookahead = SKIP_ALL, "
	    "char ignore = NO_IGNORE_CHAR)";
	}
      case Type::PEEK:
	{
	  return "int read(void)";
	}
      case Type::PRINT:
	{
	  return "size_t print(T val, int format)";
	}
      case Type::PRINTLN:
	{
	  return "size_t println(T val, int format)";
	}
      case Type::READ:
	{
	  return "int read(void)";
	}
      case Type::READ_BYTES:
	{
	  return "size_t readBytes(char *buffer, size_t length) / "
	    "size_t readBytes(uint8_t *buffer, size_t length)";
	}
      case Type::READ_BYTES_UNTIL:
	{
	  return "size_t readBytesUntil(char terminator, char *buffer, "
	    "size_t length) / "
	    "size_t readBytesUntil(char terminator, uint8_t *buffer, "
	    "size_t length)";
	}
      case Type::READ_STRING:
	{
	  return "String readString(void)";
	}
      case Type::READ_STRING_UNTIL:
	{
	  return "String readStringUntil(char terminator)";
	}
      case Type::SET_TIMEOUT:
	{
	  return "void setTimeout(unsigned long timeout)";
	}
      case Type::WRITE:
	{
	  return "size_t write(const char *str) / "
	    "size_t write(const uint8_t *buffer, size_t size) / "
	    "size_t write(uint8_t val)";
	}
      }
  }

  QString serialTypeToString(const Type type) const
  {
    switch(type)
      {
      case Type::AVAILABLE:
	{
	  return "available";
	}
      case Type::AVAILABLE_FOR_WRITE:
	{
	  return "availableForWrite";
	}
      case Type::BEGIN:
	{
	  return "begin";
	}
      case Type::END:
	{
	  return "end";
	}
      case Type::FIND:
	{
	  return "find";
	}
      case Type::FIND_UNTIL:
	{
	  return "findUntil";
	}
      case Type::FLUSH:
	{
	  return "flush";
	}
      case Type::PARSE_FLOAT:
	{
	  return "parseFloat";
	}
      case Type::PARSE_INT:
	{
	  return "parseInt";
	}
      case Type::PEEK:
	{
	  return "peek";
	}
      case Type::PRINT:
	{
	  return "print";
	}
      case Type::PRINTLN:
	{
	  return "println";
	}
      case Type::READ:
	{
	  return "read";
	}
      case Type::READ_BYTES:
	{
	  return "readBytes";
	}
      case Type::READ_BYTES_UNTIL:
	{
	  return "readBytesUntil";
	}
      case Type::READ_STRING:
	{
	  return "readString";
	}
      case Type::READ_STRING_UNTIL:
	{
	  return "readStringUntil";
	}
      case Type::SET_TIMEOUT:
	{
	  return "setTimeout";
	}
      case Type::WRITE:
	{
	  return "write";
	}
      default:
	{
	  return "available";
	}
      }
  }

  static Type stringToSerialType(const QString &s)
  {
    auto const string(s.toLower());

    if(string.contains("availableforwrite"))
      return Type::AVAILABLE_FOR_WRITE;
    else if(string.contains("begin"))
      return Type::BEGIN;
    else if(string.contains("end"))
      return Type::END;
    else if(string.contains("finduntil"))
      return Type::FIND_UNTIL;
    else if(string.contains("find"))
      return Type::FIND;
    else if(string.contains("flush"))
      return Type::FLUSH;
    else if(string.contains("parsefloat"))
      return Type::PARSE_FLOAT;
    else if(string.contains("parseint"))
      return Type::PARSE_INT;
    else if(string.contains("peek"))
      return Type::PEEK;
    else if(string.contains("println"))
      return Type::PRINTLN;
    else if(string.contains("print"))
      return Type::PRINT;
    else if(string.contains("readbytesuntil"))
      return Type::READ_BYTES_UNTIL;
    else if(string.contains("readbytes"))
      return Type::READ_BYTES;
    else if(string.contains("readstringuntil"))
      return Type::READ_STRING_UNTIL;
    else if(string.contains("readstring"))
      return Type::READ_STRING;
    else if(string.contains("read"))
      return Type::READ;
    else if(string.contains("settimeout"))
      return Type::SET_TIMEOUT;
    else if(string.contains("write"))
      return Type::WRITE;
    else
      return Type::AVAILABLE;
  }

  void setProperties(const QStringList &list);
  void setProperty(const Properties property, const QVariant &value);
};

#endif
