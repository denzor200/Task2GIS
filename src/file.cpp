#include "file.h"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

std::vector<uint8_t> file::ReadAllBytes(const std::string& path)
{
    std::vector<uint8_t> buffer;
    std::ifstream ifs(std::filesystem::u8path(path), std::ios::binary);
    if (!ifs.is_open())
        throw std::runtime_error("Can't open '" + path + "'");

    ifs.seekg(0, ifs.end);
    size_t length = static_cast<size_t>(static_cast<std::streamoff>(ifs.tellg()));
    ifs.seekg(0, ifs.beg);

    buffer.resize(length);
    ifs.read(reinterpret_cast<char*>(buffer.data()), buffer.size());

    return buffer;
}

std::string file::ReadAllText(const std::string& path)
{
    return ReadAllTextAsStream(path).str();
}

std::stringstream file::ReadAllTextAsStream(const std::string& path)
{
    std::stringstream ss;
    size_t offset = 0;
    auto buffer = ReadAllBytes(path);

    // Отбрасываем преамбулу если UTF-8
    if (buffer.size() >= 3 && buffer[0] == 0xef && buffer[1] == 0xbb && buffer[2] == 0xbf)
        offset = 3;

    ss.write(reinterpret_cast<const char*>(buffer.data() + offset), buffer.size() - offset);

    return ss;
}
