#pragma once

#include "abstractInput.hpp"
#include "okapi/api/device/rotarysensor/continuousRotarySensor.hpp"
#include <memory>

namespace kappa {

class OkapiInput : public AbstractInput<double> {
public:
  OkapiInput(std::shared_ptr<okapi::RotarySensor> iinput, double igearRatio = 1.0);

  virtual double get() const override;

protected:
  std::shared_ptr<okapi::RotarySensor> input{nullptr};
  double gearRatio{1};
};

}
