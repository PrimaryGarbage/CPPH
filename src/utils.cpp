#include "utils.hpp"
#include <string.h>

namespace cpph
{
    std::vector<std::string> splitString(std::string str, std::string delimiter)
    {
        std::vector<std::string> strings;
        size_t pos = 0, prevPos = 0;
        while ((pos = str.find(delimiter, pos + 1)) != std::string::npos)
        {
            strings.emplace_back(std::move(str.substr(prevPos, pos)));
            prevPos = pos;
        }
        strings.push_back(std::move(str.substr(prevPos + delimiter.length())));

        return strings;
    }

    std::vector<std::string> splitString(const std::string& str, const char delimiter)
    {
        std::vector<std::string> strings;
        int pos = -1, prevPos = -1;
        while ((pos = str.find(delimiter, pos + 1)) != std::string::npos)
        {
            std::string substr = str.substr(prevPos, pos - ++prevPos);
            if (!substr.empty()) strings.emplace_back(std::move(substr));
            prevPos = pos;
        }
        strings.push_back(std::move(str.substr(++prevPos)));

        return strings;
    }

    std::string toLower(const std::string& str)
    {
        std::string lowerStr;
        lowerStr.reserve(str.size());
        for (const char& c : str) lowerStr.push_back(std::tolower(c));
        return lowerStr;
    }
    
    bool contains(const std::string& str, const std::string& substr) 
    {
        size_t substrLength = substr.length();
        if(str.length() < substr.length()) return false;

        size_t searchIdx = 0;
        for(size_t i = 0; i < str.length(); ++i)
        {
            if(str[i] == substr[searchIdx]) ++searchIdx;
            if(searchIdx == substrLength) return true;
        }
        return false;
    }

    std::string replaceString(std::string_view str, std::string_view replace, std::string_view with) 
    {
        std::string result(str);
        size_t size = replace.length();
        size_t pos = 0;
        while((pos = result.find(replace, pos)) != std::string::npos)
        {
            result.replace(pos, size, with);
            pos += with.length();
        }
        return std::move(result);
    }

    std::string toString(const char* array[], size_t length)
    {
        size_t resultStringLength = 0;
        for(size_t i = 0; i < length; ++i)
        {
            if(array[i] == nullptr) continue;
            resultStringLength += strlen(array[i]) + 2;
        }

        std::string result;
        result.reserve(resultStringLength);

        for(size_t i = 0; i < length; ++i)
        {
            result.append(array[i]);
            result.append(", ");
        }

        return result.substr(0, result.length() - 2);
    }
}