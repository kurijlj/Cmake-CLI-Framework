
// NonParametrizedConstraint.h
#ifndef NONPARAMETRIZEDCONSTRAINT_H
#define NONPARAMETRIZEDCONSTRAINT_H

#include "Constraint.h"

// ----------------------------------------------------------------------------
// NonParametrizedConstraint
// ----------------------------------------------------------------------------
//
// Description: Abstract base class for all constraints that do not take a
//              constraint parameter at the run time. i.e. existance checks
//              (files, directories, ...), empty/non-empty checks, etc.
//
// ----------------------------------------------------------------------------
template <typename InputDataType>
class NonParametrizedConstraint : public Constraint<InputDataType> {
public:
  explicit NonParametrizedConstraint() {
    this->value_ = true;  // We are initializing protected data member of the
                          // parent class
  }

  bool check(const InputDataType & input) const override {
    std::cout << "Checking '"
      << input
      << "' against non-parametrized constraint!\n";

    return true;
  }

  std::string str() const override {
      return std::string("non-parametrized constraint");
  }

  friend std::ostream & operator<<(
      std::ostream & os,
      const NonParametrizedConstraint<InputDataType> & obj
    ) {
    os << "non-parametrized constraint";
    return os;
  }
};

#endif // NONPARAMETRIZEDCONSTRAINT_H
