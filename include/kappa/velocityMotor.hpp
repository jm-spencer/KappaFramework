#pragma once
#include "abstractOutput.hpp"
#include "okapi/api/device/motor/abstractMotor.hpp"

namespace kappa {

class VelocityMotor : public AbstractOutput<double> {
public:
  VelocityMotor(std::shared_ptr<okapi::AbstractMotor> imotor);

  virtual void set(double iTarget) override;

  std::shared_ptr<okapi::AbstractMotor> getMotor() const;

protected:
  std::shared_ptr<okapi::AbstractMotor> motor;
};

}
