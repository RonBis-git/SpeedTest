#include <iostream>
#include "eigOps.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

namespace py = pybind11;


PYBIND11_MODULE(eigOp, m)
{
    m.def("get_rotated_vector", &get_rotated_vector, py::return_value_policy::reference_internal);
}