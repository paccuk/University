"""
Arithmetic on matrix.
"""
RED = "\033[0;31m"
END = "\033[0m"


def sum_matrixes(A: list[list], B: list[list]) -> list[list] | None:
    if len(A) != len(B) and len(A[0]) != len(B[0]):
        print(
            RED
            + "Two matrices must have an equal number of rows and columns to be added!"
            + END
        )
        return None

    return [[nums[0] + nums[1] for nums in zip(row[0], row[1])] for row in zip(A, B)]


def add_const_matrix(const, A: list[list]) -> list[list]:
    return [[const + num for num in row] for row in A]


if __name__ == "__main__":
    add_const_matrix(
        10,
        [[3, 2, 1, 0], [6, 5, 4, 3], [9, 8, 7, 6]],
    )
