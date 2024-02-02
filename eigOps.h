#ifndef EIGOPS_H
#define EIGOPS_H
#endif

#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>

Eigen::Matrix3Xd eig_get_rotated_vector(const Eigen::Ref<const Eigen::Matrix3d> &,
                               const Eigen::Ref<const Eigen::Matrix3d> &,
                               const Eigen::Ref<const Eigen::Vector3d> &,
                               const double,
                               const Eigen::Ref<const Eigen::Matrix3Xd> &);