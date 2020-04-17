#pragma once

#include "abstractOutput.hpp"
#include <array>
#include <memory>

namespace kappa {

class StrafeChassis : public AbstractOutput<std::array<double,4>> {
public:
  StrafeChassis(std::array<std::shared_ptr<AbstractOutput<double>>,4> imotors);

  /**
   * Tuple in the format {frontLeft, frontRight, backLeft, backRight}; inherits units from provided outputs
   */
  virtual void set(std::array<double,4> iTarget) override;

  std::array<std::shared_ptr<AbstractOutput<double>>,4> getOutput() const;

protected:
  std::array<std::shared_ptr<AbstractOutput<double>>,4> motors;
};

}
