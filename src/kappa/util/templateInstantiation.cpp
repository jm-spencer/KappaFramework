#include "kappa/api.hpp"

namespace kappa {

template class ArrayInputLogger<double, 2>;
template class ArrayInputLogger<double, 3>;
template class ArrayInputLogger<double, 4>;

template class InputLogger<double>;

template class ArrayOutputLogger<double, 2>;
template class ArrayOutputLogger<double, 3>;
template class ArrayOutputLogger<double, 4>;

template class OutputLogger<double>;

template class TupleOutputLogger<double,double>;
template class TupleOutputLogger<double,double,double>;

template class ArrayDistributor<double, 2>;
template class ArrayDistributor<double, 4>;

template class ArrayOutputClamp<double, 2>;
template class ArrayOutputClamp<double, 4>;

template class OutputClamp<double>;

}
