#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

// Location of config file in home directory
std::string getConfigPath() {
    const char* home = std::getenv("HOME");
    if (!home) return ".doxy_stamp_config";
    return std::string(home) + "/.doxy_stamp_config";
}

// Get today's date
std::string getTodayDate() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm localTime = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d");
    return oss.str();
}

// Only C++ file types
bool isCppFile(const fs::path& path) {
    std::string ext = path.extension().string();
    return (ext == ".cpp" || ext == ".cc" || ext == ".cxx" ||
            ext == ".h"   || ext == ".hpp" || ext == ".hxx");
}

// Read full file
bool readFile(const fs::path& path, std::string& content) {
    std::ifstream in(path);
    if (!in) return false;

    content.assign((std::istreambuf_iterator<char>(in)),
                    std::istreambuf_iterator<char>());
    return true;
}

// Write full file
bool writeFile(const fs::path& path, const std::string& content) {
    std::ofstream out(path);
    if (!out) return false;

    out << content;
    return true;
}

// Load UID from config
std::string loadUID() {
    std::ifstream in(getConfigPath());
    if (!in) return "";
    std::string uid;
    std::getline(in, uid);
    return uid;
}

// Save UID to config
void saveUID(const std::string& uid) {
    std::ofstream out(getConfigPath());
    out << uid;
}

int main() {

    std::string uid = loadUID();

    // First-time setup or confirmation
    if (uid.empty()) {
        while (true) {
            std::cout << "Enter your UID: ";
            std::getline(std::cin, uid);

            std::cout << "You entered: " << uid << "\n";
            std::cout << "Is this correct? (y/n): ";

            std::string confirm;
            std::getline(std::cin, confirm);

            if (confirm == "y" || confirm == "Y") {
                saveUID(uid);
                break;
            }
        }
    } else {
        std::cout << "Saved UID detected: " << uid << "\n";
        std::cout << "Use this UID? (y/n): ";

        std::string confirm;
        std::getline(std::cin, confirm);

        if (!(confirm == "y" || confirm == "Y")) {
            uid.clear();
            return main();  // restart setup
        }
    }

    // Date handling
    std::string today = getTodayDate();
    std::cout << "\nDetected today's date: " << today << "\n";
    std::cout << "Is this correct? (y/n): ";

    std::string date;
    std::string response;
    std::getline(std::cin, response);

    if (response == "y" || response == "Y") {
        date = today;
    } else {
        std::cout << "Enter date manually (YYYY-MM-DD): ";
        std::getline(std::cin, date);
    }

    std::string assignment;
    std::cout << "Enter assignment name: ";
    std::getline(std::cin, assignment);

    const int width = 60;
    std::string border(width - 3, '*');

    std::cout << "\nScanning current directory...\n\n";

    for (const auto& entry : fs::directory_iterator(fs::current_path())) {

        if (!entry.is_regular_file()) continue;
        if (!isCppFile(entry.path())) continue;

        std::string filename = entry.path().filename().string();

        std::cout << "Stamp file: " << filename << " ? (y/n): ";
        std::string answer;
        std::getline(std::cin, answer);

        if (!(answer == "y" || answer == "Y"))
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

        std::string stamp = "/**\n";
        stamp += " * " + border + "\n";
        stamp += " * @file " + filename + "\n";
        stamp += " * @author " + uid + "\n";
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

    std::cout << "Done.\n";
    return 0;
}
