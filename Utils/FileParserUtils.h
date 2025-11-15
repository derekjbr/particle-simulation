#ifndef FILEPARSERUTILS_H
#define FILEPARSERUTILS_H

#include <string>
#include <fstream>

namespace Utils {

    std::string ReadFileToString(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + filePath);
        }
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        return content;
    }

}

#endif // FILEPARSERUTILS_H