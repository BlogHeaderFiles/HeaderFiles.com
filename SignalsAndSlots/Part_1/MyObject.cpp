#include "MyObject.h"
#include <qdebug.h>

MyObject::MyObject(QObject* parent)
  : QObject(parent)
{
}

void MyObject::foobar(bool state)
{
  qDebug() << __FUNCTION__ << state << (sender() ? sender()->objectName() : "<no sender>") << "{";

  if (state) {
    qDebug() << "Emit signal";
    emit signalEmitted();
  }

  qDebug() << "}";
}
