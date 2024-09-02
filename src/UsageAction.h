// UsageAction.h
#ifndef USAGEACTION_H
#define USAGEACTION_H

#include <functional>
#include <string_view>

#include "ProgramAction.h"

// ----------------------------------------------------------------------------
// UsageAction
// ----------------------------------------------------------------------------
//
// Description: Displays usage information about the program
//
// ----------------------------------------------------------------------------
class UsageAction : public ProgramAction {
public:
  using ExecuteStrategy = std::function<int(UsageAction const&)>;

  explicit UsageAction(ExecuteStrategy executor)
    : executor_(std::move(executor)) { }
  
  int execute(std::string_view const& exec_name) const override {
    return executor_(*this, exec_name);
  }

private:
  ExecuteStrategy executor_;
};

#endif // USAGEACTION_H