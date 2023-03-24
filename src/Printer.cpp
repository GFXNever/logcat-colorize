#include "Printer.h"

#include <termcolor/termcolor.hpp>

#include <iomanip>
#include <iostream>

void Printer::printLine(const std::string& line) const {
    std::cout << termcolor::bold << termcolor::bright_grey << line << termcolor::reset << std::endl;
}

void Printer::printFormatted(const LogcatEntry& log) const {

    printTimestamp(std::cout, log);
    std::cout << " ";
    printLogLevel(std::cout, log);
    std::cout << " ";
    printPid(std::cout, log);
    std::cout << " ";
    printTag(std::cout, log);
    std::cout << " ";
    printMessage(std::cout, log);

    std::cout << std::endl;
}

void Printer::printTimestamp(std::ostream& out, const LogcatEntry& log) const {
    out << termcolor::magenta << std::put_time(&log.timestamp.time, "%m-%d %H:%M:%S")
        << "." << std::setw(3) << std::setfill('0') << log.timestamp.milliseconds << std::setfill(' ')
        << termcolor::reset;
}

void Printer::printPid(std::ostream& out, const LogcatEntry& log) const {
    out << termcolor::cyan << "[" << std::setw(5) << log.pid << "]" << termcolor::reset;
}

void Printer::printLogLevel(std::ostream& out, const LogcatEntry& log) const {
    char levelLetter = 'V';
    switch (log.level) {
        case LogLevel::Verbose:
            levelLetter = 'V';
            out << termcolor::bold << termcolor::on_cyan << termcolor::white;
            break;
        case LogLevel::Debug:
            levelLetter = 'D';
            out << termcolor::bold << termcolor::on_blue << termcolor::white;
            break;
        case LogLevel::Info:
            levelLetter = 'I';
            out << termcolor::bold << termcolor::on_green << termcolor::white;
            break;
        case LogLevel::Warning:
            levelLetter = 'W';
            out << termcolor::bold << termcolor::on_yellow << termcolor::white;
            break;
        case LogLevel::Error:
            levelLetter = 'E';
            out << termcolor::bold << termcolor::on_red << termcolor::white;
            break;
        case LogLevel::Fatal:
            levelLetter = 'F';
            out << termcolor::bold << termcolor::on_red << termcolor::white;
            break;
        case LogLevel::Silent:
            levelLetter = 'S';
            out << termcolor::bold << termcolor::white;
            break;
    }

    out << " " << levelLetter << " " << termcolor::reset;
}

void Printer::printTag(std::ostream& out, const LogcatEntry& log) const {
    out << termcolor::white << log.tag << termcolor::reset;
}

void Printer::printMessage(std::ostream& out, const LogcatEntry& log) const {
    switch (log.level) {
        case LogLevel::Verbose:
            out << termcolor::cyan;
            break;
        case LogLevel::Debug:
            out << termcolor::blue;
            break;
        case LogLevel::Info:
            out << termcolor::green;
            break;
        case LogLevel::Warning:
            out << termcolor::yellow;
            break;
        case LogLevel::Error:
            out << termcolor::red;
            break;
        case LogLevel::Fatal:
            out << termcolor::red;
            break;
        case LogLevel::Silent:
            out << termcolor::white;
            break;
    }

    out << log.message << termcolor::reset;
}


