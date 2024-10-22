// DefaultCheckStrategyNPC.h

#ifndef DEFAULTCHECKSTRATEGYNPC_H
#define DEFAULTCHECKSTRATEGYNPC_H

#include "NonParametrizedConstraint.h"

#include <iostream>

// ----------------------------------------------------------------------------
// DefaultCheckStrategyNPC
// ----------------------------------------------------------------------------
//
// Description: Default check strategy for non-parametrized constraints
//
// ----------------------------------------------------------------------------

template <typename InputDataType>
class DefaultCheckStrategyNPC {
public:
  using ConstraintType = NonParametrizedConstraint<InputDataType>;
  using pConstraintType = std::unique_ptr<ConstraintType>;

  explicit DefaultCheckStrategyNPC() = default;

  static pConstraintType create() {
    return std::make_unique<ConstraintType>(DefaultCheckStrategyNPC());
  }

  bool operator()(
      ConstraintType const& constraint,
      InputDataType const& input
      ) const {
    std::cout << "Checking '"
      << input
      << "' against non-parametrized constraint!\n";

    return true;
  }
};

#endif // DEFAULTCHECKSTRATEGYNPC_H