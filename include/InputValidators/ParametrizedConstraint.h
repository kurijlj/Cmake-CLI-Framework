// ParametrizedConstraint.h
#ifndef PARAMETRIZEDCONSTRAINT_H
#define PARAMETRIZEDCONSTRAINT_H

#include "Constraint.h"

template <typename InputDataType, typename CheckDataType>
class ParametrizedConstraint : public Constraint<InputDataType, CheckDataType> {
public:
  explicit ParametrizedConstraint(const CheckDataType & value) {
    this->value_ = value;
  }

  bool check(const InputDataType & input) const override {
    std::cout << "Checking: "
      << input
      << " against parametrized constraint with value: "
      << this->value_
      << "!\n";

    return true;
  }

  std::string str() const override {
    std::stringstream ss;
    ss << "parametrized constraint with value: "
      << this->value_;

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
};

#endif // PARAMETRIZEDCONSTRAINT_H