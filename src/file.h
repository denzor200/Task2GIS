#ifndef FILE_H
#define FILE_H

#include <sstream>
#include <string>
#include <vector>

// TODO: docs

class file {
public:
    static std::string ReadAllText(const std::string& path);
    static std::vector<uint8_t> ReadAllBytes(const std::string& path);
    static std::stringstream ReadAllTextAsStream(const std::string& path);
};

#endif // FILE_H
