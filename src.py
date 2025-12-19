matrices = {}
name = None
data = [] 

with open('Book1.csv', 'r', encoding='utf-8-sig') as f:
    lines = f.readlines()

for line in lines:
    line = line.strip()
    if not line: continue
        
    if "matran" in line:
        if name and data:
            matrices[name] = [[float(x) for x in row.split(',')] for row in data]
        name = line
        data = []
    else:
        data.append(line)

if name and data:
        matrices[name] = [[float(x) for x in row.split(',')] for row in data]


def getshape(matrix):
    return (len(matrix), len(matrix[0]))

def add(A, B):
    r, c = getshape(A)
    result = [[0 for _ in range(c)] for _ in range(r)]
    
    for i in range(r):
        for j in range(c):
            result[i][j] = A[i][j] + B[i][j]
    return result

def multiplication(A, B):
    r1, c1 = getshape(A)
    r2, c2 = getshape(B)
    result = [[0 for _ in range(c2)] for _ in range(r1)]
    
    for i in range(r1):
        for j in range(c2):
            for k in range(c1):
                result[i][j] += A[i][k] * B[k][j]
    return result

def print_matrix(title, matrix):
    print(f"\n{title}:")
    for row in matrix:
        print(*row)

A = matrices.get('matran1')
B = matrices.get('matran2')

print_matrix("Ma tran A:\n", A)
print_matrix("Ma tran B:\n", B)

if A and B:
    shapeA = getshape(A)
    shapeB = getshape(B)

    if shapeA == shapeB:
        print_matrix("Tong A + B:\n", add(A, B))

    else:
        print("khac kich thuoc.")

    if shapeA[1] == shapeB[0]:
        print_matrix("Tich A * B:\n", multiplication(A, B))
    else:
        print("Khong the nhan.")

               



