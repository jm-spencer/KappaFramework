#pragma once

#include "abstractOutput.hpp"
#include <tuple>
#include <memory>

namespace kappa {

class TankChassis : public AbstractOutput<std::tuple<double,double>> {
public:
  TankChassis(std::shared_ptr<AbstractOutput<double>> ileft, std::shared_ptr<AbstractOutput<double>> iright);

  virtual void set(std::tuple<double,double> iTarget) override;

  std::tuple<std::shared_ptr<AbstractOutput<double>>, std::shared_ptr<AbstractOutput<double>>> getOutputs() const;

protected:
  std::shared_ptr<AbstractOutput<double>> left;
  std::shared_ptr<AbstractOutput<double>> right;
};

}
