import numpy as np


def np_operation(rows):
    mat = np.random.default_rng().uniform(0, 1, size=(rows, 3))
    d_mat = np.arange(9).reshape(3, 3)
    print(d_mat)
    d0 = d_mat[2,:]
    print(d0)


if __name__ == "__main__":
    np_operation(2)
