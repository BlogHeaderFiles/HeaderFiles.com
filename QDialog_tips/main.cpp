#include <qapplication.h>
#include <qdebug.h>
#include <qdialog.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qmessagebox.h>

bool basicDialog()
{
  QDialog dlg;
  
  dlg.setWindowFlag(Qt::WindowContextHelpButtonHint, false);
  dlg.setWindowFlag(Qt::MSWindowsFixedSizeDialogHint, true);
  
  auto layout = new QVBoxLayout();
  layout->addWidget(new QLabel("This is a dialog."));
  
  auto h_layout = new QHBoxLayout();
  h_layout->addStretch();
  auto ok_button = new QPushButton("OK");
  QObject::connect(ok_button, &QPushButton::clicked, &dlg, &QDialog::accept);
  h_layout->addWidget(ok_button);
  auto cancel_button = new QPushButton("Cancel");
  QObject::connect(cancel_button, &QPushButton::clicked, &dlg, &QDialog::reject);
  h_layout->addWidget(cancel_button);
  layout->addLayout(h_layout);
  
  dlg.setLayout(layout);
  
  return dlg.exec() == QDialog::Accepted;
}

void messageBoxes()
{
  qDebug() << "QMessageBox" << QMessageBox::information(nullptr, "", "Using application name");
  qDebug() << "QMessageBox" << QMessageBox::information(nullptr, "Another title", "Custom title");
  qDebug() << "QMessageBox" << QMessageBox::question(nullptr, "Title", "Yes or no?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);  
}

void customMessageBox()
{
  QMessageBox msg_box(QMessageBox::Question, "Poll", "What do you think about HeaderFiles?",
                      QMessageBox::Yes | QMessageBox::No);
  msg_box.setButtonText(QMessageBox::Yes, "HeaderFiles rules!");
  msg_box.setButtonText(QMessageBox::No, "I <3 HF");
  qDebug() << __FUNCTION__ << (msg_box.exec() == QMessageBox::Yes);
}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  qApp->setApplicationName("HeaderFiles");
  
  qDebug() << "basicDialog" << basicDialog();
  messageBoxes();
  customMessageBox();
  
  return 0;
}
