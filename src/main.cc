#include "khash.hh"

int main()
{
    KalousedHash kh("9a3051eb1768badfb1412a2f35ff9b56");
    kh.buildHexMap();
    // kh.printHexMap();
    std::ifstream file("KalousedHash.txt", std::ios::binary);
    std::cout << StringUtils::base64_encode(file);
}
