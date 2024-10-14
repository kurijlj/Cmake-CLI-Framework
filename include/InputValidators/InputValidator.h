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

  template <typename CheckDataType = bool>
  InputValidator & add_constraint(
      std::unique_ptr<Constraint<InputDataType, CheckDataType>> pconstraint
    ) {
    constraints_.push_back(std::move(pconstraint));

    return *this;
  }

  bool validate() const {
    for (auto constraint : constraints_) {
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
    for (auto constraint : constraints_) {
      ss << constraint->str() << "\n";
    }

    return ss.str();
  }

  friend std::ostream & operator<<(std::ostream & os,
      const InputValidator<InputDataType> & obj
    ) {
    os << obj.data_ << " must conform to following constraints:\n";
    for (auto constraint : obj.constraints_) {
      os << constraint->str() << "\n";
    }

    return os;
  }

private:
    class ConstraintConcept {
    public:
      virtual bool check(const InputDataType & input) const = 0;
      virtual std::string str() const = 0;
    };

    template <typename CheckDataType>
    class ConstraintModel : public ConstraintConcept {
    public:
      explicit ConstraintModel(
        const Constraint<InputDataType, CheckDataType> constraint
      ) : constraint_{std::move(constraint)}
      { }

      bool check(const InputDataType & input) const override {
          return constraint_->check(input);
      }

      std::string str() const override {
          return constraint_->str();
      }

      friend std::ostream & operator<<(
          std::ostream & os,
          const ConstraintModel<CheckDataType> & obj
        ) {
        os << obj.constraint_;

        return os;
      }

    protected:
      const Constraint<InputDataType, CheckDataType> constraint_;
    };

protected:
    const InputDataType data_;
    std::vector<std::unique_ptr<ConstraintConcept>> constraints_;
};

#endif // INPUTVALIDATOR_H