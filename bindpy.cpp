#include <iostream>
#include "eigOps.h"
#include "stltest.h"

#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/numpy.h>

#include <pybind11/stl.h>

namespace py = pybind11;

vec2D to_vec2D(py::array_t<double> array)
{

    auto buf = array.request();

    vec2D vec(buf.shape[0]);

    for (py::ssize_t i = 0; i < buf.shape[0]; i++)
    {
        vec[i].resize(buf.shape[1]);
        std::memcpy(vec[i].data(), array.data(i, 0), buf.shape[1] * sizeof(double));
    }

    return vec;
}

vec1D flatten_vec2D(const vec2D &matrix)
{
    vec1D flat;

    for (const vec1D &row : matrix)
        flat.insert(flat.end(), row.begin(), row.end());

    return flat;
}

py::array_t<double> py_stl_rotate_goniometer_vectors(py::array_t<double> setting_matrix,
                                                     py::array_t<double> fixed_matrix,
                                                     py::array_t<double> axis,
                                                     double angle,
                                                     py::array_t<double> inputVectors)
{
    py::buffer_info buffer = axis.request();
    double *ptr = static_cast<double *>(buffer.ptr);

    std::vector<double> axis_vec(ptr, ptr + buffer.size);

    vec2D inpVecs = to_vec2D(inputVectors);
    vec2D smat = to_vec2D(setting_matrix);
    vec2D fmat = to_vec2D(fixed_matrix);

    vec2D result = stl_rotate_goniometer_vectors(smat,
                                                 fmat,
                                                 axis_vec,
                                                 angle,
                                                 inpVecs);

    py::ssize_t rows = result.size();
    py::ssize_t cols = result[0].size();

    return py::array_t<double>(py::buffer_info(
        flatten_vec2D(result).data(), // pointer to data
        sizeof(double),
        py::format_descriptor<double>::format(),
        2, // ndim
        {rows, cols},
        {sizeof(double) * cols, sizeof(double)}));

    PYBIND11_MODULE(cppOps, m)
    {
        m.def("eig_get_rotated_vector", &eig_get_rotated_vector, py::return_value_policy::reference_internal);
        m.def("stl_rotate_goniometer_vectors", &py_stl_rotate_goniometer_vectors);
    }
}