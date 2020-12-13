#include "application.h"
#include "file.h"
#include "tree.h"
#include "json/value.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>

application::application()
{
}

int application::work()
{
    if (m_input.empty() || m_output.empty())
        throw std::logic_error("parameter is set incorrectly");

    auto tree = tree::parse(json::value::parse(file::ReadAllText(m_input)));
    printTree(tree);
    saveTree(tree);

    return 0;
}

void application::printTree(const tree& tree, unsigned level)
{
    if (tree.isDouble())
        std::cout << std::string(level, '-') << tree.asDouble() << std::endl;
    else if (tree.isInteger())
        std::cout << std::string(level, '-') << tree.asInteger() << std::endl;
    else if (tree.isString())
        std::cout << std::string(level, '-') << std::quoted(tree.asString()) << std::endl;
    else {
        std::cerr << "Invalid tree was detected!";
    }

    for (const auto& child : tree.childs()) {
        printTree(child, level + 1);
    }
}

void application::saveTree(const tree& tree)
{
    std::ofstream ofs(m_output);
    if (!ofs.is_open())
        throw std::runtime_error("Can't open '" + m_output + "'");
    ofs << tree.serialize().serialize();
}
