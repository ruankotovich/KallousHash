#include "strutils.hh"
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

const std::vector<char> CHAIN_CHARACTERS = {
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    'a',
    'b',
    'c',
    'd',
    'e',
    'f',
    'g',
    'h',
    'i',
    'j',
    'k',
    'l',
    'm',
    'n',
    'o',
    'p',
    'q',
    'r',
    's',
    't',
    'u',
    'v',
    'w',
    'x',
    'y',
    'z',
    '='
};

struct HexDigit {
    int weight;
    mutable char character;
    HexDigit(int w, char c)
        : weight(w)
        , character(c)
    {
    }
    const bool operator<(const HexDigit& digit) const
    {
        return this->character < digit.character;
    }

    const bool operator()(const HexDigit& digit1, const HexDigit& digit2)
    {
        return digit1.weight > digit2.weight;
    }
};

class KalousedHash {
    std::string md5sum;
    std::map<char, char> hexMap;
    std::map<char, char> inverseHexMap;
    std::vector<char> hexChain;
    std::vector<HexDigit> hexMiscChar;
    std::set<char> usedChar;
    std::ifstream file;

    bool __locked = false;

    static void __buildUnunseds(std::string& md5sum, std::vector<HexDigit>& hexMiscChar)
    {
        int sum = 0;
        int multiplication = 1;

        for (char k : md5sum) {
            sum += k;
            multiplication *= k;
        }

        multiplication %= sum;

        for (char c : CHAIN_CHARACTERS) {
            hexMiscChar.emplace_back((multiplication % c), c);
        }

        std::sort(hexMiscChar.begin(), hexMiscChar.end());
    }

    static void __deleteFromHeap(char value, std::vector<HexDigit>& hexMiscChar)
    {
        HexDigit __pivot(0, value);
        auto searchIt = (std::lower_bound(hexMiscChar.begin(), hexMiscChar.end(), __pivot));
        auto search = searchIt - hexMiscChar.begin();
        if (search >= 0 && search < hexMiscChar.size() && hexMiscChar[search].character == value) {
            hexMiscChar.erase(searchIt);
        }
    }

    void __buildHexMap()
    {

        if (__locked) {
            return;
        }
        __locked = true;

        for (char c : md5sum) {
            char toUse = '\0';

            if (usedChar.find(c) != usedChar.end()) {
                toUse = hexMiscChar.back().character;
                hexMiscChar.pop_back();
            } else {
                toUse = c;
            }

            hexChain.push_back(toUse);
            usedChar.insert(toUse);
            __deleteFromHeap(toUse, hexMiscChar);
        }

        for (int i = 0, j = hexChain.size() - 1; i <= j; i++) {
            if (i == j) {
                hexMap.insert({ hexChain[i], hexChain[0] });
                inverseHexMap.insert({ hexChain[0], hexChain[i] });
                break;
            }
            int ip1 = i + 1;
            hexMap.insert({ hexChain[i], hexChain[ip1] });
            inverseHexMap.insert({ hexChain[ip1], hexChain[i] });
        }
    }

public:
    KalousedHash(std::string&& filename)
        : md5sum(StringUtils::md5_sum(filename.c_str()))
        , file(filename, std::ios::binary)
    {
        __buildUnunseds(md5sum, hexMiscChar);
        __buildHexMap();
    };

    void printHexMap()
    {
        for (auto& hex : hexMap) {
            std::cout << hex.first << " -> " << hex.second << std::endl;
        }
    }

    std::string getMD5()
    {
        return md5sum;
    }

    static void recover(std::string& filebase64, std::string& md5)
    {

        std::map<char, char> inverseHexMap;
        std::set<char> usedChar;
        std::vector<HexDigit> hexMiscChar;
        std::vector<char> hexChain;
        std::string outputBase64;
        std::ifstream ifs(filebase64);
        std::string base64((std::istreambuf_iterator<char>(ifs)),
            (std::istreambuf_iterator<char>()));

        __buildUnunseds(md5, hexMiscChar);

        for (char c : md5) {
            char toUse = '\0';

            if (usedChar.find(c) != usedChar.end()) {
                toUse = hexMiscChar.back().character;
                hexMiscChar.pop_back();
            } else {
                toUse = c;
            }

            hexChain.push_back(toUse);
            usedChar.insert(toUse);
            __deleteFromHeap(toUse, hexMiscChar);
        }

        for (int i = 0, j = hexChain.size() - 1; i <= j; i++) {
            if (i == j) {
                inverseHexMap.insert({ hexChain[0], hexChain[i] });
                break;
            }
            int ip1 = i + 1;
            inverseHexMap.insert({ hexChain[ip1], hexChain[i] });
        }

        for (auto c : base64) {
            auto mapIt = inverseHexMap.find(c);
            outputBase64 += mapIt != inverseHexMap.end() ? mapIt->second : c;
        }

        StringUtils::base64_decode(outputBase64, filebase64 + "_out");
    }

    void encrypt(std::string&& outputFilename)
    {
        std::string fileBase64 = StringUtils::base64_encode(file);
        std::string outputBase64;
        std::ofstream ofs(outputFilename, std::ofstream::out);
        std::transform(fileBase64.begin(), fileBase64.end(), fileBase64.begin(), ::tolower);

        for (char c : fileBase64) {
            auto mapIt = hexMap.find(c);
            outputBase64 += mapIt != hexMap.end() ? mapIt->second : c;
        }

        ofs << outputBase64;
        ofs.close();
    }
};
