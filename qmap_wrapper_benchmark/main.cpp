#include "qmap_wrapper.h"
#include <qdebug.h>
#include <qmap.h>
#include <qtest.h>
#include "test.h"

int main(int argc, char *argv[])
{
  // Basic sample
  QMap<int, double> powers10 = {{0, 1.0}, {1, 10.0}, {2, 100.0}, {3, 1000.0}};

  for (const auto& [key, value] : qmap_wrapper{powers10}) { qDebug() << key << "->" << value; }

  // Test
  Test test;
  QTest::qExec(&test, argc, argv);

  return 0;
}
