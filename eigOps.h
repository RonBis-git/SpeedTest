#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>


Eigen::MatrixXd get_rotated_vector(const Eigen::Ref<const Eigen::Matrix3d> &,
                                   const Eigen::Ref<const Eigen::Matrix3d> &,
                                   const Eigen::Ref<const Eigen::Vector3d> &,
                                   const double,
                                   const Eigen::Ref<const Eigen::MatrixXd> &);