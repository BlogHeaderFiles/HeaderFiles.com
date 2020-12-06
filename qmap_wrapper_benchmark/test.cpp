// +
#include "test.h"
#include "qmap_wrapper.h"
#include <qtest.h>

namespace
{
  template<class T = QMap<QString, int>>
  T generateMapStringKey()
  {
    T map;

    for (size_t ii = 0; ii < 1'000'000; ++ii) { map[std::to_string(ii).c_str()] = ii; }

    return map;
  }
}

void Test::qmap_values()
{
  auto map = generateMapStringKey();

  int sum = 0;
  QBENCHMARK
  {
    for (const auto &value : map) { sum += value; }
  }
}

void Test::qmap_keys()
{
  auto map = generateMapStringKey();

  int sum = 0;
  QBENCHMARK
  {
    for (const auto &key : map.keys()) { sum += map[key]; }
  }
}

void Test::qmap_const_keys()
{
  auto map = generateMapStringKey();

  int sum = 0;
  QBENCHMARK
  {
    for (const auto &key : qAsConst(map).keys()) { sum += map[key]; }
  }
}

void Test::qmap_tostdmap()
{
  auto map = generateMapStringKey();

  int sum = 0;
  QBENCHMARK
  {
    for (const auto &it : map.toStdMap()) { sum += it.second; }
  }
}

void Test::qmap_iterator()
{
  auto map = generateMapStringKey();

  int sum = 0;
  QBENCHMARK
  {
    for (auto it = map.begin(); it != map.end(); ++it) { sum += it.value(); }
  }
}

void Test::qmap_wrapper()
{
  auto map = generateMapStringKey();

  int sum = 0;
  QBENCHMARK
  {
    for (const auto it : ::qmap_wrapper{map}) { sum += it.second; }
  }
}
