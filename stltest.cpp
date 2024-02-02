#include <stdio.h>
#include <math.h>
#include <stltest.h>

double get_norm(const vec1D &vec)
{
  return sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
}

vec1D normalize(const vec1D &vec)
{
  vec1D result(3);
  double norm = get_norm(vec);
  for (int i = 0; i < 3; i++)
    result[i] = vec[i] / norm;

  return result;
}

vec2D axis_angle_to_matrix(const vec1D &axis, const double angle)
{
  vec1D n_axis = normalize(axis);

  double ux, uy, uz;
  double csth, snth;

  double r00, r01, r02, r10, r11, r12, r20, r21, r22;

  ux = n_axis[0];
  uy = n_axis[1];
  uz = n_axis[2];
  csth = cos(angle);
  snth = sin(angle);

  r00 = csth + ux * ux * (1 - csth);
  r01 = ux * uy * (1 - csth) - uz * snth;
  r02 = ux * uz * (1 - csth) + uy * snth;

  r10 = uy * ux * (1 - csth) + uz * snth;
  r11 = csth + uy * uy * (1 - csth);
  r12 = uy * uz * (1 - csth) - ux * snth;

  r20 = ux * uz * (1 - csth) - uy * snth;
  r21 = uy * uz * (1 - csth) + ux * snth;
  r22 = csth + uz * uz * (1 - csth);

  return {{r00, r01, r02},
          {r10, r11, r12},
          {r20, r21, r22}};
}

vec2D multiply_matrix_with_vectors(const vec2D &inMatrix, const vec2D &inputVectors)
{

  std::size_t rows = inputVectors.size();

  vec2D result(rows, vec1D(3));

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < 3; j++)
    {
      result[i][0] += inMatrix[0][j] * inputVectors[i][j];
      result[i][1] += inMatrix[1][j] * inputVectors[i][j];
      result[i][2] += inMatrix[2][j] * inputVectors[i][j];
    }

  return result;
}

vec2D multiply_matrices(const vec2D &mat1, const vec2D &mat2)
{

  vec2D result(3, vec1D(3, 0));

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 3; k++)
        result[i][j] += mat1[i][k] * mat2[k][j];

  return result;
}

vec2D get_gonio_rotation_matrix(const vec2D &setting_matrix,
                                const vec2D &fixed_matrix,
                                const vec1D &axis,
                                const double angle)
{
  vec2D axisRotMat = axis_angle_to_matrix(axis, angle);
  return multiply_matrices(setting_matrix,
                           multiply_matrices(axisRotMat,
                                             fixed_matrix));
}

vec2D stl_rotate_goniometer_vectors(const vec2D &setting_matrix,
                                    const vec2D &fixed_matrix,
                                    const vec1D &axis,
                                    const double angle,
                                    const vec2D &inputArray)
{
  vec2D frs = get_gonio_rotation_matrix(setting_matrix,
                                        fixed_matrix,
                                        axis,
                                        angle);
  return multiply_matrix_with_vectors(frs, inputArray);
}