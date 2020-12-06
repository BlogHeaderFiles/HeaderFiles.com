template<class M>
struct qmap_wrapper
{
  M &map;

  explicit qmap_wrapper(M &map_) : map(map_) {}

  auto begin() { return map.keyValueBegin(); }
  auto begin() const { return map.constKeyValueBegin(); }
  auto end() { return map.keyValueEnd(); }
  auto end() const { return map.constKeyValueEnd(); }
};
