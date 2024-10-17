// MainProgramStrategy.h
#ifndef MAINPROGRAMSTRATEGY_H
#define MAINPROGRAMSTRATEGY_H

#include <ProgramActions/MainProgramAction.h>

#include <iostream>

#include <InputValidators/InputValidator.h>
#include <InputValidators/NonParametrizedConstraint.h>
#include <InputValidators/ParametrizedConstraint.h>

// ----------------------------------------------------------------------------
// MainProgramStrategy
// ----------------------------------------------------------------------------
//
// Description: Strategy for executing the main program
//
// ----------------------------------------------------------------------------
class MainProgramStrategy {
public:
  explicit MainProgramStrategy() = default;

  // Executes the main program
  int operator()(
      MainProgramAction const& action,
      std::string_view const& exec_name
    ) const {
    std::cout << exec_name << ": Hello world!\n";

    // Test InputValidators concept
    InputValidator<int> input_validator{42};
    input_validator
      .add_constraint(std::make_unique<NonParametrizedConstraint<int>> ())
      .add_constraint(std::make_unique<ParametrizedConstraint<int, int>> (13));
    input_validator.validate();

    return EXIT_SUCCESS;
  }
};

#endif // MAINPROGRAMSTRATEGY_H