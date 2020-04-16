#include "kappa/strafeChassis.hpp"

namespace kappa {

StrafeChassis::StrafeChassis(std::shared_ptr<AbstractOutput<double>> ifrontLeft, std::shared_ptr<AbstractOutput<double>> ifrontRight,
                             std::shared_ptr<AbstractOutput<double>> ibackLeft, std::shared_ptr<AbstractOutput<double>> ibackRight):
  frontLeft(ifrontLeft), frontRight(ifrontRight), backLeft(ibackLeft), backRight(ibackRight) {}

void StrafeChassis::set(std::tuple<double,double,double,double> iTarget) {
  frontLeft->set(std::get<0>(iTarget));
  frontRight->set(std::get<1>(iTarget));
  backLeft->set(std::get<2>(iTarget));
  backRight->set(std::get<3>(iTarget));
}

std::tuple<std::shared_ptr<AbstractOutput<double>>, std::shared_ptr<AbstractOutput<double>>,
           std::shared_ptr<AbstractOutput<double>>, std::shared_ptr<AbstractOutput<double>>> StrafeChassis::getOutputs() const {
  return std::make_tuple(std::shared_ptr<AbstractOutput<double>>(frontLeft), std::shared_ptr<AbstractOutput<double>>(frontRight),
                         std::shared_ptr<AbstractOutput<double>>(backLeft),  std::shared_ptr<AbstractOutput<double>>(backRight));
}

}
