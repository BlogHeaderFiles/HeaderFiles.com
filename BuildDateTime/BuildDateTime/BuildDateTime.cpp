#include <boost/date_time.hpp>
#include <iostream>
#include <string>

using namespace std::string_literals;

namespace
{
  std::string getFormattedBuildDatetime(const std::string &format)
  {
    // Build timestamp, uses Boost to allow conversion from the compiler
    // __TIMESTAMP__ string to a custom format
    namespace bt = boost::posix_time;

    // Normalize timestamp
    std::string timestamp(__TIMESTAMP__);
    const auto it_dblspace = timestamp.find("  ");
    if (it_dblspace != std::string::npos) { // replace day with leading space by
                                            // day with leading zero
      timestamp.replace(it_dblspace, 2, " 0");
    }

    // Extract individual components
    std::istringstream is(timestamp);
    const std::locale ts_locale(std::locale::classic(), new bt::time_input_facet("%a %b %d %H:%M:%S %Y"));
    is.imbue(ts_locale);
    bt::ptime pt;
    is >> pt;

    // Format output
    std::ostringstream os;
    os.imbue(std::locale(std::locale::classic(), new bt::time_facet(format.c_str())));
    os << pt;

    return os.str();
  }
}

int main()
{
  std::cout << "__TIMESTAMP__ " << __TIMESTAMP__ << '\n';
  std::cout << "__DATE__ " << __DATE__ << '\n';
  std::cout << "__TIME__ " << __TIME__ << '\n';
  std::cout << "Formatted: " << getFormattedBuildDatetime("%Y/%m/%d %H:%M:%S") << '\n';

  return 0;
}
