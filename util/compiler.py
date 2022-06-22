import os 
import sys

file = sys.argv[1]

os.system(f'g++ {file}.cpp -Wall -o {file}.exe')