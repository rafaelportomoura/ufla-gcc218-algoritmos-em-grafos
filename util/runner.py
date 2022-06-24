import os
import sys

exe = sys.argv[1]
input_file = sys.argv[2]

output_file = sys.argv[3]

os.system(f'./{exe} < {input_file} > {output_file}')