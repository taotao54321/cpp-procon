#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from pathlib import Path

def get_dir():
    return Path(__file__).resolve().parent

def create_cpp(base):
    hdr  = open(base/"include"/"procon.hpp", "r").read()
    body = open(base/"tmpl"/"solve.cpp", "r").read()
    with open("solve.cpp", "x") as out:
        out.write(hdr)
        out.write(body)

def create_makefile(base):
    body = open(base/"tmpl"/"Makefile", "r").read()
    with open("Makefile", "x") as out:
        out.write(body)

def main():
    base = get_dir()

    create_cpp(base)
    create_makefile(base)

if __name__ == "__main__": main()
