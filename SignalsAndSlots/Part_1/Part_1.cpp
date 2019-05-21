#include "Part_1.h"
#include <qdebug.h>
#include <qmessagebox.h>

Part_1::Part_1(QWidget* parent)
  : QMainWindow(parent),
    m_status_label(new QLabel())
{
  qDebug() << __FUNCTION__ << "{";

  ui.setupUi(this);

  ui.statusBar->addWidget(m_status_label);

  connect(ui.btnShowMessage, SIGNAL(clicked()), this, SLOT(showMessage()));
  // 'printMessage' is a method but not a slot
  connect(ui.btnShowMessage, SIGNAL(clicked()), SLOT(printMessage()));
  // typos
  connect(ui.btnShowMessage, SIGNAL(clicked()), SLOT(showMEssage()));
  connect(ui.btnShowMessage, SIGNAL(cliqued()), SLOT(showMessage()));

  // 'this' is optional
  // A signal can be connected to the same slot many times
  connect(ui.btnShowMessages, SIGNAL(clicked()), this, SLOT(showMessage()));
  connect(ui.btnShowMessages, SIGNAL(clicked()), SLOT(showMessage()));

  // 'clicked' has a boolean argument, omitted here
  connect(ui.btnChangeStatusBar, SIGNAL(clicked()), SLOT(changeStatusBar()));

  connect(ui.btnDisconnect, SIGNAL(clicked()), SLOT(onDisconnect()));

  connect(ui.actionAction, SIGNAL(triggered()), &m_object, SIGNAL(signalEmitted()));
  connect(ui.actionToggle, SIGNAL(toggled(bool)), &m_object, SLOT(foobar(bool)));
  connect(ui.actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));

  connect(&m_object, SIGNAL(signalEmitted()), SLOT(onObjectSignal()));

  qDebug() << "}";
}

void Part_1::showMessage()
{
  qDebug() << __FUNCTION__ << (sender() ? sender()->objectName() : "<no sender>") << "{";

  qDebug() << "  Calling printMessage...";
  printMessage();
  QMessageBox::information(this, "", __FUNCTION__);

  qDebug() << "}";
}

void Part_1::changeStatusBar(const QString& label)
{
  qDebug() << __FUNCTION__ << (sender() ? sender()->objectName() : "<no sender>") << "{";

  m_status_label->setText(label);

  qDebug() << "}";
}

void Part_1::onDisconnect()
{
  qDebug() << __FUNCTION__ << (sender() ? sender()->objectName() : "<no sender>") << "{";

  qDebug() << "  Disconnecting" << ui.btnShowMessage->text();
  // disconnect returns false if no such connection existed
  qDebug() << "   " << ui.btnShowMessage->disconnect(SIGNAL(clicked()));

  qDebug() << "}";
}

void Part_1::printMessage()
{
  qDebug() << __FUNCTION__ << (sender() ? sender()->objectName() : "<no sender>") << "{";
  qDebug() << "  Hello world!";
  qDebug() << "}";
}

void Part_1::onObjectSignal()
{
  qDebug() << __FUNCTION__ << (sender() ? sender()->objectName() : "<no sender>") << "{";

  qDebug() << "}";
}
