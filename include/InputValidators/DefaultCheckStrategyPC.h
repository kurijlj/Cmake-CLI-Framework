// DefaultCheckStrategyPC.h

#ifndef DEFAULTCHECKSTRATEGYPC_H
#define DEFAULTCHECKSTRATEGYPC_H

#include "ParametrizedConstraint.h"

#include <iostream>

// ----------------------------------------------------------------------------
// DefaultCheckStrategyPC
// ----------------------------------------------------------------------------
//
// Description: Default check strategy for parametrized constraints
//
// ----------------------------------------------------------------------------

template <typename InputDataType, typename CheckDataType>
class DefaultCheckStrategyPC {
public:
  using ConstraintType = ParametrizedConstraint<InputDataType, CheckDataType>;

  explicit DefaultCheckStrategyPC() = default;

  bool operator()(
      ConstraintType const& constraint,
      InputDataType const& input
      ) const {
    std::cout << "Checking '"
      << input
      << "' against parametrized constraint '"
      << constraint.value()
      << "'!\n";

    return true;
  }
};

#endif // DEFAULTCHECKSTRATEGYPC_H