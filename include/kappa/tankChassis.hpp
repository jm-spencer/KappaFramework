#pragma once

#include "abstractOutput.hpp"
#include "okapi/api/device/motor/abstractMotor.hpp"
#include <utility>

namespace kappa {

template <typename T>
class TankChassis : public AbstractOutput<std::pair<T,T>> {
public:
  TankChassis(std::shared_ptr<AbstractOutput<T>> ileft, std::shared_ptr<AbstractOutput<T>> iright);

  virtual void set(std::pair<T,T> iTarget) override {
    left->set(iTarget.first);
    right->set(iTarget.second);
  }

  std::pair<std::shared_ptr<AbstractOutput<T>>, std::shared_ptr<AbstractOutput<T>>> getOutputs() const {
    return std::make_pair<std::shared_ptr<AbstractOutput<T>>, std::shared_ptr<AbstractOutput<T>>>(left, right);
  }

protected:
  std::shared_ptr<AbstractOutput<T>> left;
  std::shared_ptr<AbstractOutput<T>> right;
};

}
