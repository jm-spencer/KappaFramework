#pragma once

#include "kappa/input/abstractInput.hpp"

namespace kappa {

class TimeInput : public AbstractInput<double> {
public:
  TimeInput();

  virtual double get() const override;
};

}
