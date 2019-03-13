#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from pathlib import Path
import subprocess
from subprocess import DEVNULL
import sys

import colorama
from colorama import Fore, Style

def get_cases():
    return tuple(filter(Path.is_dir, Path('test/').iterdir()))

def build_case(case):
    cmdline = (
        "g++",
        "-std=c++14",
        "-Wall", "-Wextra",
        "-O2",
        "-I../../include/",
        "solve.cpp",
    )
    proc = subprocess.run(cmdline, cwd=case)
    return proc.returncode == 0

def run_case(case):
    cmdline = (
        "./t"
    )
    proc = subprocess.run(cmdline, cwd=case, stderr=DEVNULL)
    return proc.returncode == 0

def exec_case(case):
    if not build_case(case): return False
    if not run_case(case): return False
    return True

def main():
    colorama.init()

    cases = get_cases()

    n_ok = 0
    for case in cases:
        if exec_case(case):
            print(f"[{Fore.GREEN}OK{Style.RESET_ALL}] ", end="")
            n_ok += 1
        else:
            print(f"[{Fore.RED}NG{Style.RESET_ALL}] ", end="")
        print(case)

    print()
    print(f"test passed: {n_ok}/{len(cases)}")

    all_ok = n_ok == len(cases)
    sys.exit(0 if all_ok else 1)

if __name__ == "__main__": main()
