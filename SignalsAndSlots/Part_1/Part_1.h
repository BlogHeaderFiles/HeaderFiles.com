#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Part_1.h"
#include <qlabel.h>
#include "MyObject.h"

class Part_1 : public QMainWindow {
  Q_OBJECT

public:
  explicit Part_1(QWidget* parent = Q_NULLPTR);
  ~Part_1() = default;

  void printMessage(); // not a slot

public slots:
  void showMessage();

protected slots:
  void onObjectSignal();
  void changeStatusBar(const QString& label = "Hello world!");

private:
  Ui::Part_1Class ui;

  QLabel* m_status_label;
  MyObject m_object;
};
