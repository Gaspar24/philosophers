import os
import subprocess
import time
import shlex

def usleep(mlsec):
    sec = mlsec / 1000000.0
    time.sleep(sec)

BLUE = '\033[94m'
GREEN = '\033[92m'
RED = '\033[91m'
RESET = '\033[0m'

def wait_for_input():
    print(f"\n{BLUE}Press {RED}[Enter]{BLUE} to continue...{RESET}")
    input()

def wait_for_input_Y_or_N():
    answer = input(f"{BLUE}Type {RED}[Y]{BLUE} if philosopher dies type {RED}[N]{BLUE} if not: {RESET}")
    while answer != 'y' and answer != 'n':
        answer = input(f"{RED}Type {RED}[Y]{BLUE} if philosopher dies type {RED}[N]{BLUE} if not: {RESET}")
    return answer

def check_norm():
    answer = True
    usleep(100000)
    print(f"\n{BLUE}[ === Norm check === ]{RESET}")
    r = subprocess.run('ls', shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    arr = r.stdout.strip().split("\n")
    for i, file_name in enumerate(arr, start=1):
        r1 = subprocess.run(f'norminette {file_name}', shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        if r1.returncode == 0:
            print(f"{GREEN}{i}.[OK] [NORMINETTE]{RESET}")
        else:
            print(f"{RED}{i}.[KO] [NORMINETTE]{RESET}")
            print(f'{RED}norminette {file_name}{RESET}')
            answer = False
    return answer

def check_if_dies():
    answer = True
    usleep(100000)
    print(f"\n{BLUE}[ === Test if a philosopher dies === ]{RESET}")
    cmd = ['./philo 4 310 200 100', './philo 1 800 200 200', './philo 4 400 200 200', './philo 5 400 200 200', './philo 4 310 160 150']
    for c in cmd:
        usleep(50000)
        print(f"\n{BLUE}{c} {RED}[ONLY ONE PHILO SHOULD DIE]{RESET}")
        wait_for_input()
        os.system(c)
        if wait_for_input_Y_or_N() == 'n':
            print(f"{RED}[KO] [PHILOSOPHER SHOULD DIE]{RESET}")
            answer = False
        else:
            print(f"{GREEN}[OK] [PHILOSOPHER DIED]{RESET}")
    return answer

def check_if_not_dies():
    answer = True
    usleep(100000)
    print(f"\n{BLUE}[ === Test if a philosopher does not die === ]{RESET}")
    cmd = ['./philo 5 800 200 200 10' , './philo 3 800 200 200 10', './philo 4 310 150 150 10', './philo 200 400 60 60 10', './philo 73 400 60 60 10']
    for c in cmd:
        usleep(50000)
        print(f"\n{BLUE}{c} {RED}[NO PHILOSOPHER SHOULD DIE]{RESET}")
        wait_for_input()
        os.system(c)
        if wait_for_input_Y_or_N() == 'y':
            print(f"{RED}[KO] [PHILOSOPHER SHOULD NOT DIE]{RESET}")
            answer = False
        else:
            print(f"{GREEN}[OK] [PHILOSOPHER DID NOT DIE]{RESET}")
    return answer

def check_leaks_on_wrong_arguments():
    answer = True
    i = 1
    usleep(100000)
    print(f"\n{BLUE}[ === Test wrong arguments with valgrind === ]{RESET}")
    valgrind_ok = "ERROR SUMMARY: 0 errors from 0 contexts"

    cmd = ['./philo ', './philo "a" 310 100 100', './philo 4 "a" 100 100', './philo 4 310 "a" 100', './philo 4 310 100 "a"', './philo 4 310 100 100 "a"',
           './philo " " 310 100 100', './philo 4 " " 100 100', './philo 4 310 " " 100', './philo 4 310 100 " "', './philo 4 310 100 100 " "',
           './philo -1 310 100 100', './philo 4 -1 100 100', './philo 4 310 -1 100', './philo 4 310 100 -1', './philo 4 310 100 100 -1',
           './philo 0 310 100 100', './philo 4 0 100 100', './philo 4 310 0 100', './philo 4 310 100 0', './philo 4 310 100 100 0',
           './philo "" 310 100 100', './philo 4 "" 100 100', './philo 4 310 "" 100', './philo 4 310 100 ""', './philo 4 310 100 100 ""',
           './philo 4 310 100 100 100 100', './philo 4 310 100', './philo 4 310', './philo 4', './philo 4 310 100 100 100 100 100',
           './philo 201 310 100 100' ]
    valgrind = 'valgrind --leak-check=full'
    for c in cmd:
        test = subprocess.Popen(f"{valgrind} {c}", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        exit_code = subprocess.run(c, shell=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL).returncode
        if valgrind_ok not in test.stderr.read().decode():
            print(f"{RED}{i}. [KO LEAKS]{RESET}")
            print(f"{RED}Command: {c}{RESET}")
            answer = False
        else:
            print(f"{GREEN}{i}.[OK] [VALGRIND] [MOK]{RESET}")
        i += 1
        if exit_code != 1:
            print(f"{RED}{i}. [KO]{RESET} {BLUE}EXIT [1] {RED}RETURN [{exit_code}]{RESET}")
            print(f"{RED}Command: {c}{RESET}")
            answer = False
        else:
            print(f"{GREEN}{i}.[OK]{RESET} {BLUE}EXIT [1] {GREEN}RETURN [{exit_code}]{RESET}")
        i += 1
    return answer

def check_helgraind_when_dies():
    answer = True
    i = 1
    usleep(100000)
    print(f"\n{BLUE}[ === Test if helgrind detects deadlocks === ]{RESET}")
    cmd = ['./philo 4 310 200 100 10', './philo 1 800 200 200 10', './philo 4 400 200 200 10', './philo 5 400 200 200 10', './philo 4 310 160 150 10',
            './philo 5 800 200 200 2' , './philo 3 800 200 200 2', './philo 2 800 200 200 2', './philo 1 800 200 200 2' , './philo 7 800 200 200 2']
    helgraind_ok = "ERROR SUMMARY: 0 errors from 0 contexts"
    helgraind = 'valgrind --tool=helgrind'
    for c in cmd:
        test = subprocess.Popen(f"{helgraind} {c}", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        philo_and_time = "[" + c.split()[1] + "]" + " " + "[" +  c.split()[2] + "]" + " " + "[" + c.split()[3] + "]" + " " + "[" + c.split()[4] + "]" + " " + "[" + c.split()[5] + "]"
        if helgraind_ok not in test.stderr.read().decode():
            print(f"{RED}{i}. [KO DEADLOCK] {BLUE} {philo_and_time}{RESET}")
            print(f"{RED}Command: {c}{RESET}")
            answer = False
        else:
            print(f"{GREEN}{i}.[OK] [HELGRIND OK] {BLUE} {philo_and_time}{RESET}")
        i += 1
    return answer

def chec_helgrind_when_10_times_eat():
    answer = True
    i = 1
    usleep(100000)
    print(f"\n{BLUE}[ === Test if helgrind detects data races === ]{RESET}")
    print(f"{RED}!!! IT MAY TAKE A LONG TIME BECAUSE THE TESTS ARE VERY HEAVY !!!{RESET}")
    cmd = ['./philo 4 310 150 150 10', './philo 1 800 200 200 10', './philo 4 400 200 200 10', './philo 5 400 200 200 10', './philo 4 310 150 150 10',
            './philo 200 800 60 60 10' , './philo 50 800 100 100 10', './philo 25 800 200 200 10' , './philo 10 800 200 200 10',
            './philo 7 800 200 200 10', './philo 3 800 200 200 10', './philo 200 200 60 60 10', './philo 50 200 60 60 10',
            './philo 7 800 60 60 25', './philo 3 800 60 60 25', './philo 4 200 60 60 25', './philo 25 200 60 60 25',]
    helgraind_ok = "ERROR SUMMARY: 0 errors from 0 contexts"
    helgraind = 'valgrind --tool=helgrind'
    for c in cmd:
        test = subprocess.Popen(f"{helgraind} {c}", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        philo_and_time = "[" + c.split()[1] + "]" + " " + "[" +  c.split()[2] + "]" + " " + "[" + c.split()[3] + "]" + " " + "[" + c.split()[4] + "]" + " " + "[" + c.split()[5] + "]"
        if helgraind_ok not in test.stderr.read().decode():
            print(f"{RED}{i}. [KO DATA RACE] {BLUE} {philo_and_time}{RESET}")
            print(f"{RED}Command: {c}{RESET}")
            answer = False
        else:
            print(f"{GREEN}{i}.[OK] [HELGRIND OK] {BLUE} {philo_and_time}{RESET}")
        i += 1
    return answer

def compile_with_fsanitize():
    with open("Makefile", "r") as f:
            fsanitize = "fsanitize=address"
            strings = f.read()
            if fsanitize in strings:
                return
    with open("Makefile", "r") as f:
        cc = "cc"
        gcc = "gcc"
        strings = f.read()
        if cc in strings or gcc in strings:
            if(cc in strings):
                lines = strings.replace(cc, f"{cc} -fsanitize=address")
            else:
                lines = strings.replace(gcc, f"{gcc} -fsanitize=address")
        with open("Makefile", "w") as f:
            f.writelines(lines)
    os.system("make re")
    os.system("make clean")

def check_fsanitize_address():
    answer = True
    i = 1
    usleep(100000)
    print(f"\n{RED}[FSANITIZE=ADDRESS]{RESET}")
    cmd_when_not_dies = [ './philo 5 800 200 200 2' , './philo 3 800 200 200 2', './philo 2 800 200 200 2', './philo 8 800 200 200 2' , './philo 7 800 200 200 2',
            './philo 4 800 200 200 4', './philo 5 800 200 200 4', './philo 3 800 200 200 4', './philo 2 800 200 200 4', './philo 8 800 200 200 4']
    cmd_when_dies = ['./philo 4 310 200 100', './philo 1 800 200 200', './philo 4 400 200 200', './philo 5 400 200 200', './philo 4 310 160 150']
    
    cmd_when_error = ['./philo ', './philo "a" 310 100 100', './philo 4 "a" 100 100', './philo 4 310 "a" 100', './philo 4 310 100 "a"', './philo 4 310 100 100 "a"',
           './philo " " 310 100 100', './philo 4 " " 100 100', './philo 4 310 " " 100', './philo 4 310 100 " "', './philo 4 310 100 100 " "',
           './philo -1 310 100 100', './philo 4 -1 100 100', './philo 4 310 -1 100', './philo 4 310 100 -1', './philo 4 310 100 100 -1',
           './philo 0 310 100 100', './philo 4 0 100 100', './philo 4 310 0 100', './philo 4 310 100 0', './philo 4 310 100 100 0',
           './philo "" 310 100 100', './philo 4 "" 100 100', './philo 4 310 "" 100', './philo 4 310 100 ""', './philo 4 310 100 100 ""',
           './philo 4 310 100 100 100 100', './philo 4 310 100', './philo 4 310', './philo 4', './philo 4 310 100 100 100 100 100',
           './philo 201 310 100 100' ]
    compile_with_fsanitize()
    usleep(100000)
    print(f"{BLUE}[ === Test when wrong arguments === ]{RESET}")
    for c in cmd_when_error:
        test = subprocess.Popen(c, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        argss = ' '.join(['[' + s + ']' for s in shlex.split(c)[1:]])
        usleep(50000)
        if "AddressSanitizer: heap-buffer-overflow" in test.stderr.read().decode():
            print(f"{RED}{i}. [KO MEMORY PROBLEM] {BLUE} {argss}{RESET}")
            print(f"{RED}Command: {c}{RESET}")
            answer = False
        else:
            print(f"{GREEN}{i}.[OK] [MEMORY OK] {BLUE} {argss}{RESET}")
        i += 1
    usleep(100000)
    print(f"\n{BLUE}[ === Test when philosopher dies === ]{RESET}")
    for c in cmd_when_dies:
        test = subprocess.Popen(c, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        argss = ' '.join(['[' + s + ']' for s in shlex.split(c)[1:]])
        if "AddressSanitizer: heap-buffer-overflow" in test.stderr.read().decode():
            print(f"{RED}{i}. [KO MEMORY PROBLEM] {BLUE} {argss}{RESET}")
            print(f"{RED}Command: {c}{RESET}")
            answer = False
        else:
            print(f"{GREEN}{i}.[OK] [MEMORY OK] {BLUE} {argss}{RESET}")
        i += 1
    usleep(100000)
    print(f"\n{BLUE}[ === Test when philosopher does not die === ]{RESET}")
    print(f"{RED}!!! IT MAY TAKE A LONG TIME BECAUSE THE TESTS ARE VERY HEAVY !!!{RESET}")
    for c in cmd_when_not_dies:
        test = subprocess.Popen(c, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        argss = ' '.join(['[' + s + ']' for s in shlex.split(c)[1:]])
        if "AddressSanitizer: heap-buffer-overflow" in test.stderr.read().decode():
            print(f"{RED}{i}. [KO MEMORY PROBLEM] {BLUE} {argss}{RESET}")
            print(f"{RED}Command: {c}{RESET}")
            answer = False
        else:
            print(f"{GREEN}{i}.[OK] [MEMORY OK] {BLUE} {argss}{RESET}")
        i += 1
    return answer

if __name__ == "__main__":
    test = False
    failed_tests = []
    if not check_if_not_dies():
        test = True
        failed_tests.append("check_if_not_dies")
    if not check_if_dies():
        test = True
        failed_tests.append("check_if_dies")
    if not check_norm():
        test = True
        failed_tests.append("check_norm")
    if not check_leaks_on_wrong_arguments():
        test = True
        failed_tests.append("check_leaks_on_wrong_arguments")
    if not check_helgraind_when_dies():
        test = True
        failed_tests.append("check_helgraind_when_dies")
    if not chec_helgrind_when_10_times_eat():
        test = True
        failed_tests.append("chec_helgrind_when_10_times_eat")
    if not check_fsanitize_address():
        test = True
        failed_tests.append("check_fsanitize_address")
    if test:
        print(f"\n{RED}[SOME TESTS FAILED]{RESET}")
        for i in failed_tests:
            print(f"{RED}[{i}.]{RESET}")
    else:
        print(f"\n{GREEN}[ALL TESTS PASSED]{RESET}")
