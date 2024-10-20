
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
  using CheckStrategy = std::function<bool(
    NonParametrizedConstraint<InputDataType> const &,
    InputDataType const &
    )>;

  explicit NonParametrizedConstraint(CheckStrategy executor)
    : executor_(std::move(executor))
  { }

  bool check(const InputDataType & input) const override {
    return executor_(*this, input);
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

private:
  CheckStrategy executor_;
};

#endif // NONPARAMETRIZEDCONSTRAINT_H
