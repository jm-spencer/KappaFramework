#pragma once

#include "abstractOutput.hpp"
#include <tuple>
#include <memory>

namespace kappa {

class StrafeChassis : public AbstractOutput<std::tuple<double,double,double,double>> {
public:
  StrafeChassis(std::shared_ptr<AbstractOutput<double>> ifrontLeft, std::shared_ptr<AbstractOutput<double>> ifrontRight,
                std::shared_ptr<AbstractOutput<double>> ibackLeft, std::shared_ptr<AbstractOutput<double>> ibackRight);

  virtual void set(std::tuple<double,double,double,double> iTarget) override;

  std::tuple<std::shared_ptr<AbstractOutput<double>>, std::shared_ptr<AbstractOutput<double>>,
             std::shared_ptr<AbstractOutput<double>>, std::shared_ptr<AbstractOutput<double>>> getOutputs() const;

protected:
  std::shared_ptr<AbstractOutput<double>> frontLeft;
  std::shared_ptr<AbstractOutput<double>> frontRight;
  std::shared_ptr<AbstractOutput<double>> backLeft;
  std::shared_ptr<AbstractOutput<double>> backRight;
};

}
