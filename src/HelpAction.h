// HelpAction.h
#ifndef HELPACTION_H
#define HELPACTION_H

#include <functional>
#include <string_view>

#include "ProgramAction.h"

// ----------------------------------------------------------------------------
// HelpAction
// ----------------------------------------------------------------------------
//
// Description: Displays help information about the program
//
// ----------------------------------------------------------------------------
class HelpAction : public ProgramAction {
public:
  using ExecuteStrategy = std::function<int(HelpAction const&)>;

  explicit HelpAction(ExecuteStrategy executor)
    : executor_(std::move(executor)) { }
  
  // Shows short help message
  int execute(std::string_view const& exec_name)) const override {
    return executor_(*this, exec_name);
  }

  // Shows detailed help message
  int execute(
      std::string_view const& exec_name,
      std::string_view const& doc,
      std::string_view const& author_email
      ) const override {
    return executor_(*this, exec_name, doc, author_email);
  }

private:
  ExecuteStrategy executor_;
};

#endif // HELPACTION_H