#include <iostream>
#include <fstream>

#include <argparse/argparse.hpp>
#include <nlohmann/json.hpp>

#include "Printer.h"
#include "filter/FilterFactory.h"
#include "logcat/LogcatParser.h"

argparse::ArgumentParser parseArgs(int argc, const char** argv) {
    argparse::ArgumentParser args(argv[0], VERSION);
    args.add_argument("-f", "--filter")
        .help("Path to a filter file")
        .action([&](const std::string& path) {
            try {
                std::ifstream jsonFile(path);
                nlohmann::json json;
                jsonFile >> json;
                return json;
            } catch (const std::exception& e) {
                std::cerr << "Invalid json file:" << e.what() << std::endl;
                std::cerr << args << std::endl;
                ::exit(-1);
            }
        });

    try {
        args.parse_args(argc, argv);
    } catch (const std::runtime_error& error) {
        std::cerr << "Failed to parse command line arguments: " << error.what() << std::endl;
        std::cerr << args << std::endl;
        ::exit(-1);
    }

    return args;
}

int main(int argc, const char** argv) {
    auto args = parseArgs(argc, argv);

    // Set up resources
    auto filter = FilterFactory::create(args);
    Printer printer;

    for (std::string line; std::getline(std::cin, line); ) {
        auto entry = LogcatParser::parseLine(line);
        if (entry) {
            if (!filter || filter->pass(*entry)) {
                printer.printFormatted(*entry);
            }
        } else {
            printer.printLine(line);
        }
    }

    return 0;
}
