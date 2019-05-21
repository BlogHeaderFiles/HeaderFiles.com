#include "Part_2.h"
#include <qdebug.h>
#include <qmessagebox.h>

Part_2::Part_2(QWidget* parent)
  : QMainWindow(parent),
    m_status_label(new QLabel())
{
  qDebug() << __FUNCTION__ << "{";

  ui.setupUi(this);

  ui.statusBar->addWidget(m_status_label);

  connect(ui.btnShowMessage, &QPushButton::clicked, this, &Part_2::showMessage);
  // 'printMessage' is a method but not a slot, but is connectable using Qt 5
  connect(ui.btnShowMessage, &QPushButton::clicked, this, &Part_2::printMessage);
  // These no longer compile using Qt 5 new syntax
  //connect(ui.btnShowMessage, &QPushButton::clicked, this, Part_2::showMEssage);
  //connect(ui.btnShowMessage, &QPushButton::cliqued, this, Part_2::showMessage);

  // A signal can be connected to the same slot many times
  // We can disconnect them independently using the QMetaObject::Connection returned
  m_connections << connect(ui.btnShowMessages, &QPushButton::clicked, this, &Part_2::showMessage);
  m_connections << connect(ui.btnShowMessages, &QPushButton::clicked, this, &Part_2::showMessage);

  // 'this' is not optional in the new syntax
  //connect(ui.btnShowMessages, &QPushButton::clicked, &Part_2::showMessage);

  // Error: Signal and slot arguments are not compatible.
  // 'clicked' has a boolean argument and 'changeStatusBar' a const QString&
  //connect(ui.btnChangeStatusBar, &QPushButton::clicked, this, &Part_2::changeStatusBar);
  // It can be solved using a lambda
  // To disconnect this type of connection we must save the connection
  m_change_status_bar_connection = connect(ui.btnChangeStatusBar, &QPushButton::clicked, [this]() {
    // sender() is null when using a connection to non-member
    qDebug() << __FUNCTION__ << (sender() ? sender()->objectName() : "<no sender>") << "{";

    changeStatusBar();

    qDebug() << "}";
  });

  connect(ui.btnDisconnect, &QPushButton::clicked, this, &Part_2::onDisconnect);

  connect(ui.actionAction, &QAction::triggered, &m_object, &MyObject::signalEmitted);
  // Requires qOverload<...> to choose the correct overload of the method
  connect(ui.actionToggle, &QAction::toggled, &m_object, qOverload<bool>(&MyObject::foobar));
  // No error here: bool can be implicitly converted into an int
  connect(ui.actionToggle, &QAction::toggled, this, &Part_2::onPressed);
  connect(ui.actionQuit, &QAction::triggered, qApp, &QApplication::quit);

  connect(&m_object, &MyObject::signalEmitted, this, &Part_2::onObjectSignal);

  qDebug() << "}";
}

void Part_2::showMessage()
{
  qDebug() << __FUNCTION__ << (sender() ? sender()->objectName() : "<no sender>") << "{";

  qDebug() << "  Calling printMessage...";
  printMessage();
  QMessageBox::information(this, "", __FUNCTION__);

  qDebug() << "}";
}

void Part_2::onPressed(int value)
{
  qDebug() << __FUNCTION__ << (sender() ? sender()->objectName() : "<no sender>") << "{";

  qDebug() << "  'value' =" << value;

  qDebug() << "}";
}

void Part_2::changeStatusBar(const QString& label)
{
  qDebug() << __FUNCTION__ << (sender() ? sender()->objectName() : "<no sender>") << "{";

  m_status_label->setText(label);

  qDebug() << "}";
}

void Part_2::onDisconnect()
{
  qDebug() << __FUNCTION__ << (sender() ? sender()->objectName() : "<no sender>") << "{";

  qDebug() << "  Disconnecting" << ui.btnShowMessage->text();
  // It is possible to mix Qt 4 and Qt 5 syntax:
  qDebug() << "   " << ui.btnShowMessage->disconnect(SIGNAL(clicked()));

  qDebug() << "  Disconnecting" << ui.btnChangeStatusBar->text();
  // Prints true if the connection is active
  qDebug() << "   " << m_change_status_bar_connection;
  // disconnect returns false if no such connection existed
  qDebug() << "   " << disconnect(m_change_status_bar_connection);
  qDebug() << "   " << m_change_status_bar_connection;

  if (!m_connections.isEmpty()) {
    qDebug() << "  Disconnecting one" << ui.btnShowMessages->text();
    // It is possible to mix Qt 4 and Qt 5 syntax:
    qDebug() << "   " << disconnect(m_connections.front());
    m_connections.pop_front();
  } else {
    qDebug() << "  No connections remain for" << ui.btnShowMessages->text();
  }

  qDebug() << "}";
}

void Part_2::printMessage()
{
  qDebug() << __FUNCTION__ << (sender() ? sender()->objectName() : "<no sender>") << "{";
  qDebug() << "  Hello world!";
  qDebug() << "}";
}

void Part_2::onObjectSignal()
{
  qDebug() << __FUNCTION__ << (sender() ? sender()->objectName() : "<no sender>") << "{";

  qDebug() << "}";
}
