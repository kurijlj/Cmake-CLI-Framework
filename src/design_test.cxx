// ============================================================================
// <one line to give the file's name and a brief idea of what it does.>
//  Copyright (C) <yyyy> <Author Name> <author@mail.com>
//
// This file is part of <program_name>.
// 
// <program_name> is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software  Foundation, either version 3 of the License, or (at your option)
// any later version.
// 
// <program_name> is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// <program_name>. If not, see <https://www.gnu.org/licenses/>.
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
// * For command line arguments parsing using clipp consult documentation and
//   examples at <https://github.com/muellan/clipp>.
//
// ============================================================================


// ============================================================================
// Preprocessor directives section
// ============================================================================


// ============================================================================
// Headers include section
// ============================================================================

// Related header

// "C" system headers

// Standard Library headers
#include <cstdlib>      // required by EXIT_SUCCESS, EXIT_FAILURE
#include <filesystem>   // Used for testing directory and file status
#include <iostream>     // required by cin, cout, ...
#include <memory>       // required by std::unique_ptr
#include <string>       // required by std::string

// External libraries headers
#include <clipp.hpp>    // command line arguments parsing

// Project librarties headers
// #include <ProgramActions/MainProgramStrategy.h>
#include <ProgramActions/ShowHelpClippStrategy.h>
#include <ProgramActions/ShowUsageClippStrategy.h>
#include <ProgramActions/ShowVersionInfoStrategy.h>
#include <ProgramActions/UnsupportedOptionsClippStrategy.h>

#include "MainProgramStrategy.h"


// ============================================================================
// Global constants section
// ============================================================================

static constexpr auto kAppName       = "cli_app";
static constexpr auto kVersionString = "0.1";
static constexpr auto kYearString    = "yyyy";
static constexpr auto kAuthorName    = "Ljubomir Kurij";
static constexpr auto kAuthorEmail   = "ljubomir_kurij@protonmail.com";
static constexpr auto kAppDoc        = "\
Framework for developing command line applications using \'clipp\' command\n\
line argument parsing library.\n\n\
Mandatory arguments to long options are mandatory for short options too.\n";
static constexpr auto kLicense       = "\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n";


// ============================================================================
// Global variables section
// ============================================================================


// ============================================================================
// Utility function prototypes
// ============================================================================


// ============================================================================
// Main Function Section
// ============================================================================

int main(int argc, char *argv[])
{
  namespace fs = std::filesystem;  // Define a shorter alias for filesystem

  // Determine the exec name under wich program is beeing executed
  std::string exec_name = fs::path(argv[0]).filename().string();

  // Here we define the structure for holding the passed command line otions.
  // The structure is also used to define the command line options and their
  // default values.
  struct CLIOptions {
    bool show_help;
    bool print_usage;
    bool show_version;
    std::string input_file;
    std::vector<std::string> unsupported;
    };

  // Define the default values for the command line options
  CLIOptions user_options {
    false,  // show_help
    false,  // print_usage
    false,  // show_version
    "",     // input_file
    {}      // unsupported options aggregator
    };

  // Option filters definitions
  auto istarget = clipp::match::prefix_not("-");  // Filter out strings that
                                                  // start with '-' (options)

  // Set command line options
  auto parser_config = (
    // Define the command line options and their default values.
    // - Must have more than one option.
    // - The order of the options is important.
    // - The order of the options in the group is important.
    // - Take care not to omitt value filter when parsing file and directory
    //   names. Otherwise, the parser will treat options as values.
    // - Define positional arguments first
    // - Define positional srguments as optional to enforce the priority of
    //   help, usage and version switches. Then enforce the required
    //   positional arguments by checking if their values are set.
    (
      clipp::opt_value(istarget, "INPUT_FILE", user_options.input_file),
      clipp::option("-h", "--help").set(user_options.show_help)
        .doc("show this help message and exit"),
      clipp::option("--usage").set(user_options.print_usage)
        .doc("give a short usage message"),
      clipp::option("-V", "--version").set(user_options.show_version)
        .doc("print program version")
    ).doc("general options:"),
    clipp::any_other(user_options.unsupported)
  );

  // Parse command line options
  auto result = clipp::parse(argc, argv, parser_config);

  // Reference to a program action that will be executed
  std::unique_ptr<ProgramAction> program_action;

  // Check triggered command line options by the priority order

  // Check if the unsupported options were passed
  if (!user_options.unsupported.empty()) {
    program_action = std::make_unique<UnsupportedOptionsAction> (
      UnsupportedOptionsClippStrategy(user_options.unsupported)
      );

  // Check if the help switch was triggered. We give help switch the
  // highest priority, so if it is triggered we don't need to check
  // anything else.
  } else if (user_options.show_help) {
    program_action = std::make_unique<ShowHelpAction> (
      ShowHelpClippStrategy(parser_config, kAppDoc, kAuthorEmail)
      );

  // Check if the usage switch was triggered. Usge switch has the second
  // highest priority, so if it is triggered we don't need to check
  // anything else.
  } else if (user_options.print_usage) {
    auto fmt = clipp::doc_formatting {}
      .first_column(0)
      .last_column(79);
    program_action = std::make_unique<ShowUsageAction> (
      ShowUsageClippStrategy(parser_config, fmt)
      );

  // Check if the version switch was triggered. Version switch has the
  // third highest priority.
  } else if (user_options.show_version) {
    program_action = std::make_unique<ShowVersionInfoAction> (
      ShowVersionInfoStrategy(
        kVersionString,
        kYearString,
        kAuthorName,
        kLicense
        )
      );

  // No high priority switch was triggered. Proceed with the main code.
  } else {
    // Default program action goes here ---------------------------------------
    program_action = std::make_unique<MainProgramAction> (
      MainProgramStrategy()
      );
  }

  return program_action->execute(exec_name.c_str());
}
