import os
import sys

exe = sys.argv[1]
output = ''
if 2 < len(sys.argv):
    input_file = sys.argv[2]
    output += f' < {input_file}'

if 3 < len(sys.argv):
    output_file = sys.argv[3]
    output += f' > {output_file}'

cmd = f'./{exe}{output}'
print(cmd)
os.system(cmd)
