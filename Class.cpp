#include "../Headers.h"
using namespace std;

void Chunk :: ToString() {
    std::cout << "id: " << chunkID << endl;
    std::cout << "data: " << "encryptedData" << endl;
    std::cout << "file name: " << fileName << endl;
    std::cout << "chunk hash: " << "chunkHash" << endl;
}

File::File(size_t size, const std::vector<char>& hash, const std::string& name, const std::string& type, std::queue<Chunk> c)
    : fileSize(size), fileHash(hash), fileName(name), fileType(type), chunks(c) {}

size_t File::getFileSize() const {
    return fileSize;
}

const std::vector<char>& File::getFileHash() const {
    return fileHash;
}

const std::string& File::getFileName() const {
    return fileName;
}

const std::string& File::getFileType() const {
    return fileType;
}

const std::queue<Chunk>& File::getChunks() const {
    return chunks;
}

void File::setFileSize(size_t size) {
    fileSize = size;
}

void File::setFileHash(const std::vector<char>& hash) {
    fileHash = hash;
}

void File::setFileName(const std::string& name) {
    fileName = name;
}

void File::setFileType(const std::string& type) {
    fileType = type;
}

void File::ToString() {
    std::cout << "File Name: " << fileName << endl;
    std::cout << "File Type: " << fileType << endl;
    std::cout << "File Size: " << fileSize << " bytes\n";
    std::queue<Chunk> tempChunks = chunks;
    size_t chunkCount = 0;

    while (!tempChunks.empty()) {
        std::cout << "  Chunk " << chunkCount << ":\n";
        tempChunks.front().ToString();
        tempChunks.pop();
        ++chunkCount;
    }
}

File copyFileObject(const std::string& fileName, const std::string& filePath) {

    if (!std::filesystem::exists(filePath + "\\" + fileName)) { //have to change the c++ type to c++17 or higher.
        return File(0, {}, "", "", {});
    }

    std::ifstream file1(filePath + "\\" + fileName, std::ios::binary);

    std::queue<Chunk> chunk;
    std::vector<char> buffer(64 * 1024);
    size_t currentChunk = 0;

    file1.seekg(0, std::ios::end);
    size_t fileSize = file1.tellg();
    file1.seekg(0, std::ios::beg);

    while (file1) {

        file1.read(buffer.data(), buffer.size()); 
        
        std::streamsize bytesRead = file1.gcount();
        if (bytesRead == 0) {
            break; 
        }
        std::vector<char> currentData(buffer.begin(), buffer.begin() + bytesRead);
        Chunk current(currentChunk, currentData, fileName, {'2'});
        chunk.push(current);
        currentChunk++;
    }
    File f1(fileSize, { 2 }, fileName, fileName, chunk);



    return f1;
}

void createNewFile() {
    
}