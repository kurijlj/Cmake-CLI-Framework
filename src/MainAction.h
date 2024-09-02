// MainAction.h
#ifndef MAINACTION_H
#define MAINACTION_H

#include <functional>
#include <string_view>

#include "ProgramAction.h"

// ----------------------------------------------------------------------------
// MainAction
// ----------------------------------------------------------------------------
//
// Description: Executes the main action of the program
//
// ----------------------------------------------------------------------------
class MainAction : public ProgramAction {
public:
  using ExecuteStrategy = std::function<int(MainAction const&)>;

  explicit MainAction(ExecuteStrategy executor)
    : executor_(std::move(executor)) { }
  
  int execute(std::string_view const& exec_name) const override {
    return executor_(*this, exec_name);
  }

private:
  ExecuteStrategy executor_;
};

#endif // MAINACTION_H
