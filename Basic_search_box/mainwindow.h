#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
  
public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  
protected slots:
  void searchExact(const QString& text);
  void searchByTokens(const QString& text);
  
private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
