#ifndef STLTEST_H
#define STLTEST_H

#include <vector>

#endif

using vec2D = std::vector<std::vector<double>>;
using vec1D = std::vector<double>;

double get_norm(const vec1D &);
vec1D normalize(const vec1D &);
vec2D axis_angle_to_matrix(const vec1D &, const double);
vec2D multiply_matrices(const vec2D &, const vec2D &);
vec2D multiply_matrix_with_vectors(const vec2D &, const vec2D &);
vec2D get_gonio_rotation_matrix(const vec2D &,
                                const vec2D &,
                                const vec1D &,
                                const double);
vec2D stl_rotate_goniometer_vectors(const vec2D &,
                                    const vec2D &,
                                    const vec1D &,
                                    const double,
                                    const vec2D &);