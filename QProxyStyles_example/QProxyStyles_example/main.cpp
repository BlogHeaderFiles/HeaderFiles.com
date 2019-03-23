#include <QtWidgets/QApplication>
#include <QProxyStyle>
#include <QMessageBox>

class MyProxyStyle : public QProxyStyle {
public:
  MyProxyStyle(const QString& name)
    : QProxyStyle(name),
      m_warning_icon(":/resources/warning.png") {
  }

public:
  virtual QIcon standardIcon(StandardPixmap standard_icon, const QStyleOption* option, const QWidget* widget) const override {
    switch (standard_icon) { // custom, more stylized icons for warning message boxes
    case SP_MessageBoxWarning: return m_warning_icon;
    }

    // Handle any other
    return QProxyStyle::standardIcon(standard_icon, option, widget);
  }

private:
  QIcon m_warning_icon;
};

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  a.setApplicationName("QProxyStyles example");

  QMessageBox::warning(nullptr, "", "Without any style");

  qApp->setStyle("fusion");
  QMessageBox::warning(nullptr, "", "With <em>fusion</em> style");

  qApp->setStyle(new MyProxyStyle("fusion"));
  QMessageBox::warning(nullptr, "", "With <em>fusion</em> proxy style");

  return 0;
}
