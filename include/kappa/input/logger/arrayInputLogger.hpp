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
    input(iinput), prefix(""), seperator(" "), postfix("\n"), out(std::cout) {}

  ArrayInputLogger(int iprecision, std::string iprefix, std::string iseperator, std::string ipostfix, std::shared_ptr<AbstractInput<std::array<T,N>>> iinput):
    input(iinput), prefix(iprefix), seperator(iseperator), postfix(ipostfix), out(std::cout) {

    out << std::setprecision(iprecision);
  }

  ArrayInputLogger(int iprecision, std::string iprefix, std::string iseperator, std::string ipostfix, std::ostream &iout, std::shared_ptr<AbstractInput<std::array<T,N>>> iinput):
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

}
