// Constraint.h
#ifndef CONSTRAINT_H
#define CONSTRAINT_H

// ----------------------------------------------------------------------------
// Constraint
// ----------------------------------------------------------------------------
//
// Description: Abstract base class for all constraints that are to be used for
//              the input validation
//
// ----------------------------------------------------------------------------
template <typename InputDataType, typename CheckDataType = bool>
class Constraint {
public:
  virtual bool check(const InputDataType & input) const = 0;
  virtual std::string str() const = 0;

protected:
  CheckDataType value_;
};

#endif // CONSTRAINT_H