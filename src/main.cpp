#include <iostream>
#include <fstream>

#include <argparse/argparse.hpp>
#include <nlohmann/json.hpp>

#include "logcat/LogcatParser.h"
#include "Printer.h"

int main(int argc, const char** argv) {
    Printer printer;

    for (std::string line; std::getline(std::cin, line); ) {
        auto entry = LogcatParser::parseLine(line);
        if (entry) {
            printer.printFormatted(*entry);
        } else {
            printer.printLine(line);
        }
    }

    return 0;
}
