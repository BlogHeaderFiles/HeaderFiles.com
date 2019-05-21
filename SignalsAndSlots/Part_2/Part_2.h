#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Part_2.h"
#include <qlabel.h>
#include "MyObject.h"

class Part_2 : public QMainWindow {
  Q_OBJECT

public:
  explicit Part_2(QWidget* parent = Q_NULLPTR);
  ~Part_2() = default;

  void printMessage(); // not a slot

public slots:
  void showMessage();

protected slots:
  void onPressed(int value);
  void onObjectSignal();
  void changeStatusBar(const QString& label = "Hello world!");
  void onDisconnect();

private:
  Ui::Part_2Class ui;

  QLabel* m_status_label;
  MyObject m_object;

  QMetaObject::Connection m_change_status_bar_connection;
  QList<QMetaObject::Connection> m_connections;
};
