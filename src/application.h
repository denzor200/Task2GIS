#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>

// TODO docs

class tree;

class application {
    std::string m_input;
    std::string m_output;

public:
    application();

    void setInput(std::string input);

    void setOutput(std::string output);

    int work();

private:
    void printTree(const tree& tree, unsigned level = 0);
    void saveTree(const tree& tree);
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
