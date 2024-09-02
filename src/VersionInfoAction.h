// VersionInfoAction.h
#ifndef VERSIONINFOACTION_H
#define VERSIONINFOACTION_H

#include <functional>
#include <string_view>

#include "ProgramAction.h"

// ----------------------------------------------------------------------------
// VersionInfoAction
// ----------------------------------------------------------------------------
//
// Description: Displays version information about the program
//
// ----------------------------------------------------------------------------
class VersionInfoAction : public ProgramAction {
public:
  using ExecuteStrategy = std::function<int(VersionInfoAction const&)>;

  explicit VersionInfoAction(ExecuteStrategy executor)
    : executor_(std::move(executor)) { }
  
  int execute(
      std::string_view const& exec_name
      std::string_view const& version,
      std::string_view const& year,
      std::string_view const& author_name,
      std::string_view const& license
      ) const override {
    return executor_(*this, exec_name, version, year, author_name, license);
  }

private:
  ExecuteStrategy executor_;
};

#endif // VERSIONINFOACTION_H
