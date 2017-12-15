#include "khash.hh"

#define BLACK_TEXT "\e[30;1m"
#define RED_TEXT "\e[31;1m"
#define GREEN_TEXT "\e[32;1m"
#define YELLOW_TEXT "\e[33;1m"
#define BLUE_TEXT "\e[34;1m"
#define BLACK_BACK "\e[40;1m"
#define DEFAULT "\e[0m"

int main(int argc, char* argv[])
{

    if (argc == 4) {
        std::string option = std::string(argv[1]);
        if (option == "e") {
            KalousedHash kh(argv[2]);
            std::cout << YELLOW_TEXT << "Make sure to save the MD5." << DEFAULT << std::endl;
            std::cout << "MD5 : " << BLACK_BACK << BLUE_TEXT << kh.getMD5() << DEFAULT << std::endl;
            kh.encrypt(argv[3]);
            std::cout << GREEN_TEXT << "Successfully performed!" << DEFAULT << std::endl;
            std::cout << GREEN_TEXT << "Khash saved in the file '" << argv[3] << "'." << DEFAULT << std::endl;
        } else if (option == "r") {
            std::string fName = argv[2];
            std::string mSum = argv[3];
            KalousedHash::recover(fName, mSum);
            std::cout << GREEN_TEXT << "Successfully performed!" << DEFAULT << std::endl;
            std::cout << GREEN_TEXT << "Original file saved in'" << (fName + "_out") << "' if your hash was correct." << DEFAULT << std::endl;
        } else {
            std::cout << RED_TEXT << "Invalid option '" << option << "'." DEFAULT << std::endl;
            return 1;
        }
        return 0;
    } else {
        std::cout << "Invalid number of arguments (expected 3).";
        return 1;
    }

    // std::cout << "This is your HexMap:" << std::endl;
    // kh.printHexMap();
    // std::cout << std::endl;

    // std::ifstream file("KallousHash.txt", std::ios::binary);
    // std::string encode = StringUtils::base64_encode(file);

    // StringUtils::base64_decode(encode, "KallousHashDecoded.txt");
    // std::cout << StringUtils::md5_sum("KallousHashDecoded.txt");
}
