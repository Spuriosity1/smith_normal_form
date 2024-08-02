import random
import sys
import numpy as np
import os

script_folder = os.path.dirname(os.path.realpath(__file__))

if len(sys.argv) < 3:
    print(f"USAGE: {sys.argv[0]} DIMENSION NUM_RAND [cwd_to_script_folder=no [Y/n]]")
    sys.exit(1)

cwd_to_script_folder = False
if len(sys.argv) >= 4 and sys.argv[3].lower().startswith('y'):
    cwd_to_script_folder = True


n = int(sys.argv[1])
num_rand = int(sys.argv[2])

M = np.eye(n, dtype=np.int_)


def row_add(n, i, j, val):
    A = np.eye(n, dtype=np.int_)
    if (i != j):
        A[i, j] = val
    else:
        A[i, j] *= -1
    return A


def row_swap(n, i, j):
    A = np.eye(n, dtype=np.int_)
    A[i, i] = 0
    A[j, j] = 0
    A[i, j] = 1
    A[j, i] = 1
    return A


for _ in range(num_rand):
    # choose random i != j
    idx = [i for i in range(n)]
    i = random.choice(idx)
    idx.pop(i)
    j = random.choice(idx)

    if random.random() < 0.8:
        val = random.randint(-7, 7)
        M = row_add(n, i, j, val) @ M
    else:
        M = row_swap(n, i, j) @ M


filename = f"invertible_{n}x{n}_{num_rand}.mat"
if cwd_to_script_folder:
    filename = os.path.join(script_folder, filename)

with open(filename, 'w') as f:
    for row in range(n):
        for col in range(n):
            f.write(str(M[row][col]) + " ")
        f.write("\n")
