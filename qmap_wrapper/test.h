#pragma once

#include <qobject.h>

class Test : public QObject
{
  Q_OBJECT

private slots:
  void qmap_values();
  void qmap_keys();
  void qmap_const_keys();
  void qmap_tostdmap();
  void qmap_iterator();
  void qmap_wrapper();
};
