#include "application.h"
#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char** argv)
{
    po::options_description desc("Allowed options");
    desc.add_options() ///
        ("help", "produce help message") ///
        ("input,i", po::value<std::string>(), "forward path to input file") ///
        ("output,o", po::value<std::string>(), "forward path to output file");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    if (vm.count("input")) {
        std::cerr << "Path to input file was not set.\n";
        return 1;
    }

    if (vm.count("output")) {
        std::cerr << "Path to output file was not set.\n";
        return 1;
    }

    application app;
    app.setInput(vm["input"].as<std::string>());
    app.setOutput(vm["output"].as<std::string>());
    return app.work();
}
