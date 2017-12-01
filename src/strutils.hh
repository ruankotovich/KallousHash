#include <string>
#include <vector>

namespace StringUtils {
static std::vector<int> findLocation(std::string sample, char findIt)
{
    std::vector<int> characterLocations;
    for (int i = 0; i < sample.size(); i++)
        if (sample[i] == findIt)
            characterLocations.push_back(i);

    return characterLocations;
}

static std::vector<std::pair<int, char>> findLocationAndNextChar(std::string sample, char findIt)
{
    std::vector<std::pair<int, char>> characterLocations;
    for (int i = 0; i < sample.size(); i++)
        if (sample[i] == findIt) {
            int ip1 = i + 1;
            characterLocations.emplace_back(i, ip1 != sample.size() ? sample[ip1] : '\0');
        }

    return characterLocations;
}
}
