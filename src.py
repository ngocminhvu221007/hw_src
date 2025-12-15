import numpy as np

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
            matrices[name] = np.loadtxt(data, delimiter=',')
        
        name = line
        data = [] 
    else:
        data.append(line)

if name and data:
    matrices[name] = np.loadtxt(data, delimiter=',')

A = matrices.get('matran1')
B = matrices.get('matran2')

print("Ma tran A:\n", A)
print("Ma tran B:\n", B)

if A.shape == B.shape:
    print("Tong A + B:\n", A + B)
else:
    print("Khong the cong.")
    
if A.shape == B.shape:
    print("Hieu A - B:\n", A - B)
else:
    print("Khong the tru")
if A.shape[1] == B.shape[0]:
    print("Tich A * B:\n", A @ B)
else:
    print("Khong the nhan.")
if B.shape[0] == B.shape[1]:
    try: 
        det_B = np.linalg.det(B)
        if det_B != 0:
           B_inv = np.linalg.inv(B)
           if A.shape[1] == B.shape[0]:
            print("Thuong A/B: \n", A * B_inv)
           else:
               print("Khong the chia.")
        else:
            print("Khong the chia. DetB=0.")
    except np.linalg.LinAlgError:
        print("Lỗi.")
else:
    print("Khong the chia (B khong phai ma tran vuong).")
               


