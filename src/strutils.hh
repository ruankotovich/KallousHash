#include "base64_rfc4648.hpp"
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

namespace StringUtils {
static std::vector<int> findLocation(std::string& sample, char findIt)
{
    std::vector<int> characterLocations;
    for (int i = 0; i < sample.size(); i++)
        if (sample[i] == findIt)
            characterLocations.push_back(i);

    return characterLocations;
}

static std::vector<std::pair<int, char>> findLocationAndNextChar(std::string& sample, char findIt)
{
    std::vector<std::pair<int, char>> characterLocations;
    for (int i = 0; i < sample.size(); i++)
        if (sample[i] == findIt) {
            int ip1 = i + 1;
            characterLocations.emplace_back(i, ip1 != sample.size() ? sample[ip1] : '\0');
        }

    return characterLocations;
}

static std::string base64_encode(std::ifstream& fileStream)
{
    std::vector<char> buffer((std::istreambuf_iterator<char>(fileStream)), (std::istreambuf_iterator<char>()));
    return cppcodec::base64_rfc4648::encode(&buffer[0], buffer.size());
}

static void base64_decode(std::string& base64String)
{
    std::string& decoding = cppcodec::base64_rfc4648::decode<std::string>(base64String, base64String.size());
}
}
