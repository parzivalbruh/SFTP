#pragma once
#include <iostream>
#include <vector>
#include <queue>


class Chunk {
private:
    size_t chunkID;
    std::vector<char> encryptedData;
    std::string fileName;
    std::vector<char> chunkHash;

public:

    Chunk(const size_t id, const std::vector<char>& ED, const std::string& FN, const std::vector<char>& CH)
        : chunkID(id), encryptedData(ED), fileName(FN), chunkHash(CH) {}

    size_t getChunkID() const { return chunkID; }

    const std::vector<char>& getEncryptedData() const { return encryptedData; }

    const std::string& getFileName() const { return fileName; }

    const std::vector<char>& getChunkHash() const { return chunkHash; }

    void ToString();
};

class File {
private:
    size_t fileSize;
    std::vector<char> fileHash;
    std::string fileName;
    std::string fileType;
    std::queue<Chunk> chunks;
public:
    File(size_t size, const std::vector<char>& hash, const std::string& name, const std::string& type, std::queue<Chunk> c);

    size_t getFileSize() const;
    const std::vector<char>& getFileHash() const;
    const std::string& getFileName() const;
    const std::string& getFileType() const;
    const std::queue<Chunk>& getChunks() const;

    void setFileSize(size_t size);
    void setFileHash(const std::vector<char>& hash);
    void setFileName(const std::string& name);
    void setFileType(const std::string& type);
    void ToString();
};

File copyFileObject(const std::string& fileName, const std::string& filePath);
void createNewFile(File f1, const std::string& dp);
