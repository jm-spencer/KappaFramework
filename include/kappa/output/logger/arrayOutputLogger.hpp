#pragma once

#include "kappa/output/abstractOutput.hpp"
#include "kappa/output/impl/nullOutput.hpp"
#include "pros/rtos.hpp"
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
  ArrayOutputLogger(std::shared_ptr<AbstractOutput<std::array<T,N>>> ioutput = std::make_shared<NullOutput<std::array<T,N>>>()):
    ArrayOutputLogger(6, " ", " ", "\n", std::cout, ioutput) {}

  ArrayOutputLogger(int iprecision, std::string iprefix, std::string iseperator, std::string ipostfix, std::shared_ptr<AbstractOutput<std::array<T,N>>> ioutput = std::make_shared<NullOutput<std::array<T,N>>>()):
    ArrayOutputLogger(iprecision, iprefix, iseperator, ipostfix, std::cout, ioutput) {}

  ArrayOutputLogger(int iprecision, std::string iprefix, std::string iseperator, std::string ipostfix, std::ostream &iout, std::shared_ptr<AbstractOutput<std::array<T,N>>> ioutput = std::make_shared<NullOutput<std::array<T,N>>>()):
    output(ioutput), prefix(iprefix), seperator(iseperator), postfix(ipostfix), out(iout) {

    out << std::setprecision(iprecision);
  }

  virtual void set(const std::array<T,N> &itarget) override {
    out << pros::millis() << prefix;

    for(const T &i : itarget){
      out << i << seperator;
    }

    out << postfix;

    output->set(itarget);
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

extern template class ArrayOutputLogger<double, 2>;
extern template class ArrayOutputLogger<double, 3>;
extern template class ArrayOutputLogger<double, 4>;

}
