import numpy as np

import sys

sys.path.append("build")
import cppOps
import npOps

def operations(rows):
    return np.random.default_rng().uniform(0, 1, size=(rows, 3))


if __name__ == "__main__":
    s_mat = np.arange(9).reshape(3, 3)
    print(s_mat)
    f_mat = np.arange(100,109).reshape(3,3)
    print(f_mat)
    axis = np.random.default_rng().uniform(0,3,size=3)
    angle = np.pi/4
    vecs = operations(rows=2)

    print('Numpy results')
    np_rotvecs = npOps.rotate_vectors(s_mat, f_mat, axis, angle, vecs)
    print(np_rotvecs)

    print('Eigen results')
    eig_rotvecs = cppOps.get_rotated_vectors(s_mat, f_mat, axis, angle, vecs)
    print(eig_rotvecs)

