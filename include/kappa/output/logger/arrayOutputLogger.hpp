#pragma once

#include "kappa/output/abstractOutput.hpp"
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
  ArrayOutputLogger(std::shared_ptr<AbstractOutput<std::array<T,N>>> ioutput):
    output(ioutput), prefix(""), seperator(" "), postfix("\n"), out(std::cout) {}

  ArrayOutputLogger(int iprecision, std::string iprefix, std::string iseperator, std::string ipostfix, std::shared_ptr<AbstractOutput<std::array<T,N>>> ioutput):
    output(ioutput), prefix(iprefix), seperator(iseperator), postfix(ipostfix), out(std::cout){

    out << std::setprecision(iprecision);
  }

  ArrayOutputLogger(int iprecision, std::string iprefix, std::string iseperator, std::string ipostfix, std::ostream &iout, std::shared_ptr<AbstractOutput<std::array<T,N>>> ioutput):
    output(ioutput), prefix(iprefix), seperator(iseperator), postfix(ipostfix), out(iout) {

    out << std::setprecision(iprecision);
  }

  virtual void set(const std::array<T,N> &iTarget) override {
    out << prefix;

    for(const T &i : iTarget){
      out << i << seperator;
    }

    out << postfix;

    output->set(iTarget);
  }

  std::shared_ptr<AbstractOutput<std::array<T,N>>> getOutput() const {
    return output;
  };

protected:
  std::shared_ptr<AbstractOutput<std::array<T,N>>> output{nullptr};

  std::string prefix;
  std::string seperator;
  std::string postfix;

  std::ostream &out;
};

}
