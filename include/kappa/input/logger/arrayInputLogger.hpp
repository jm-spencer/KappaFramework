#pragma once

#include "abstractInput.hpp"
#include <memory>
#include <array>
#include <ostream>
#include <iostream>
#include <iomanip>
#include <string>

namespace kappa {

template <typename T, std::size_t N>
class ArrayInputLogger : public AbstractInput<std::array<T,N>> {
public:
  ArrayInputLogger(std::shared_ptr<AbstractInput<std::array<T,N>>> iinput, int iprecision = 6, std::string iprefix = "", std::string iseperator = " ", std::string ipostfix = "\n", std::ostream &iout = std::cout):
    input(iinput), prefix(iprefix), seperator(iseperator), postfix(ipostfix), out(iout) {

    out << std::setprecision(iprecision);
  }

  virtual std::array<T,N> get() const override {
    std::array<T,N> values = input->get();

    out << prefix;

    for(T &i : values){
      out << i << seperator;
    }

    out << postfix;

    return values;
  }

protected:
  std::shared_ptr<AbstractInput<std::array<T,N>>> input{nullptr};

  std::string prefix;
  std::string seperator;
  std::string postfix;

  std::ostream &out;
};

}
