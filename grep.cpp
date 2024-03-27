#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

#include "grep.hpp"

std::string tolower_str(std::string str);

void grep(GrepInfo& grep_info)
{
    std::string line;
    std::vector<std::string> lines;
    std::vector<std::string> grepped;
    std::ifstream in { grep_info.filename };
    std::ofstream out { grep_info.outfile };
     
    while ( std::getline(in, line) ) {
        lines.push_back(line);
    }

    if (grep_info.ignore_case) {
        const std::string low_pattern = tolower_str(grep_info.pattern);
        for (auto s : lines) {
            const std::string low_line = tolower_str(s);
            if (low_line.find(low_pattern) != std::string::npos) {
                grepped.push_back(s);
            }
        }
    } else {
        for (auto s : lines) {
            if ( s.find(grep_info.pattern) != std::string::npos ) {
                grepped.push_back(s);
            }
        }
    }

    if (grep_info.outfile.size() == 0) {
        for (auto s : grepped) {
            std::cout << s << '\n';
        }
    } else {
        for (auto s : grepped) {
            out << s << '\n';
        }
    }

    in.close(); out.close();
}

std::string tolower_str(std::string str)
{
//    std::transform(str.begin(), str.end(), str.begin(),
//                   [](unsigned char c) { return std::tolower(c); });
    for (size_t i{}; i < str.size(); i++) {
        str[i] = std::tolower(str[i]);
    }

    return str;
}
