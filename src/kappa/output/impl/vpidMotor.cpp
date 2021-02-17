#include "kappa/output/impl/vpidMotor.hpp"

namespace kappa {

kappa::VPidSubController makeVPIDMotor(
  std::int8_t iport,
  kappa::VPidSubController::Gains igains,
  double iconversion,
  double ioutputMin,
  double ioutputMax,
  std::unique_ptr<okapi::Filter> isensorFilter,
  std::unique_ptr<okapi::Filter> icontrollerFilter){

  auto motor = std::make_shared<okapi::Motor>(iport);

  return
    kappa::VPidSubController(igains, ioutputMin, ioutputMax, std::move(icontrollerFilter),
      std::make_shared<kappa::InputDifferentiator<double>>(iconversion, std::move(isensorFilter),
      std::make_shared<kappa::OkapiInput>(motor->getEncoder())
    ),
    std::make_shared<kappa::VoltageMotor>(motor)
  );
}

kappa::VPidSubController makeVPIDMotor(
  std::shared_ptr<okapi::AbstractMotor> imotor,
  kappa::VPidSubController::Gains igains,
  double iconversion,
  double ioutputMin,
  double ioutputMax,
  std::unique_ptr<okapi::Filter> isensorFilter,
  std::unique_ptr<okapi::Filter> icontrollerFilter){

  return
    kappa::VPidSubController(igains, ioutputMin, ioutputMax, std::move(icontrollerFilter),
      std::make_shared<kappa::InputDifferentiator<double>>(iconversion, std::move(isensorFilter),
      std::make_shared<kappa::OkapiInput>(imotor->getEncoder())
    ),
    std::make_shared<kappa::VoltageMotor>(imotor)
  );
}

kappa::VPidSubController makeVPIDMotor(
  std::shared_ptr<kappa::VoltageMotor> imotor,
  kappa::VPidSubController::Gains igains,
  double iconversion,
  double ioutputMin,
  double ioutputMax,
  std::unique_ptr<okapi::Filter> isensorFilter,
  std::unique_ptr<okapi::Filter> icontrollerFilter){

  return
    kappa::VPidSubController(igains, ioutputMin, ioutputMax, std::move(icontrollerFilter),
      std::make_shared<kappa::InputDifferentiator<double>>(iconversion, std::move(isensorFilter),
      std::make_shared<kappa::OkapiInput>(imotor->getMotor()->getEncoder())
    ),
    imotor
  );
}

}
