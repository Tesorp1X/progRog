"""         Gauss Method for matrix m with sizes n x n.     """

from fractions import Fraction
from os import linesep
import gilbert_matrix

# File inpur through input.txt #

def read_matrix(b, type_of_values):

    with open("input.txt") as file:
        n = int(file.readline())
        print("n = ", n)
        matr = [[] for i in range(n)]
        if type_of_values == "int":
            for i in range(n):
                matr[i] = [int(t) for t in file.readline().split()]
            line = [int(t) for t in file.readline().split()]
        elif type_of_values == "float":

            for i in range(n):
                matr[i] = [float(t) for t in file.readline().split()]

            line = [float(t) for t in file.readline().split()]
        elif type_of_values == "fraction":
            for i in range(n):
                temp = [str(t) for t in file.readline().split()]
                for j in range(n):
                    matr[j].append(Fraction(temp[j]))
            temp = [str(t) for t in file.readline().split()]
            line = []
            for f_str in temp:
                line.append(Fraction(f_str))
            
        for i in range(n):
            b.append(linesep[i])

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


def to_triangular_matrix(matr, x):
    n = len(matr)
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




def solve_gauss(matr, b):
    
    n = len(matr)

    first_line = []
    
    x = [t for t in b]
    
    mmatr = to_triangular_matrix(matr, x)
    '''line_index = 0

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
            break'''

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

    return matr


def determinant(matr):
    n = len(matr)
    x = [int(0) for i in range(n)]
    to_triangular_matrix(matr, x)
    det = 1
    for i in range(n):
        det *= matr[i][i]

if __name__ == "__main__":

    b = []
    m = []
    x = []
    det = 0
    attempt = 0
    while attempt < 10:

        value_type = input("Выбирете тип матрицы:\n1. Int\n2. float\n3. Fraction\n4. Generate randomly.\n5. Generate Gilbert matrix\n")
        
        if value_type == '1':
            value_type = "int"
            
            m = read_matrix(b, value_type)
            break
        elif value_type == '2':
            value_type = "float"
            m = read_matrix(b, value_type)
            break
        elif value_type == '3':
            value_type = "fraction"
            m = read_matrix(b, value_type)
            break
        elif value_type == '4':
            size = int(input("Введите размер: "))
            low, high = float(input("Введите нижнюю и верхнюю границы для чисел: ").split())
        elif value_type == '5':
            size = int(input("Введите размер: "))
            
        else:
            print("Error: wrong argument.")
            attempt += 1

    attempt = 0
    while attempt < 10:
        task_no = input("Выберете задание:\n1. Режить СЛАУ вида Ax = b\n2.Вычислить определитель матрицы A\n")
        if task_no == '1':
            x = solve_gauss(m, b)
            break
        elif task_no == '2':
            det = determinant(m)
            break
        else:
            attempt += 1


    if attempt != 0:
        exit(1)
    
    x = solve_gauss(m, b)

    print("\nResult vector:")
    print_vector(x)
    #print_matrix(m)
