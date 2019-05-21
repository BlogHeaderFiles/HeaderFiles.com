#include "MyObject.h"
#include <qdebug.h>

MyObject::MyObject(QObject* parent)
  : QObject(parent)
{
  // QString != const QString&
  //connect(this, &MyObject::stringEmitted, this, qOverload<QString>(&MyObject::foobar));
  connect(this, &MyObject::stringEmitted, this, qOverload<const QString&>(&MyObject::foobar));
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
