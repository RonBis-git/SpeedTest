import numpy as np
from time import perf_counter
import timeit
import sys

sys.path.append("build")
import cppOps
import npOps

def operations(rows):
    return np.random.default_rng().uniform(0, 1, size=(rows, 3))


if __name__ == "__main__":
    s_mat = np.eye(3).astype(np.float64)
    print(s_mat)
    f_mat = np.array(
    [
        [0.96502798, 0.05985625, -0.25522191],
        [-0.12860378, -0.74028049, -0.65988322],
        [-0.22843393, 0.66962828, -0.70669364],
    ],
    dtype=np.float64
)
    print(f_mat)
    axis = np.array([1.0,0.0,0.0]).astype(np.float64)
    angle = np.pi/3
    vecs = operations(rows=100000)

    print('Numpy results')
    npstart = perf_counter()
    np_rotvecs = npOps.rotate_vectors(s_mat, f_mat, axis, angle, vecs)
    npstop = perf_counter()
    # print(np_rotvecs)

    print('Eigen results')
    cppstart = perf_counter()
    eig_rotvecs = cppOps.eig_get_rotated_vector(s_mat, 
                                            f_mat, 
                                            axis, 
                                            angle, 
                                            vecs.T).T
    cppstop = perf_counter()
    print(np.isclose(eig_rotvecs,np_rotvecs, rtol=1E-7, atol=1E-8))

    print('STL results')
    cppstlstart = perf_counter()
    stl_rotvecs = cppOps.stl_rotate_goniometer_vectors(s_mat, 
                                            f_mat, 
                                            axis, 
                                            angle, 
                                            vecs)
    cppstlstop = perf_counter()
    print(np.isclose(stl_rotvecs,np_rotvecs, rtol=1E-7, atol=1E-8))

    numpy_time = timeit.timeit(lambda: npOps.rotate_vectors(s_mat, f_mat, axis, angle, vecs), number=1000)

    cpp_eig_time = timeit.timeit(lambda: cppOps.eig_get_rotated_vector(s_mat, f_mat, axis, angle, vecs.T), number=1000)
    cpp_stl_time = timeit.timeit(lambda: cppOps.stl_rotate_goniometer_vectors(s_mat, f_mat, axis, angle, vecs), number=1000)


    print(f"NumPy time: {npstop-npstart} secs and {numpy_time} secs")
    print(f"C++ Eigen time: {cppstop-cppstart} secs and {cpp_eig_time} secs")
    print(f"C++ STL time: {cppstlstop-cppstlstart} secs and {cpp_stl_time} secs")