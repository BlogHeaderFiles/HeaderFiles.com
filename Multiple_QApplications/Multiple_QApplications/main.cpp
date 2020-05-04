#include <QtCore>
#include <qapplication.h>
#include <qpalette.h>

QTranslator tr1;

class MyObject : public QObject {
public:
  explicit MyObject(QObject *parent) : QObject(parent) {
    qDebug() << "****" << __FUNCTION__ << this->parent();
  }
  ~MyObject() { qDebug() << "****" << __FUNCTION__ << parent(); }
};

void testTranslators(QApplication& a)
{
  qDebug() << qApp->removeTranslator(&tr1); // false if the translator is not installed
  a.installTranslator(&tr1); // it is installed in the latest instance (as if called from qApp)
  qDebug() << qApp->removeTranslator(&tr1); // false if the translator is not installed
}

void oneQApplication(int argc, char* argv[])
{
  qDebug() << __FUNCTION__;

  QApplication a1(argc, argv);
  a1.setApplicationName("a1");
  a1.installTranslator(&tr1);
  qDebug() << qApp << &a1;
  qDebug() << "a1.applicationName() =" << a1.applicationName();

  // qApp == &a1
  QObject::connect(&a1, &QCoreApplication::aboutToQuit, []() { qDebug() << "aboutToQuit from a1!"; });
  QTimer::singleShot(2000, &a1, &QCoreApplication::quit); // as if connected to latest qApp

  testTranslators(a1);

  new MyObject(qApp);

  qApp->exec();
  qDebug() << "-----";
}

void twoQApplications(int argc, char* argv[])
{
  qDebug() << __FUNCTION__;

  QApplication a1(argc, argv);
  a1.setApplicationName("a1");
  a1.installTranslator(&tr1);
  qDebug() << qApp << &a1;
  qDebug() << "a1.applicationName() =" << a1.applicationName();

  // qApp == &a1
  QObject::connect(&a1, &QCoreApplication::aboutToQuit, []() { qDebug() << "aboutToQuit from a1!"; });
  QTimer::singleShot(2000, &a1, &QCoreApplication::quit); // as if connected to latest qApp

  qApp->setStyleSheet("QLineEdit{}");
  qDebug() << "qApp->styleSheet() = " << qApp->styleSheet();

  const auto group = QPalette::Active;
  const auto role = QPalette::Text;
  auto palette = qApp->palette();
  qDebug() << "qApp->palette before:" << palette.color(group, role).name();

  palette.setColor(group, role, "#123456");
  qDebug() << "new palette:" << palette.color(group, role).name();
  qApp->setPalette(palette);
  qDebug() << "qApp->palette after:" << qApp->palette().color(group, role).name();

  new MyObject(qApp);

  do { // limite scope of second application
    QApplication a2(argc, argv);
    a2.setApplicationName("a2");
    qDebug() << qApp << &a1 << &a2;
    qDebug() << "a2.applicationName() =" << a2.applicationName();
    qDebug() << "a1.applicationName() =" << a1.applicationName(); // as if called from qApp
    qDebug() << "qApp->applicationName() =" << qApp->applicationName();
    qDebug() << "qApp->styleSheet() = " << qApp->styleSheet();
    qDebug() << "qApp->palette after:" << qApp->palette().color(group, role).name();
    QObject::connect(&a2, &QCoreApplication::aboutToQuit, []() { qDebug() << "aboutToQuit from a2!"; });

    testTranslators(a1);

    new MyObject(qApp);

    qApp->exec();
  } while (false);

  qDebug() << qApp << &a1;

  a1.installTranslator(&tr1);

  qDebug() << "-----";
}

int main(int argc, char* argv[])
{
  oneQApplication(argc, argv);
  twoQApplications(argc, argv);

  return 0;
}
