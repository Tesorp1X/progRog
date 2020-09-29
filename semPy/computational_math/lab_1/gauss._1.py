"""         Gauss Method for matrix m with sizes n x n.     """


# File inpur through input.txt #

def read_matrix(b, isInt=True):

    with open("input.txt") as file:
        n = int(file.readline())
        print("n = ", n)
        matr = [[] for i in range(n)]
        if isInt:
            for i in range(n):
                matr[i] = [int(t) for t in file.readline().split()]
        else:
            for i in range(n):
                matr[i] = [float(t) for t in file.readline().split()]
            '''matr = file.readlines()
            del matr[0]
            matr = [[float(n) for n in x.split()] for x in matr]'''

            line = [float(t) for t in file.readline().split()]
            for i in range(n):
                b.append(line[i])

    print("Got matrix:")
    print_matrix(matr)

    return matr
        
def print_matrix(matr):

    n = len(matr)

    for i in range(n):
        for j in matr[i]:
            print(j, end="\t")
        print("\n")
        
def print_vector(vector):
    for num in vector:
        print('|', num)

def swap_lines(m, i, j):
    temp = m[i]
    m[i] = m[j]
    m[j] = m[i]


def solve_gauss(matr, b):
    
    n = len(matr)

    first_line = []
    
    x = [t for t in b]
    

    line_index = 0

    while (line_index < n):

        if (matr[line_index][line_index] != 0):

            first_line = matr[line_index]
            x_index = line_index
            for this_line in matr[(line_index + 1)::]:
                x_index += 1
                if (this_line[line_index] != 0):

                    a = this_line[line_index]

                    for i in range(line_index, n):

                        this_line[i] -= float((first_line[i] / first_line[line_index]) * a)
    
                    x[x_index] -= float((x[line_index] / first_line[line_index]) * a)

            line_index += 1

        elif (line_index < n):
            swap_lines(matr, line_index, line_index + 1)
        else:
            break

    if matr[n - 1][n - 1] != 0:
        x[n - 1] /= matr[n - 1][n - 1]
    i = n - 2

    while i >= 0:
        if matr[i][i] != 0:
            sum = 0
            for k in range(i + 1, n):
                sum += matr[i][k] * x[k]
            x[i] = (x[i] - sum) / matr[i][i]
            i -= 1
        else:
            print("Система имеет бесконечное кол-во решений.")
            break

    return x





if __name__ == "__main__":


    attempt = 0
    while attempt < 10:

        is_int = input("Выбирете тип матрицы:\n1. Int\n2. float\n3. Generate randomly.\n")
        
        if is_int == '1':
            is_int = True
            break
        elif is_int == '2':
            is_int = False
            break
        elif is_int == '3':
            size = int(input("Введите размер: "))
            low, high = float(input("Введите нижнюю и верхнюю границы для чисел: ").split())

        else:
            print("Error: wrong argument.")
            attempt += 1

    if attempt != 0:
        exit(1)
    
    b = []
    m = read_matrix(b, is_int)
    x = solve_gauss(m, b)

    print("\nResult vector:")
    print_vector(x)
    #print_matrix(m)
