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

    // NonParametrizedConstraint<int> a{ };
    std::unique_ptr<Constraint<int>> a
      = std::make_unique<NonParametrizedConstraint<int>> ();
    std::cout << exec_name << ": " << a.get() << "\n";
    std::cout << exec_name << ": ";
    a->check(10);
    std::unique_ptr<Constraint<int>> b = std::move(a);
    std::cout << exec_name << ": " << b.get() << "\n";
    std::cout << exec_name << ": ";
    b->check(10);

    return EXIT_SUCCESS;
  }
};

#endif // MAINPROGRAMSTRATEGY_H