import os
import sys

def main(arg):
    return os.path.abspath(arg)

if __name__ == '__main__':
    sys.stdout.write(main(sys.argv[1]))

