#pragma once

#include <qobject.h>

class MyObject : public QObject {
  Q_OBJECT

public:
  explicit MyObject(QObject* parent = nullptr);
  ~MyObject() = default;

public slots:
  void foobar(bool state);

signals:
  void signalEmitted();
};
