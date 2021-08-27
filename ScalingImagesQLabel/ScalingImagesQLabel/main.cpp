#include "ScalingImagesQLabel.h"
#include <qapplication.h>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ScalingImagesQLabel w;
  w.show();
  return a.exec();
}
