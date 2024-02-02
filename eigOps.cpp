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
    // Eigen::Affine3d q;
    // rot_mat.translation() << 0.0, 0.0, 0.0;
    // q.linear() = set_mat* Eigen::AngleAxisd(angle, axis.normalized()).toRotationMatrix() * fixed_mat;
    // std::cout << "Setting Matrix = " << set_mat << std::endl;
    // std::cout << "Fixed Matrix = " << fixed_mat << std::endl;
    // std::cout << "Axis = " << axis.normalized() << std::endl;
    // std::cout << "Angle = " << angle << std::endl;
    // // std::cout << "Vectors = " << vectors << std::endl;
    // std::cout << "Rows = " << vectors.rows() << "Columns = " << vectors.cols() << std::endl;
    // std::cout << "Rotation Matrix = " << q.linear() << std::endl;
    return rot_mat * vectors;
}

void print_passed(const Eigen::Ref<const Eigen::RowVector3d> &mat)
{
    std::cout << mat << std::endl;
}
