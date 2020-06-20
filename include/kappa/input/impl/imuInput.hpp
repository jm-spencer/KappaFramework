#pragma once

#include "kappa/input/abstractInput.hpp"
#include "pros/imu.hpp"
#include <memory>


namespace kappa {

class ImuInput : public AbstractInput<double> {
public:
  ImuInput(const std::uint8_t port);

  std::int32_t calibrate() const;

  std::shared_ptr<pros::Imu> getInput() const;

  virtual double get() const override;

protected:
  std::shared_ptr<pros::Imu> input;
};

}
