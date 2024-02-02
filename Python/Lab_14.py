import numpy as np


def zadanie_1():
    matrix = np.arange(1, 21).reshape((5, 4), order="F")

    print(matrix)


def zadanie_2():
    def m_cramera(A: np.ndarray, b: np.ndarray):
        s_A = A.shape

        if s_A[0] == s_A[1]:
            det_A = np.linalg.det(A)
            n = s_A[0]
            rg = range(n)

            result = np.zeros((n, 1))

            for i in rg:
                I = A.copy()

                for j in rg:
                    I[j, i] = b[j, 0]

                det_i = np.linalg.det(I)
                result[i, 0] = det_i / det_A

            print(result)

        else:
            raise IndexError("Matrix must have as many rows as unknown values.")

    A = np.array(
        [
            [3, 1, 3],
            [2, 0, 4],
            [2, 1, 3],
        ]
    )
    b = np.array(
        [
            0,
            5,
            2,
        ]
    ).reshape((3, 1))

    m_cramera(A, b)


if __name__ == "__main__":
    zadanie_2()
