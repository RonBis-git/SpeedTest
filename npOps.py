import numpy as np
from scipy.spatial.transform import Rotation

def rotate_vectors(s_mat:np.ndarray, f_mat:np.ndarray, axis:np.ndarray, angle:np.float64, vectors:np.ndarray) -> np.ndarray:
    rotvec = Rotation.as_matrix(
            Rotation.from_rotvec(angle*axis)
        )
    rot_mat = Rotation.from_matrix(
        s_mat @ rotvec @ f_mat
    )
    print(f'Setting mat = {s_mat}')
    print(f'Fixed mat = {f_mat}')
    print(f'Axis = {axis}')
    print(f'angle = {angle}')
    print(f'Vectors = {vectors}')
    return rot_mat.apply(vectors) 