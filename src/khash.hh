#include "strutils.hh"
#include <map>
#include <iostream>
#include <set>
#include <vector>

struct HexElement {
  char element;
  std::vector<char> forwardElement;
  unsigned posHash;

  HexElement(char character)
  : element(character), posHash(0)
  {
  }

  bool operator<(HexElement& element)
  {
    return this->element < element.element;
  }
};

struct KalousedHash {
  std::map<char, HexElement> hexElements;
  std::set<unsigned> visitedLocations;
  std::string& md5sum;
  KalousedHash(std::string& md5sum)
  : md5sum(md5sum){};
  KalousedHash(std::string&& md5sum)
  : md5sum(md5sum){};

  void printKHash(){
    for(auto hElement : hexElements){
      auto cur = hElement.second;
      std::cout << '('<< cur.posHash << ')' << " # " << cur.element <<"->[";
      for(auto index : cur.forwardElement){
        std::cout << index << ',';
      }

      std::cout << "] # {" << cur.forwardElement.size() << "}\n";
    }
  }

  void buildHexMap()
  {

    if(_locked){
      return;
    }

    _locked = true;

    for (unsigned i = 0; i < md5sum.size(); i++) {

      if (visitedLocations.find(i) != visitedLocations.end()) {
        continue;
      }

      auto foundLocations = StringUtils::findLocationAndNextChar(md5sum, md5sum[i]);

      auto &curHexElement = hexElements.emplace(md5sum[i], md5sum[i]).first->second;

      for (auto pos : foundLocations) {
        visitedLocations.insert(pos.first);
        curHexElement.posHash+=pos.first;
        if (pos.second != '\0') {
          curHexElement.forwardElement.push_back(pos.second);
        }
      }
    }
    visitedLocations.clear();
  }
private:
  bool _locked = false;
};
