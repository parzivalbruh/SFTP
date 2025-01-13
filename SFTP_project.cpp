#include "../Headers.h"
using namespace std;

int main()
{
    std::string fileName;
    std::string filePath;
    std::cout << "pls enter file path\n";
    std::cin >> filePath;
    std::cout << "pls enter file name and type\n";
    std::cin >> fileName;
    std::cout << filePath + fileName << endl;
    File f1 = copyFileObject(fileName, filePath);
    f1.ToString();
}
