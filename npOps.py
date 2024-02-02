import numpy as np
from scipy.spatial.transform import Rotation

def rotate_vectors(s_mat:np.ndarray, f_mat:np.ndarray, axis:np.ndarray, angle:np.float64, vectors:np.ndarray) -> np.ndarray:
    rotvec = Rotation.as_matrix(
            Rotation.from_rotvec(angle*axis)
        )
    rot_mat = Rotation.from_matrix(
        s_mat @ rotvec @ f_mat
    )
    return rot_mat.apply(vectors) 