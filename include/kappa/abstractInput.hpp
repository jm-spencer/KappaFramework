#pragma once

namespace kappa {

template <typename T> class AbstractInput {
public:
  virtual T get() const = 0;
};

}
