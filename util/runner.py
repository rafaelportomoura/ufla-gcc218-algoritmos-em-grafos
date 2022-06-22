import os
import sys

exe = sys.argv[1]
input_file = sys.argv[2]

os.system(f'./{exe} < {input_file}')