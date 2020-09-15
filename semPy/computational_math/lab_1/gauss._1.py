"""         Gauss Method for matrix m with sizes n x n.     """


# File inpur through input.txt #

def read_matrix(isInt=True):

    with open("input.txt") as file:
        n = int(file.readline())
        print("n = ", n)
        if isInt:
            matr = [[] for i in range(n)]
            for i in range(n):
                matr[i] = [int(t) for t in file.readline().split()]
        else:
            matr = file.readlines()
            del matr[0]
            matr = [[float(n) for n in x.split()] for x in matr]
    

    print("Got matrix:")
    print_matrix(matr)

    return matr
        
def print_matrix(matr):

    n = len(matr)

    for i in range(n):
        for j in matr[i]:
            print(j, end="\t")
        print("\n")
        

def swap_lines(m, i, j):
    temp = m[i]
    m[i] = m[j]
    m[j] = m[i]


def solve_gauss(matr):
    
    n = len(matr)

    first_line = []
    
    line_index = 0
    while (line_index < n):
        if (matr[line_index][line_index] != 0):
            first_line = matr[line_index]
            for this_line in matr[(line_index + 1)::]:
                if (this_line[line_index] != 0):
                    a = this_line[line_index]
                    for i in range(line_index, n):
                        this_line[i] -= float((first_line[i] / first_line[line_index]) * a)

            line_index += 1

        elif (line_index < n):
            swap_lines(matr, line_index, line_index + 1)
        else:
            break

    return matr





if __name__ == "__main__":
    attempt = 0
    while attempt < 10:
        is_int = input("Выбирете тип матрицы:\n1. Int\n2. float\n")
        if is_int == '1':
            is_int = True
            break
        elif is_int == '2':
            is_int = False
            break
        else:
            print("Error: wrong argument.")
            attempt += 1

    if attempt != 0:
        exit(1)

    m = read_matrix(is_int)
    solve_gauss(m)
    print("\nResult matrix:")
    print_matrix(m)
    