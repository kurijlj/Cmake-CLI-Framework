// ParametrizedConstraint.h
#ifndef PARAMETRIZEDCONSTRAINT_H
#define PARAMETRIZEDCONSTRAINT_H

#include "Constraint.h"

// ----------------------------------------------------------------------------
// ParametrizedConstraint
// ----------------------------------------------------------------------------
//
// Description: Abstract base class for all constraints that do take a
//              constraint parameter at the run time. i.e. greater than, less
//              than, etc.
//
// ----------------------------------------------------------------------------
template <typename InputDataType, typename CheckDataType>
class ParametrizedConstraint : public Constraint<InputDataType> {
public:
  explicit ParametrizedConstraint(const CheckDataType & value) : value_(value)
  { }

  bool check(const InputDataType & input) const override {
    std::cout << "Checking '"
      << input
      << "' against parametrized constraint '"
      << value_
      << "'!\n";

    return true;
  }

  std::string str() const override {
    std::stringstream ss;
    ss << "parametrized constraint with value: "
      << value_;

    return ss.str();
  }

  friend std::ostream & operator<<(
      std::ostream & os,
      const ParametrizedConstraint<InputDataType, CheckDataType> & obj
    ) {
    os << "parametrized constraint with value: "
      << obj.value_;

    return os;
  }

protected:
  CheckDataType value_;
};

#endif // PARAMETRIZEDCONSTRAINT_H