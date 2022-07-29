import os
import sys

exe = sys.argv[1]
output = ''


def getOutput(numeric_inputs=0, file_in_range=1):
    if 3 < len(sys.argv):
        if numeric_inputs:
            return f' > test/{file_in_range}.out'
        output_file = sys.argv[3]
        return f' > {output_file}'

    return ''


def getInput(is_numeric=0, input_file=1):
    if is_numeric:
        return f' < test/{input_file}.in'
    if 2 < len(sys.argv):
        input_file = sys.argv[2]
        if '--numeric_inputs=' in input_file:
            return input_file.split('=')[1]
        else:
            return f' < {input_file}'
    return ''

def read(file):
    with open(file, 'r') as f:
        text = f.read()
        return text

def write(file, text):
    with open(file, 'w') as f:
        f.write(text)

def exec_cmd():
    input_file = getInput()
    all_tests = ''
    if input_file.isnumeric():
        for i in range(int(input_file)):
            output_file = getOutput(1,i+1)
            cmd = f'./{exe}{getInput(1,i+1)}{output_file}'
            print(cmd)
            test = read(output_file.replace(' > ',''))
            all_tests += f'Teste {i+1}\n'
            all_tests += f'{test}\n'
            os.system(cmd)
    else:
        output_file = getOutput()
        cmd = f'./{exe}{input_file}{output_file}'
        test = read(output_file.replace(' > ',''))
        all_tests += test
        print(cmd)
        os.system(cmd)

    write('test/all.out',all_tests)


exec_cmd()
