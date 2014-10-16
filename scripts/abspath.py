import os
import sys

def main(arg):
    sys.stdout.write(os.path.abspath(arg))

if __name__ == '__main__':
    main(sys.argv[1])

