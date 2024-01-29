#include <iostream>

#include "eigOps.h"

Eigen::MatrixXd get_rotated_vector(const Eigen::Ref<const Eigen::Matrix3d> &set_mat,
                                   const Eigen::Ref<const Eigen::Matrix3d> &fixed_mat,
                                   const Eigen::Ref<const Eigen::Vector3d> &axis,
                                   const double angle,
                                   const Eigen::Ref<const Eigen::MatrixXd> &vectors)
{
    Eigen::Matrix3d rot_mat = set_mat * Eigen::AngleAxisd(angle, axis).matrix() * fixed_mat;
    std::cout << 'Setting Matrix = ' << set_mat << std::endl;
    std::cout << 'Fixed Matrix = ' << fixed_mat << std::endl;
    std::cout << 'Axis = ' << axis << std::endl;
    std::cout << 'Angle = ' << angle << std::endl;
    std::cout << 'Vectors = ' << vectors << std::endl;
    return rot_mat * vectors;
}

