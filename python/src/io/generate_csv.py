import os
import random

def sample(x):
    mid = random.gauss(50, 5)
    low = mid - random.uniform(0.01, 0.50)
    high = mid + random.uniform(0.01, 0.50)
    return f"{low},{mid},{high},{x}\n"

n = 10_000_000
file_path = os.path.expanduser("~/dev/puzzles/cpp/res/large_csv_lomidhict.csv")
lines = [sample(x) for x in range(n)]

with open(file_path, "w") as f:
    f.writelines(lines)
