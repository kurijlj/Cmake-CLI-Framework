// InputValidator.h
#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <memory>

#include "Constraint.h"

template <typename InputDataType>
class InputValidator {
public:
  explicit InputValidator(const InputDataType & data) : data_(data) { }
  ~InputValidator() = default;

  InputValidator & add_constraint(
      std::unique_ptr<Constraint<InputDataType>> pimpl
    ) {
    constraints_.push_back(std::move(pimpl));

    return *this;
  }

  bool validate() const {
    for (auto && constraint : constraints_) {
      if (!constraint->check(data_)) {
        std::cerr << data_
          << " doesn't pass check against"
          << constraint
          << "\n";

        return false;
      }
    }

    return true;
  }

  std::string str() const {
    std::stringstream ss;
    ss << data_ << " must conform to following constraints:\n";
    for (auto && constraint : constraints_) {
      ss << constraint->str() << "\n";
    }

    return ss.str();
  }

  friend std::ostream & operator<<(std::ostream & os,
      const InputValidator<InputDataType> & obj
    ) {
    os << obj.data_ << " must conform to following constraints:\n";
    for (auto && constraint : obj.constraints_) {
      os << constraint->str() << "\n";
    }

    return os;
  }

protected:
    const InputDataType data_;
    std::vector<std::unique_ptr<Constraint<InputDataType>>> constraints_;
};

#endif // INPUTVALIDATOR_H