#include <iostream>
#include <string>

struct TrueValue
{
  const std::string true_str;
};
struct FalseValue
{
  const std::string false_str;
};

template<typename T>
bool string2bool(const std::string &str, T &&value)
{
  constexpr bool is_true_exp = std::is_same_v<T, TrueValue>;
  constexpr bool is_false_exp = std::is_same_v<T, FalseValue>;

  if constexpr (is_true_exp) return str == value.true_str;
  if constexpr (is_false_exp) return str != value.false_str;

  static_assert(is_true_exp || is_false_exp, "'value' must be of either TrueValue or FalseValue types");
}

int main()
{
  std::cout << string2bool("yes", TrueValue{"yes"}) << '\n';
  std::cout << string2bool("no", TrueValue{"yes"}) << '\n';
  std::cout << string2bool("yes", FalseValue{"no"}) << '\n';
  std::cout << string2bool("no", FalseValue{"no"}) << '\n';
  //std::cout << string2bool("no", "maybe") << '\n';
}
