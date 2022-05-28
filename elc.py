import argparse

from compiler import Compiler, Lexer


compiler = Compiler(Lexer())


if __name__ == '__main__':
    print('E Language Compiler - version 0.0p\n')

    parser = argparse.ArgumentParser(description='E Language Compiler')
    parser.add_argument('input', metavar='input', type=str, nargs='?', help='.e input file')
    args = parser.parse_args()

    compiler.compile(args.input)
