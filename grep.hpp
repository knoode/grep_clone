#pragma once

struct GrepInfo {
    std::string pattern;
    std::string filename;
    std::string outfile;
    bool ignore_case = false;
};

void grep(GrepInfo& grep_info);
