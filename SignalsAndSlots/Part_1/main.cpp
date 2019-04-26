#include "Part_1.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  Part_1 w;

  // Call method and slot out of signal
  w.printMessage();
  w.showMessage();

  w.show();

  return a.exec();
}
