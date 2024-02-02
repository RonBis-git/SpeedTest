#include <iostream>

#include "eigOps.h"

Eigen::Matrix3Xd eig_get_rotated_vector(const Eigen::Ref<const Eigen::Matrix3d> &set_mat,
                               const Eigen::Ref<const Eigen::Matrix3d> &fixed_mat,
                               const Eigen::Ref<const Eigen::Vector3d> &axis,
                               const double angle,
                               const Eigen::Ref<const Eigen::Matrix3Xd> &vectors)
{
    Eigen::Matrix3d rot_mat;
    rot_mat =  set_mat* Eigen::AngleAxisd(angle, axis.normalized()).toRotationMatrix() * fixed_mat;
    return rot_mat * vectors;
}
