#pragma once

#include "abstractOutput.hpp"
#include <memory>
#include <array>
#include <ostream>
#include <iostream>
#include <iomanip>
#include <string>

namespace kappa {

template <typename T, std::size_t N>
class ArrayOutputLogger : public AbstractOutput<std::array<T,N>> {
public:
  ArrayOutputLogger(std::shared_ptr<AbstractOutput<std::array<T,N>>> ioutput, int iprecision = 6, std::string iprefix = "", std::string iseperator = " ", std::string ipostfix = "\n", std::ostream &iout = std::cout):
    output(ioutput), prefix(iprefix), seperator(iseperator), postfix(ipostfix), out(iout) {

    out << std::setprecision(iprecision);
  }

  virtual void set(std::array<T,N> iTarget) override {
    out << prefix;

    for(T &i : iTarget){
      out << i << seperator;
    }

    out << postfix;

    output->set(iTarget);
  }

protected:
  std::shared_ptr<AbstractOutput<std::array<T,N>>> output{nullptr};

  std::string prefix;
  std::string seperator;
  std::string postfix;

  std::ostream &out;
};

}
