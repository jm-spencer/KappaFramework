#pragma once

#include "kappa/output/abstractOutput.hpp"
#include <array>
#include <memory>


namespace kappa {

template<typename T, std::size_t N>
class ArrayDistributor : public AbstractOutput<std::array<T,N>> {
public:
  ArrayDistributor(const std::array<std::shared_ptr<AbstractOutput<T>>,N> &ioutput) {
    if(ioutput.size() != N) {
      std::string err("ArrayDistributor: invalid number of outputs");
      throw std::invalid_argument(err);
    }

    for(std::size_t i = 0; i < N; i++){
      output[i] = ioutput[i];
    }
  }


  virtual void set(const std::array<T,N> &iTarget) override {
    for(std::size_t i = 0; i < N; i++) {
      output[i]->set(iTarget[i]);
    }
  }

  std::array<std::shared_ptr<AbstractOutput<T>>,N> getOutput() const {
    return output;
  };

protected:
  std::array<std::shared_ptr<AbstractOutput<T>>,N> output;
};

}
