#include "mainwindow.h"
#include <QApplication>
#include <QProxyStyle>

class MyProxyStyle : public QProxyStyle {
public:
  MyProxyStyle(const QString& name)
    : QProxyStyle(name),
      m_clear_icon(":/clear.png") {
  }
  
public:
  virtual QIcon standardIcon(StandardPixmap standard_icon,
                             const QStyleOption* option,
                             const QWidget* widget) const override {
    if (standard_icon == SP_LineEditClearButton) return m_clear_icon;
    return QProxyStyle::standardIcon(standard_icon, option, widget);
  }
  
private:
  QIcon m_clear_icon;
};

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  
  qApp->setStyle(new MyProxyStyle("fusion"));
  
  MainWindow w;
  w.show();
  
  return a.exec();
}
