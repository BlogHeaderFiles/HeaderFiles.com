#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace {
  QStringList splitSearchString(QString pattern)
  {
    // Change all possible delimiters with spaces
    pattern.replace(QRegExp("[.,;:]+"), " ");
  
    return pattern.split(' ', QString::SkipEmptyParts);    
  }
}

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  
  setStyleSheet(R"(
                QListView, QLineEdit {
                  border: 1px solid #dddddd;
                }
                QListView {
                  alternate-background-color: #dddddd;
                }
                )");
  
  ui->listWidget->setFrameShape(QListWidget::NoFrame);
  ui->listWidget->addItem("Denis Ritchie");
  ui->listWidget->addItem("Bill Gates");
  ui->listWidget->addItem("Steve Jobs");
  ui->listWidget->addItem("Linus Torvald");
  ui->listWidget->addItem("Haavard Nord");
  ui->listWidget->addItem("Eirik Chambe-Eng");
  ui->listWidget->sortItems();
  ui->listWidget->setAlternatingRowColors(true);
  
  ui->txtSearch->setPlaceholderText("Search...");
  ui->txtSearch->setFixedHeight(24);
  ui->txtSearch->setClearButtonEnabled(true);
  //connect(ui->txtSearch, &QLineEdit::textChanged, this, &MainWindow::searchExact);
  connect(ui->txtSearch, &QLineEdit::textChanged, this, &MainWindow::searchByTokens);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::searchExact(const QString& text)
{
  for (int ii = 0; ii < ui->listWidget->count(); ++ii) {
    const bool matches = ui->listWidget->item(ii)->text().contains(text, Qt::CaseInsensitive);
    ui->listWidget->item(ii)->setHidden(!matches);
  }
}

void MainWindow::searchByTokens(const QString& text)
{
  const auto tokens = splitSearchString(text);
  
  for (int ii = 0; ii < ui->listWidget->count(); ++ii) {
    bool matched = true;
    for (const auto& token : tokens) {
      if (!ui->listWidget->item(ii)->text().contains(token, Qt::CaseInsensitive)) {
        matched = false; // must contain ALL tokens
        break;
      }
    }
    ui->listWidget->item(ii)->setHidden(!matched);
  }
}
