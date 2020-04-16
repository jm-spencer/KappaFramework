#include "kappa/tankChassis.hpp"

namespace kappa {

TankChassis::TankChassis(std::shared_ptr<AbstractOutput<double>> ileft, std::shared_ptr<AbstractOutput<double>> iright):
  left(ileft), right(iright) {}

void TankChassis::set(std::tuple<double, double> iTarget) {
  left->set(std::get<0>(iTarget));
  right->set(std::get<1>(iTarget));
}

std::tuple<std::shared_ptr<AbstractOutput<double>>, std::shared_ptr<AbstractOutput<double>>> TankChassis::getOutputs() const {
  return std::make_tuple(std::shared_ptr<AbstractOutput<double>>(left), std::shared_ptr<AbstractOutput<double>>(right));
}

}
