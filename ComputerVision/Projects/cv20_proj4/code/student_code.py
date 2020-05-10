import numpy as np


def calculate_projection_matrix(points_2d, points_3d):
    """
    To solve for the projection matrix. You need to set up a system of
    equations using the corresponding 2D and 3D points:

                                                      [ M11      [ u1
                                                        M12        v1
                                                        M13        .
                                                        M14        .
    [ X1 Y1 Z1 1 0  0  0  0 -u1*X1 -u1*Y1 -u1*Z1        M21        .
      0  0  0  0 X1 Y1 Z1 1 -v1*X1 -v1*Y1 -v1*Z1        M22        .
      .  .  .  . .  .  .  .    .     .      .       *   M23   =    .
      Xn Yn Zn 1 0  0  0  0 -un*Xn -un*Yn -un*Zn        M24        .
      0  0  0  0 Xn Yn Zn 1 -vn*Xn -vn*Yn -vn*Zn ]      M31        .
                                                        M32        un
                                                        M33 ]      vn ]

    Then you can solve this using least squares with np.linalg.lstsq() or SVD.
    Notice you obtain 2 equations for each corresponding 2D and 3D point
    pair. To solve this, you need at least 6 point pairs.

    Args:
    -   points_2d: A numpy array of shape (N, 2)
    -   points_2d: A numpy array of shape (N, 3)
    Returns:
    -   M: A numpy array of shape (3, 4) representing the projection matrix
    """

    # Placeholder M matrix. It leads to a high residual. Your total residual
    # should be less than 1.
    M = np.asarray([[0.1768, 0.7018, 0.7948, 0.4613],
                    [0.6750, 0.3152, 0.1136, 0.0480],
                    [0.1020, 0.1725, 0.7244, 0.9932]])
    ###########################################################################
    # TODO: YOUR PROJECTION MATRIX CALCULATION CODE HERE
    ###########################################################################
    # raise NotImplementedError('`calculate_projection_matrix` function in ' +
    #     '`student_code.py` needs to be implemented')
    # Dims
    num_points = points_3d.shape[0]
    num_variables = 11
    # AM = b
    A = np.zeros((2*num_points, num_variables), dtype=np.float)
    b = np.zeros((2*num_points), dtype=np.float)
    # Form set of linear equations
    for ix, ([u, v], [x, y, z]) in enumerate(zip(points_2d, points_3d)):
        A[2*ix, :]   = [x, y, z, 1, 0, 0, 0, 0, -u*x, -u*y, -u*z]
        A[2*ix+1, :] = [0, 0, 0, 0, x, y, z, 1, -v*x, -v*y, -v*z]
        b[2*ix]      = u
        b[2*ix+1]    = v
    # Solve for M
    # M = (A'A)^-1.A'b
    M = np.linalg.inv(A.T@A) @ A.T @ b
    # M = np.linalg.lstsq(A, b)[0]
    M = np.append(M, 1).reshape((3, 4))
    ###########################################################################
    # END OF YOUR CODE
    ###########################################################################
    return M

def calculate_camera_center(M):
    """
    Returns the camera center matrix for a given projection matrix.

    The center of the camera C can be found by:

        C = -Q^(-1)m4

    where your project matrix M = (Q | m4).

    Args:
    -   M: A numpy array of shape (3, 4) representing the projection matrix

    Returns:
    -   cc: A numpy array of shape (1, 3) representing the camera center
            location in world coordinates
    """
    # Placeholder camera center. In the visualization, you will see this camera
    # location is clearly incorrect, placing it in the center of the room where
    # it would not see all of the points.
    cc = np.asarray([1, 1, 1])
    ###########################################################################
    # TODO: YOUR CAMERA CENTER CALCULATION CODE HERE
    ###########################################################################

    #raise NotImplementedError('`calculate_camera_center` function in ' +
    #    '`student_code.py` needs to be implemented')

    Q = M[:, :3]
    m4 = M[:, 3]
    cc = -np.linalg.inv(Q) @ m4
    
    ###########################################################################
    # END OF YOUR CODE
    ###########################################################################
    return cc

def estimate_fundamental_matrix(points_a, points_b):
    """
    Calculates the fundamental matrix. Try to implement this function as
    efficiently as possible. It will be called repeatedly in part 3.

    You must normalize your coordinates through linear transformations as
    described on the project webpage before you compute the fundamental
    matrix.

    Args:
    -   points_a: A numpy array of shape (N, 2) representing the 2D points in
                  image A
    -   points_b: A numpy array of shape (N, 2) representing the 2D points in
                  image B

    Returns:
    -   F: A numpy array of shape (3, 3) representing the fundamental matrix
    """
    # Placeholder fundamental matrix
    F = np.asarray([[0, 0, -0.0004],
                    [0, 0, 0.0032],
                    [0, -0.0044, 0.1034]])
    ###########################################################################
    # TODO: YOUR FUNDAMENTAL MATRIX ESTIMATION CODE HERE
    ###########################################################################

    #raise NotImplementedError('`estimate_fundamental_matrix` function in ' +
    #    '`student_code.py` needs to be implemented')
    num_points = points_a.shape[0]
    num_variables = 9
    # AF = 0
    A = np.zeros((num_points, num_variables), dtype=np.float)
    # Form set of linear equations
    for ix, ([u1, v1], [u2, v2]) in enumerate(zip(points_a, points_b)):
        A[ix, :] = [u2*u1, u2*v1, u2, v2*u1, v2*v1, v2, u1, v1, 1]
    # Solve for F subject to |F| = 1 (SVD Trick)
    u, s, vt = np.linalg.svd(A.T @ A)
    F = vt[-1, :].reshape((3, 3))
    ###########################################################################
    # END OF YOUR CODE
    ###########################################################################
    return F

def ransac_fundamental_matrix(matches_a, matches_b):
    """
    Find the best fundamental matrix using RANSAC on potentially matching
    points. Your RANSAC loop should contain a call to
    estimate_fundamental_matrix() which you wrote in part 2.

    If you are trying to produce an uncluttered visualization of epipolar
    lines, you may want to return no more than 100 points for either left or
    right images.

    Args:
    -   matches_a: A numpy array of shape (N, 2) representing the coordinates
                   of possibly matching points from image A
    -   matches_b: A numpy array of shape (N, 2) representing the coordinates
                   of possibly matching points from image B
    Each row is a correspondence (e.g. row 42 of matches_a is a point that
    corresponds to row 42 of matches_b)

    Returns:
    -   best_F: A numpy array of shape (3, 3) representing the best fundamental
                matrix estimation
    -   inliers_a: A numpy array of shape (M, 2) representing the subset of
                   corresponding points from image A that are inliers with
                   respect to best_F
    -   inliers_b: A numpy array of shape (M, 2) representing the subset of
                   corresponding points from image B that are inliers with
                   respect to best_F
    """

    # Placeholder values
    best_F = estimate_fundamental_matrix(matches_a[:10, :], matches_b[:10, :])
    inliers_a = matches_a[:100, :]
    inliers_b = matches_b[:100, :]
    ###########################################################################
    # TODO: YOUR RANSAC CODE HERE
    ###########################################################################
    
    raise NotImplementedError('`ransac_fundamental_matrix` function in ' +
        '`student_code.py` needs to be implemented')
    ###########################################################################
    # END OF YOUR CODE
    ###########################################################################
    return best_F, inliers_a, inliers_b