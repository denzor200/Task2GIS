#ifndef FILE_H
#define FILE_H

#include <sstream>
#include <string>
#include <vector>

/**
 * @class file
 * @brief утилиты для работы с файлами
 */
class file {
public:
    /**
     * @brief Открывает текстовый файл, считывает весь текст файла в строку и затем закрывает файл.
     * @param path Файл, открываемый для чтения.
     * @return Строка, содержащая весь текст файла.
     */
    static std::string ReadAllText(const std::string& path);

    /**
     * @brief Открывает текстовый файл, считывает весь текст файла в std::stringstream и затем закрывает файл.
     * @param path Файл, открываемый для чтения.
     * @return Стрим, содержащий весь текст файла.
     */
    static std::stringstream ReadAllTextAsStream(const std::string& path);

    /**
     * @brief Открывает файл, считывает все байты файла и затем закрывает файл.
     * @param path Файл, открываемый для чтения.
     * @return Контейнер, содержащий все байты из файла
     */
    static std::vector<uint8_t> ReadAllBytes(const std::string& path);
};

#endif // FILE_H
