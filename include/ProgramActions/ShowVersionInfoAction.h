// ShowVersionInfoAction.h
#ifndef SHOWVERSIONINFOACTION_H
#define SHOWVERSIONINFOACTION_H

#include "ProgramAction.h"

// ----------------------------------------------------------------------------
// ShowVersionInfoAction
// ----------------------------------------------------------------------------
//
// Description: Displays version information about the program
//
// ----------------------------------------------------------------------------
class ShowVersionInfoAction : public ProgramAction {
public:
  using ExecuteStrategy = std::function<int(
    ShowVersionInfoAction const&,
    std::string_view const&
    )>;

  explicit ShowVersionInfoAction(ExecuteStrategy executor)
    : executor_(std::move(executor)) { }
  
  int execute(std::string_view const& exec_name) const override {
    return executor_(*this, exec_name);
  }

private:
  ExecuteStrategy executor_;
};

#endif // SHOWVERSIONINFOACTION_H
