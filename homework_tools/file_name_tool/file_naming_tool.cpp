#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cctype>
#include <algorithm>

namespace fs = std::filesystem;

/* ---------------- Utility ---------------- */

static std::string trim(const std::string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == std::string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

static char firstNonSpaceCharLower(const std::string& s) {
    for (unsigned char c : s) {
        if (!std::isspace(c))
            return static_cast<char>(std::tolower(c));
    }
    return '\0';
}

/* ---------------- Config (UID) ---------------- */

static void saveUID(const fs::path& configPath, const std::string& uid) {
    std::ofstream out(configPath);
    if (!out) {
        std::cerr << "Error: could not write config file: " << configPath << "\n";
        std::exit(1);
    }
    out << "UID=" << uid << "\n";
}

static std::string readUIDIfPresent(const fs::path& configPath) {
    if (!fs::exists(configPath)) return "";

    std::ifstream in(configPath);
    if (!in) return "";

    std::string line;
    if (!std::getline(in, line)) return "";

    line = trim(line);
    const std::string prefix = "UID=";
    if (line.rfind(prefix, 0) != 0) return "";

    return trim(line.substr(prefix.size()));
}

static std::string promptForUID() {
    std::string uid;
    std::cout << "Enter your Unique ID: ";
    std::getline(std::cin, uid);
    uid = trim(uid);

    while (uid.empty()) {
        std::cout << "Unique ID cannot be empty. Enter your Unique ID: ";
        std::getline(std::cin, uid);
        uid = trim(uid);
    }
    return uid;
}

static std::string loadConfirmOrPromptUID(const fs::path& configPath) {
    std::string uid = readUIDIfPresent(configPath);

    if (uid.empty()) {
        uid = promptForUID();
        saveUID(configPath, uid);
        return uid;
    }

    std::cout << "Unique ID is '" << uid << "'. Is this correct? (Y/n): ";
    std::string answer;
    std::getline(std::cin, answer);

    char c = firstNonSpaceCharLower(answer);
    if (c == 'n') {
        uid = promptForUID();
        saveUID(configPath, uid);
    }

    return uid;
}

/* ---------------- Project Name ---------------- */

static std::string normalizeProjectName(std::string input) {
    input = trim(input);
    if (input.empty()) {
        std::cerr << "Project name cannot be empty.\n";
        std::exit(1);
    }

    std::string out;
    bool lastWasUnderscore = false;

    for (unsigned char c : input) {
        if (std::isspace(c)) {
            if (!out.empty() && !lastWasUnderscore) {
                out.push_back('_');
                lastWasUnderscore = true;
            }
            continue;
        }

        if (std::isalnum(c) || c == '_' || c == '-') {
            out.push_back(static_cast<char>(c));
            lastWasUnderscore = (c == '_');
        }
    }

    while (!out.empty() && out.back() == '_')
        out.pop_back();

    if (out.empty()) {
        std::cerr << "Project name became empty after normalization.\n";
        std::exit(1);
    }

    return out;
}

static std::string getProjectNameFromArgOrPrompt(const std::string& arg) {
    std::string name = trim(arg);
    if (name.empty()) {
        std::cout << "Enter Project Name (used for the zip file name): ";
        std::getline(std::cin, name);
    }
    return normalizeProjectName(name);
}

/* ---------------- File Collection ---------------- */

static bool isCppOrHeader(const fs::path& p) {
    std::string ext = p.extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(),
                   [](unsigned char c){ return static_cast<char>(std::tolower(c)); });
    return (ext == ".cpp" || ext == ".h");
}

static std::vector<fs::path> collectSourceFiles(const fs::path& dir) {
    std::vector<fs::path> files;

    for (const auto& entry : fs::directory_iterator(dir)) {
        if (!entry.is_regular_file())
            continue;

        if (isCppOrHeader(entry.path())) {
            files.push_back(entry.path().filename());
        }
    }

    return files;
}

/* ---------------- Main ---------------- */

int main(int argc, char** argv) {
    try {
        fs::path cwd = fs::current_path();
        fs::path configPath = cwd / ".submit_config";

        std::string uid = loadConfirmOrPromptUID(configPath);

        std::string projectArg;
        if (argc >= 2)
            projectArg = argv[1];

        std::string projectName = getProjectNameFromArgOrPrompt(projectArg);

        auto files = collectSourceFiles(cwd);
        if (files.empty()) {
            std::cerr << "No .cpp or .h files found in this directory.\n";
            return 1;
        }

        fs::path tempDir = cwd / "temp_submit";
        if (fs::exists(tempDir))
            fs::remove_all(tempDir);
        fs::create_directory(tempDir);

        std::string prefix = uid + "_";

        for (const auto& f : files) {
            fs::path src = cwd / f;
            std::string filename = f.string();

            std::string outName = filename;
            if (filename.rfind(prefix, 0) != 0) {
                outName = prefix + filename;
            }

            fs::copy_file(src, tempDir / outName,
                          fs::copy_options::overwrite_existing);
        }

        std::string zipName = uid + "_" + projectName + ".zip";

        if (fs::exists(cwd / zipName))
            fs::remove(cwd / zipName);

        std::string cmd =
            "cd \"" + tempDir.string() +
            "\" && zip -r \"../" + zipName + "\" .";

        int result = std::system(cmd.c_str());
        if (result != 0) {
            std::cerr << "zip command failed. Make sure 'zip' is installed.\n";
            fs::remove_all(tempDir);
            return 1;
        }

        fs::remove_all(tempDir);

        std::cout << "Created " << zipName << " with UID-prefixed files.\n";
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
