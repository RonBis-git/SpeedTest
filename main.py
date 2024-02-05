import numpy as np

from time import perf_counter
import timeit
import sys

sys.path.append("build")
import cppOps
import npOps


def create_vectors(sample_size):
    return np.random.default_rng().uniform(0, 1, size=(sample_size, 3))


def create_axis():
    return np.random.default_rng().uniform(0, 5, size=3)


def fixed_and_setting():
    # Fixed and setting matrix have been hardcoded from an experiment file.
    s_mat = np.eye(3).astype(np.float64)
    f_mat = np.array(
        [
            [0.96502798, 0.05985625, -0.25522191],
            [-0.12860378, -0.74028049, -0.65988322],
            [-0.22843393, 0.66962828, -0.70669364],
        ],
        dtype=np.float64,
    )
    return s_mat, f_mat


def get_run_times(s_mat, f_mat, axis, angle, vecs):
    # print("Numpy results")
    npstart = perf_counter()
    np_rotvecs = npOps.rotate_vectors(s_mat, f_mat, axis, angle, vecs)
    npstop = perf_counter()
    # print(np_rotvecs)

    # print("Eigen results")
    cpp_eig_start = perf_counter()
    eig_rotvecs = cppOps.eig_get_rotated_vector(s_mat, f_mat, axis, angle, vecs.T).T
    cpp_eig_stop = perf_counter()
    # print(np.isclose(eig_rotvecs, np_rotvecs, rtol=1e-7, atol=1e-8))

    # print("STL results")
    cpp_stl_start = perf_counter()
    stl_rotvecs = cppOps.stl_rotate_goniometer_vectors(s_mat, f_mat, axis, angle, vecs)
    cpp_stl_stop = perf_counter()
    # print(np.isclose(stl_rotvecs, np_rotvecs, rtol=1e-7, atol=1e-8))

    # numpy_time = timeit.timeit(
    #     lambda: npOps.rotate_vectors(s_mat, f_mat, axis, angle, vecs), number=1000
    # )

    # cpp_eig_time = timeit.timeit(
    #     lambda: cppOps.eig_get_rotated_vector(s_mat, f_mat, axis, angle, vecs.T),
    #     number=1000,
    # )
    # cpp_stl_time = timeit.timeit(
    #     lambda: cppOps.stl_rotate_goniometer_vectors(s_mat, f_mat, axis, angle, vecs),
    #     number=1000,
    # )

    # print(f"NumPy time: {npstop-npstart} secs and {numpy_time} secs")
    # print(f"C++ Eigen time: {cppstop-cppstart} secs and {cpp_eig_time} secs")
    # print(f"C++ STL time: {cppstlstop-cppstlstart} secs and {cpp_stl_time} secs")

    return npstop - npstart, cpp_eig_stop - cpp_eig_start, cpp_stl_stop - cpp_stl_start

def plot_run_times(sample_size, np_times, eig_times, stl_times):
    import matplotlib.pyplot as plt
    
    plt.plot(sample_size,np_times,label='numpy')
    plt.plot(sample_size,eig_times,label='Eigen')
    plt.plot(sample_size,stl_times,label='std::vector')

    plt.xlabel('Vector Sample Size')
    plt.ylabel('Run time (secs)')

    plt.legend(loc='best')
    plt.xscale('log')
    plt.yscale('log')

    plt.show()


if __name__ == "__main__":

    # Input params
    angle = np.pi / 3
    s_mat, f_mat = fixed_and_setting()
    axis = create_axis()

    # Initialising sample_size and output timing arrays

    sample_size = np.array([10, 100, 1000, 10_000, 100_000, 1_000_000])
    np_times = []
    eig_times = []
    stl_times = []

    # Running the timing function for each sample size

    for i in range(len(sample_size)):
        np_t, eig_t, stl_t = get_run_times(
            s_mat, f_mat, axis, angle, create_vectors(sample_size[i])
        )
        np_times.append(np_t)
        eig_times.append(eig_t)
        stl_times.append(stl_t)

    print(np_times)
    #Plotting the run times 
    plot_run_times(sample_size, np_times, eig_times, stl_times)
