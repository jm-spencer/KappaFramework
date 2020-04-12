#pragma once
#include "abstractOutput.hpp"
#include "okapi/api/device/motor/abstractMotor.hpp"

namespace kappa {

class VoltageMotor : public AbstractOutput<double> {
public:
  VoltageMotor(std::shared_ptr<okapi::AbstractMotor> imotor);

  virtual void set(double iTarget) override;

  std::shared_ptr<okapi::AbstractMotor> getMotor() const;

protected:
  std::shared_ptr<okapi::AbstractMotor> motor;
};

}
