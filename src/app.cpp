// ============================================================================
// <one line to give the program's name and a brief idea of what it does.>
//
//  Copyright (C) <yyyy> <Author Name> <author@mail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// ============================================================================


// ============================================================================
//
// <Put documentation here>
//
// <yyyy>-<mm>-<dd> <Author Name> <author@mail.com>
//
// * <programfilename>.cpp: created.
//
// ============================================================================


// ============================================================================
//
// References (this section should be deleted in the release version)
//
// * For coding style visit Google C++ Style Guide page at
//   <https://google.github.io/styleguide/cppguide.html>.
//
// * For command line arguments parsing using clipp consult documentation and
//   examples at <https://github.com/muellan/clipp>.
//
// * For filesystem operations (C++17) visit 'filesystem' reference at:
//   <https://en.cppreference.com/w/cpp/filesystem>.
//
// ============================================================================


// ============================================================================
// Preprocessor directives section
// ============================================================================
#define SODIUM_STATIC 1  // Required for 'sodium.h' to work properly if using
                         // static linking of the library


// ============================================================================
// Headers include section
// ============================================================================

// Related header

// "C" system headers

// Standard Library headers
#include <cstdlib>     // required by EXIT_SUCCESS, EXIT_FAILURE
#include <filesystem>  // Used for testing directory and file status
#include <iostream>    // required by cin, cout, ...
#include <string>      // self explanatory ...
#include <set>         // self explanatory ...
#include <vector>      // self explanatory ...

// External libraries headers
#include <clipp.hpp>  // command line arguments parsing
#include <sqlite3.h>  // SQLite3 database library
#include <sodium.h>   // Libsodium library


// ============================================================================
// Define namespace aliases
// ============================================================================

namespace fs = std::filesystem;


// ============================================================================
// Global constants section
// ============================================================================

const std::string kAppName = "cli_app";
const std::string kVersionString = "0.1";
const std::string kYearString = "yyyy";
const std::string kAuthorName = "Ljubomir Kurij";
const std::string kAuthorEmail = "ljubomir_kurij@protonmail.com";
const std::string kAppDoc = "\
Framework for developing command line applications using \'clipp\' command\n\
line argument parsing library.\n\n\
Mandatory arguments to long options are mandatory for short options too.\n";
const std::string kLicense = "\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n";


// ============================================================================
// Global variables section
// ============================================================================

static std::string exec_name = kAppName;


// ============================================================================
// Utility function prototypes
// ============================================================================

void printShortHelp(std::string = kAppName);
void printUsage(
        const clipp::group&,
        const std::string = kAppName,
        const clipp::doc_formatting& = clipp::doc_formatting{}
    );
void printVersionInfo();
void showHelp(
        const clipp::group&,
        const std::string = kAppName,
        const std::string = kAppDoc
    );


// ============================================================================
// App's main function body
// ============================================================================

int main(int argc, char *argv[])
{
    // Determine the exec name under wich program is beeing executed
    fs::path exec_path {argv[0]};
    exec_name = exec_path.filename().string();

    // Define structures to store command line options arguments and validators
    struct CLIArguments {
        bool        show_help;
        bool        print_usage;
        bool        show_version;
    };

    CLIArguments user_options {false, false, false};

    // Unsupported options aggregator.
    std::vector<std::string> unknown_options;

    // Option filters definitions
    auto istarget = clipp::match::prefix_not("-");

    // Set command line options
    auto cli = (
        // Must have more than one option
        // Take care not to omitt value filter when using
        // path input options
        (
            clipp::option("-h", "--help").set(user_options.show_help)
                .doc("show this help message and exit"),
            clipp::option("--usage").set(user_options.print_usage)
                .doc("give a short usage message"),
            clipp::option("-V", "--version").set(user_options.show_version)
                .doc("print program version")
        ).doc("general options:"),
        clipp::any_other(unknown_options)
    );

    // Parse command line options
    if (clipp::parse(argc, argv, cli)) {
        if (unknown_options.empty()) {
            if (user_options.show_help) {
                showHelp(cli, exec_name);

                return EXIT_SUCCESS;
            }
            if (user_options.print_usage) {
                auto fmt = clipp::doc_formatting {}
                    .first_column(0)
                    .last_column(79);

                printUsage(cli, exec_name, fmt);

                return EXIT_SUCCESS;
            }
            if (user_options.show_version) {
                printVersionInfo();

                return EXIT_SUCCESS;
            }
        } else {
            std::cerr << "Unknown options: ";
            for (const auto& opt : unknown_options) {
                std::cerr << opt << " ";
            }
            std::cerr << "\n";
            printShortHelp(exec_name);

            return EXIT_FAILURE;
        }
    }

    // No options provided. Execute default action
    std::cout << kAppName << ": Hello World!" << std::endl;

    // Try to initialize the libsodium library
    if (sodium_init() < 0) {
        std::cerr << kAppName
            << ": Error initializing libsodium library!"
            << std::endl;

        return EXIT_FAILURE;
    }

    // Sodium library initialized successfully. Print success message
    std::cout << kAppName
        << ": Libsodium library initialized successfully!"
        << std::endl;

    // Create a SQLite3 database connection
    sqlite3* DB; 
    
    // Try to open the database. If it does not exist, it will be created
    int ret_code = sqlite3_open("example.db", &DB); 
  
    // Check if the database was opened successfully
    if (0 != ret_code) { 
        // Something went wrong. Print error message and exit
        std::cerr << kAppName
            << ": Error creating DB: "
            << sqlite3_errmsg(DB)
            << std::endl; 

        return EXIT_FAILURE;
    } 
    
    // Everything went well. Print success message
    std::cout << kAppName << ": Database opened successfully!" << std::endl; 

    // Close the database
    sqlite3_close(DB); 

    // Return success
    return EXIT_SUCCESS;
}


// ============================================================================
// Function definitions
// ============================================================================

inline void printShortHelp(std::string exec_name) {
    std::cout << "Try '" << exec_name << " --help' for more information.\n";
}


inline void printUsage(
        const clipp::group& group,
        const std::string prefix,
        const clipp::doc_formatting& fmt)
{
    std::cout << clipp::usage_lines(group, prefix, fmt) << "\n";
}


void printVersionInfo() {
    std::cout << kAppName << " " << kVersionString << " Copyright (C) "
        << kYearString << " " << kAuthorName << "\n"
        << kLicense;
}


void showHelp(
        const clipp::group& group,
        const std::string exec_name,
        const std::string doc
        ) {
    auto fmt = clipp::doc_formatting {}.first_column(0).last_column(79);
    clipp::man_page man;

    man.prepend_section("USAGE", clipp::usage_lines(group, exec_name, fmt).str());
    man.append_section("", doc);
    man.append_section("", clipp::documentation(group, fmt).str());
    man.append_section("", "Report bugs to <" + kAuthorEmail + ">.");

    std::cout << man;
}