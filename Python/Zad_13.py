import numpy as np


def zadanie_1():
    def squared_matrix(n: int):
        matrix = np.ones((n, n), dtype=np.int64)

        for row in range(n):
            for col in range(1, n):
                matrix[row, col] = pow(row + 1, col)

        print(matrix)

    squared_matrix(6)


def zadanie_2():
    def squared_matrix(n: int):
        matrix = np.arange(1, n**2 + 1, dtype=np.int64)
        matrix = matrix.reshape(n, n)

        for row in range(1, n, 2):
            matrix[row, :] = np.flip(matrix[row])

        print(matrix)

    squared_matrix(6)


def zadanie_3():
    def squared_matrix(n: int):
        matrix = np.zeros((n, n), dtype=np.int64)

        for row in range(n):
            matrix[row, :] = np.flip(matrix[row])

        print(matrix)

    squared_matrix(6)

    squared_matrix(4)


if __name__ == "__main__":
    zadanie_3()
