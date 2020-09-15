import random

def print_matrix(matr):

    n = len(matr)

    for i in range(n):
        for j in matr[i]:
            print(j, end="\t")
        print("")

def random_matrix(size, low = -10, high = 10, precision = 6, int_or_float = 1):
    matr = [[] for i in range(size)]
    for i in range(size):
        line = []
        for j in range(size):
            if (int_or_float == 1):
                line.append(random.randint(low, high))
            else:
                line.append(round(random.uniform(low, high), precision))
        matr[i] = line[:]
    return matr

if __name__ == "__main__":

    int_or_float = int(input("Какую матрицу сгененрировать?\n1. int\n2. float\n"))
    if (int_or_float == 1):
        size = int(input("Введите размер матрицы: "))
        low, high = int(input("Введите нижнюю границу: ")), int(input("Вверхнюю грницу:"))
        print(size, end="\n")
        print_matrix(random_matrix(size, low, high))


    elif (int_or_float == 2):
        size = int(input("Введите размер матрицы: "))
        low, high, precision = float(input("Введите нижнюю границу: ")), float(input("Вверхнюю грницу:")), int(input("Вверхнюю точность(int):"))
        print(size, end="\n")
        print_matrix(random_matrix(size, low, high, precision, 2))

    