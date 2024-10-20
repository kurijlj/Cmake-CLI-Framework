// Constraint.h
#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include <functional>

// ----------------------------------------------------------------------------
// Constraint
// ----------------------------------------------------------------------------
//
// Description: Abstract base class for all constraints that are to be used for
//              the input validation
//
// ----------------------------------------------------------------------------
template <typename InputDataType>
class Constraint {
public:
  ~Constraint() = default;

  virtual bool check(const InputDataType & input) const = 0;
  virtual std::string str() const = 0;
};

#endif // CONSTRAINT_H