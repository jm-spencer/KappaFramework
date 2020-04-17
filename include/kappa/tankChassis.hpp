#pragma once

#include "abstractOutput.hpp"
#include <array>
#include <memory>

namespace kappa {

class TankChassis : public AbstractOutput<std::array<double,2>> {
public:
  TankChassis(std::array<std::shared_ptr<AbstractOutput<double>>,2> imotors);

  /**
   * Tuple in the format {left,right}; inherits units from provided outputs
   */
  virtual void set(std::array<double,2> iTarget) override;

  std::array<std::shared_ptr<AbstractOutput<double>>,2> getOutput() const;

protected:
  std::array<std::shared_ptr<AbstractOutput<double>>,2> motors;
};

}
