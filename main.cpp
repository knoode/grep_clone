#include <iostream>

#include "grep.hpp"

#define HAS_FLAG(arg, short_flag, long_flag) \
    std::string(arg) == short_flag || std::string(arg) == long_flag

void usage(std::string_view exec_name, std::string_view error_msg = "");

int main(int argc, char* argv[])
{
    GrepInfo grep_info;

    if (argc >= 2) {
        if (HAS_FLAG(argv[1], "-h", "--help")) {
            usage(argv[0]);
            return EXIT_SUCCESS;
        }
    }

    if (argc < 3) {
        usage(argv[0], "Error: Wrong amount of arguments");
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i++) // skip exec name
    {
        if ( (!grep_info.ignore_case) && (HAS_FLAG(argv[i], "-i", "--ignore-case")) ) {
            grep_info.ignore_case = true;
        } else if ( (grep_info.outfile.size() == 0) && (HAS_FLAG(argv[i], "-o", "--output")) ) {
            if (i + 1 < argc) {
                grep_info.outfile = argv[i + 1];
                // Skip iteration: `-o` argument
                i++;
                continue;
            }
        } else if (argv[i + 1]) { // no flags are specified
            grep_info.pattern = std::string(argv[i]);
            grep_info.filename = std::string(argv[i + 1]);
            break;
        }
    }

    // Check if obligatory arguments were specified
    if (grep_info.pattern.size() == 0 || grep_info.filename.size() == 0) {
        usage(argv[0], "Error: Please supply the PATTERN and FILENAME");
        return EXIT_FAILURE;
    }

    grep(grep_info);
}

void usage(std::string_view exec_name, std::string_view error_msg)
{
    std::cout << "Usage: " << exec_name << " [ARGS] PATTERN FILENAME\n\n";
    std::cout << "-i, --ignore-case\tDo not preserve case\n";
    std::cout << "-o, --output FILENAME\tOutput findings to file\n";
    std::cout << "-h, --help\t\tDisplay help\n";

    if (error_msg.size() != 0)
    {
        std::cerr << '\n' << error_msg << '\n';
    }
}
