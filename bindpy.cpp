#include <iostream>
#include "eigOps.h"

#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/numpy.h>

namespace py = pybind11;


PYBIND11_MODULE(cppOps, m)
{
    m.def("eig_get_rotated_vector", &eig_get_rotated_vector, py::return_value_policy::reference_internal);
}