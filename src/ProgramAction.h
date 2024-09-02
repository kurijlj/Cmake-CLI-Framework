// ProgramAction.h
#ifndef PROGRAMACTION_H
#define PROGRAMACTION_H

// ----------------------------------------------------------------------------
// Abstract class for all actions that can be executed by the program
// ----------------------------------------------------------------------------
//
// Description: TODO: Add description
//
// ----------------------------------------------------------------------------

class ProgramAction {
public:
  ~ProgramAction() = default;

  virtual int execute() const = 0;
};

#endif // PROGRAMACTION_H