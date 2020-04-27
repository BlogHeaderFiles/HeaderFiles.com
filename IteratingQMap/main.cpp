#include <qdebug.h>
#include <map>
#include <qmap.h>

namespace
{
  void iterate_std_map(std::map<QString, int> std_map)
  {
    qDebug() << "# std::map";
    qDebug() << "## Iterators";
    for (auto it = std_map.begin(); it != std_map.end(); ++it) {
      qDebug() << it->first << it->second;
    }

    qDebug() << "## range-for";
    for (auto& elem : std_map) {
      qDebug() << elem.first << elem.second;
    }
  }

  // Credits to bcmpinc https://stackoverflow.com/a/60329987/1485885
  template<class K, class V>
  struct qmap_wrapper {
    QMap<K, V>& map;
    explicit qmap_wrapper(QMap<K, V>& map_) : map(map_) {}
    auto begin() { return map.keyValueBegin(); }
    auto end() { return map.keyValueEnd(); }
  };

  template<class K, class V>
  struct qmap_wrapper_pre510 {
    using qiterator = QKeyValueIterator<K, V, typename QMap<K, V>::iterator>;
    QMap<K, V>& map;
    explicit qmap_wrapper_pre510(QMap<K, V>& map_) : map(map_) {}
    auto begin() { return qiterator(map.begin()); }
    auto end() { return qiterator(map.end()); }
  };

  void iterate_qmap(QMap<QString, int> qmap)
  {
    qDebug() << "# QMap";
    qDebug() << "## Iterators";
    for (auto it = qmap.begin(); it != qmap.end(); ++it) {
      qDebug() << it.key() << it.value();
    }

    qDebug() << "## Java-style";
    QMapIterator<decltype(qmap)::key_type, decltype(qmap)::mapped_type> jit(qmap);
    // idem to QMapIterator<QString, int> it(qmap);
    while (jit.hasNext()) {
      jit.next();
      qDebug() << jit.key() << jit.value();
    }

    qDebug() << "## stl-style (since Qt 5.10)";
    for (auto it = qmap.keyValueBegin(); it != qmap.keyValueEnd(); ++it) {
      qDebug() << (*it).first << (*it).second;
      //qDebug() << it->first << it->second; // doesn't work
    }

    qDebug() << "## range-for";
    for (auto& elem : qmap) {
      qDebug() << elem;
    }

    qDebug() << "### Iterate keys";
    for (const auto& key : qmap.keys()) {
      qDebug() << key << qmap[key];
    }

    qDebug() << "### Convert to std::map";
    for (auto& elem : qmap.toStdMap()) {
      qDebug() << elem.first << elem.second;
    }

    qDebug() << "## range-for (>=5.10)";
    for (auto elem : qmap_wrapper(qmap)) {
      qDebug() << elem.first << elem.second;
    }

    qDebug() << "## range-for (<5.10)";
    for (auto elem : qmap_wrapper_pre510(qmap)) {
      qDebug() << elem.first << elem.second;
    }
  }
}

int main()
{
  iterate_std_map({{"one", 1}, {"two", 2}, {"three", 3}});
  iterate_qmap({{"one", 1}, {"two", 2}, {"three", 3}});
}
