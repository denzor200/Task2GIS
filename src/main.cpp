#include "application.h"
#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char** argv)
{
    int status = 1;
    bool isValidArgs = false;

    po::options_description desc("Allowed options");
    desc.add_options() ///
        ("help,h", "produce help message") ///
        ("input,i", po::value<std::string>(), "forward path to input file") ///
        ("output,o", po::value<std::string>(), "forward path to output file");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    isValidArgs = true;
    if (vm.count("input") == 0) {
        std::cerr << "Path to input file was not set.\n";
        isValidArgs = false;
    }

    if (vm.count("output") == 0) {
        std::cerr << "Path to output file was not set.\n";
        isValidArgs = false;
    }

    if (!isValidArgs)
        std::cerr << "Please run '" << argv[0] << " --help' for more info\n";
    else {
        application app;
        app.setInput(vm["input"].as<std::string>());
        app.setOutput(vm["output"].as<std::string>());
        status = app.work();
    }
    return status;
}
