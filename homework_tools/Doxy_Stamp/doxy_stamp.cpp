#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

// Configure your UID here
const std::string AUTHOR_ID = "your_uid";

// Get today's date in YYYY-MM-DD format
std::string getTodayDate() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm localTime = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d");
    return oss.str();
}

// Only target common C++ file extensions
bool isCppFile(const fs::path& path) {
    std::string ext = path.extension().string();
    return (ext == ".cpp" || ext == ".cc" || ext == ".cxx" ||
            ext == ".h"   || ext == ".hpp" || ext == ".hxx");
}

// Read entire file into a string
bool readFile(const fs::path& path, std::string& outContent) {
    std::ifstream in(path);
    if (!in) return false;

    outContent.assign((std::istreambuf_iterator<char>(in)),
                       std::istreambuf_iterator<char>());
    return true;
}

// Write entire string back to file
bool writeFile(const fs::path& path, const std::string& content) {
    std::ofstream out(path);
    if (!out) return false;

    out << content;
    return true;
}

int main() {
    std::string date;
    std::string assignment;

    // Auto-detect date
    std::string today = getTodayDate();
    std::cout << "Detected today's date: " << today << "\n";
    std::cout << "Is this correct? (y/n): ";

    std::string response;
    std::getline(std::cin, response);

    if (response == "y" || response == "Y") {
        date = today;
    } else {
        std::cout << "Enter date manually (YYYY-MM-DD): ";
        std::getline(std::cin, date);
    }

    std::cout << "Enter assignment name: ";
    std::getline(std::cin, assignment);

    const int width = 60;
    std::string border(width - 3, '*');

    std::cout << "\nScanning current directory...\n\n";

    bool anySeen = false;

    for (const auto& entry : fs::directory_iterator(fs::current_path())) {

        if (!entry.is_regular_file())
            continue;

        if (!isCppFile(entry.path()))
            continue;

        anySeen = true;

        std::string filename = entry.path().filename().string();

        std::cout << "Stamp file: " << filename << " ? (y/n): ";
        std::string answer;
        std::getline(std::cin, answer);

        if (answer != "y" && answer != "Y")
            continue;

        std::string content;
        if (!readFile(entry.path(), content)) {
            std::cout << "Could not open " << filename << "\n\n";
            continue;
        }

        size_t pos = content.find("<doxy>");
        if (pos == std::string::npos) {
            std::cout << "No <doxy> tag found in " << filename << "\n\n";
            continue;
        }

        // Build header
        std::string stamp = "/**\n";
        stamp += " * " + border + "\n";
        stamp += " * @file " + filename + "\n";
        stamp += " * @author " + AUTHOR_ID + "\n";
        stamp += " * @date " + date + "\n";
        stamp += " * @brief " + assignment + "\n";
        stamp += " * " + border + "\n";
        stamp += " */\n\n";

        content.replace(pos, 6, stamp);

        if (!writeFile(entry.path(), content)) {
            std::cout << "Could not write " << filename << "\n\n";
            continue;
        }

        std::cout << filename << " stamped successfully.\n\n";
    }

    if (!anySeen) {
        std::cout << "No C++ files found in this directory.\n";
    }

    std::cout << "Done.\n";
    return 0;
}
