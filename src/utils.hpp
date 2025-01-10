#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <vector>
#include <string>

namespace cpph
{
    std::vector<std::string> splitString(std::string str, std::string delimiter);
    std::vector<std::string> splitString(const std::string& str, const char delimiter);
    std::string replaceString(std::string_view str, std::string_view replace, std::string_view with);
    std::string toLower(const std::string& str);
    bool contains(const std::string_view str, const std::string& substr);
}

#endif // __UTILS_HPP__