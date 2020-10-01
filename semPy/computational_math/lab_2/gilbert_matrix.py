from fractions import Fraction

def generate_gilbert_matrix(size):
    matr = [[] for i in range(size)]
    for i in range(size):
        for j in range(size):
            matr[i][j] = Fraction(1, i + j + 1)
    return matr