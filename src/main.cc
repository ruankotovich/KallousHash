#include "khash.hh"

int main(int argc, char* argv[])
{

    if (argc == 4) {
        std::string option = std::string(argv[1]);
        if (option == "e") {
            KalousedHash kh(argv[2]);
            std::cout << "Make sure to annotate the MD5 and DO NOT LOSE IT!" << std::endl;
            std::cout << "MD5 : " << kh.getMD5() << std::endl;
            kh.encrypt(argv[3]);
            std::cout << "Successfully performed!" << std::endl;
            std::cout << "Khash saved in the file '" << argv[2] << "'." << std::endl;
        } else if (option == "r") {
            std::string fName = argv[2];
            std::string mSum = argv[3];
            KalousedHash::recover(fName, mSum);
            std::cout << "Successfully performed!" << std::endl;
        } else {
            std::cout << "Invalid option '" << option << "'.";
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
