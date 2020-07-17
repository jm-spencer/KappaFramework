#pragma once

#include "kappa/input/abstractInput.hpp"
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
  ArrayInputLogger(std::shared_ptr<AbstractInput<std::array<T,N>>> iinput):
    ArrayInputLogger(6, " ", " ", "\n", std::cout, iinput) {}

  ArrayInputLogger(int iprecision, std::string iprefix, std::string iseperator, std::string ipostfix, std::shared_ptr<AbstractInput<std::array<T,N>>> iinput):
    ArrayInputLogger(iprecision, iprefix, iseperator, ipostfix, std::cout, iinput) {}

  ArrayInputLogger(int iprecision, std::string iprefix, std::string iseperator, std::string ipostfix, std::ostream &iout, std::shared_ptr<AbstractInput<std::array<T,N>>> iinput):
    input(iinput), prefix(iprefix), seperator(iseperator), postfix(ipostfix), out(iout) {

    out << std::setprecision(iprecision);
  }

  virtual std::array<T,N> get() const override {
    std::array<T,N> values = input->get();

    out << pros::millis() << prefix;

    for(T &i : values){
      out << i << seperator;
    }

    out << postfix;

    return values;
  }

  std::shared_ptr<AbstractInput<std::array<T,N>>> getInput() const {
    return input;
  }

protected:
  std::shared_ptr<AbstractInput<std::array<T,N>>> input{nullptr};

  std::string prefix;
  std::string seperator;
  std::string postfix;

  std::ostream &out;
};

extern template class ArrayInputLogger<double, 2>;
extern template class ArrayInputLogger<double, 3>;
extern template class ArrayInputLogger<double, 4>;

}
