#include <iostream>
#include <string>
#include <cstring>

bool is_palindrome(const char* str, size_t len)
{
    if (len == 0) return true;
    for (size_t ii = 0, jj = len - 1; ii < jj; ++ii, --jj) {
        if (str[ii] != str[jj]) return false;
    }
    return true;
}

template<typename T>
bool is_palindrome(const T& str)
{
    return std::equal(begin(str), end(str), rbegin(str));
}

template<size_t N>
bool is_palindrome(const char (&str)[N])
{
    return is_palindrome(str, N - 1);
}

template<size_t N>
void test(const char (&txt)[N])
{
    const std::string str(txt);
    std::cout << str << " is palindrome (const char*): " << is_palindrome(str.c_str(), str.size()) << "\n";
    std::cout << str << " is palindrome (std::string): " << is_palindrome(str) << "\n";
    std::cout << str << " is palindrome (const char[]): " << is_palindrome(txt) << "\n";
}

int main()
{
    std::cout << std::boolalpha;
    
    test("");
    test("ana");
    test("animal lamina");
    test("aaaa");
    test("Ojo");
    test("HeaderFiles");
}
