#include <iostream>
#include <string>
#include <cstring>

bool is_palindrom(const char* str, size_t len)
{
    for (size_t ii = 0, jj = len - 1; ii < jj; ++ii, --jj) {
        if (str[ii] != str[jj]) return false;
    }
    return true;
}

template<typename T>
bool is_palindrom(const T& str)
{
    return std::equal(begin(str), end(str), rbegin(str));
}

template<size_t N>
bool is_palindrom(const char (&str)[N])
{
    return is_palindrom(str, N - 1);
}

template<size_t N>
void test(const char (&txt)[N])
{
    const std::string str(txt);
    std::cout << str << " is palindrom (const char*): " << is_palindrom(str.c_str(), str.size()) << "\n";
    std::cout << str << " is palindrom (std::string): " << is_palindrom(str) << "\n";
    std::cout << str << " is palindrom (const char[]): " << is_palindrom(txt) << "\n";
}

int main()
{
    std::cout << std::boolalpha;
    
    test("ana");
    test("animal lamina");
    test("aaaa");
    test("Ojo");
    test("HeaderFiles");
    
    return 0;
}
