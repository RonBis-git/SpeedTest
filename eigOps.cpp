#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>


Eigen::MatrixXd get_rotated_vector(const Eigen::Ref<const Eigen::Matrix3d>& set_mat, const Eigen::Ref<const Eigen::Matrix3d>& fixed_mat, const Eigen::Ref<const Eigen::Vector3d>& axis, const double angle, const Eigen::Ref<const Eigen::MatrixXd>& vectors)
{
    Eigen::Matrix3d rot_mat = set_mat*Eigen::AngleAxisd(angle,axis).matrix()*fixed_mat;
    return rot_mat*vectors;
}



int main()
{
    return 0;
}