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
    'v'
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

    bool __locked = false;

    void __buildUnunseds()
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

public:
    KalousedHash(std::string& md5sum)
        : md5sum(md5sum)
    {
        __buildUnunseds();
    };
    KalousedHash(std::string&& md5sum)
        : md5sum(md5sum)
    {
        __buildUnunseds();
    };

    void deleteFromHeap(char value)
    {
        HexDigit __pivot(0, value);
        auto searchIt = (std::lower_bound(hexMiscChar.begin(), hexMiscChar.end(), __pivot));
        auto search = searchIt - hexMiscChar.begin();
        if (search >= 0 && search < hexMiscChar.size() && hexMiscChar[search].character == value) {
            hexMiscChar.erase(searchIt);
        }
    }

    void printHexMap()
    {
        for (auto& hex : hexMap) {
            std::cout << hex.first << " -> " << hex.second << std::endl;
        }
    }

    void buildHexMap()
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
            deleteFromHeap(toUse);
        }

        for (int i = 0, j = hexChain.size() - 1; i <= j; i++) {
            if (i == j) {
                hexMap.insert({ hexChain[i], hexChain[0] });
                inverseHexMap.insert({ hexChain[0], hexChain[i] });
                break;
            }
            hexMap.insert({ hexChain[i], hexChain[i + 1] });
            inverseHexMap.insert({ hexChain[i + 1], hexChain[i] });
        }
    }
};
