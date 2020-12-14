#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>

class tree;

/**
 * @class application
 * @brief Класс отвечает за основную логику приложения.
 */
class application {
public:
    /**
     * @brief application constructor
     */
    application();

    /**
     * @brief Задать путь к входному файлу
     * @remarks Выполнять перед вызовом метода work
     * @param input путь к входному файлу
     */
    void setInput(std::string input);

    /**
     * @brief Задать путь к выходному файлу
     * @remarks Выполнять перед вызовом метода work
     * @param input путь к выходному файлу
     */
    void setOutput(std::string output);

    /**
     * @brief Выполняет основную работу приложения.
     * @remarks Вся логика функции состоит из трех шагов:
     *           1. Загрузить дерево из входного файла
     *           2. Отобразить дерево в консоли
     *           3. Сохранить дерево в выходном файле
     * @return 0 если успешно
     */
    int work();

private:
    /**
     * @brief Функция выполняет "шаг 2" (Отобразить дерево в консоли)
     * @remarks Функция реализована рекурсивно, используя служебный параметр level
     * @param tree дерево
     * @param level глубина рекурсии
     */
    void printTree(const tree& tree, unsigned level = 0);

    /**
     * @brief Функция выполняет "шаг 3" (Сохранить дерево в выходном файле)
     * @param tree дерево
     */
    void saveTree(const tree& tree);

private:
    std::string m_input;
    std::string m_output;
};

inline void application::setInput(std::string input)
{
    m_input = std::move(input);
}

inline void application::setOutput(std::string output)
{
    m_output = std::move(output);
}

#endif // APPLICATION_H
