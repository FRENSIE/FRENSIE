import os
import shutil

def main():
    cwd = os.getcwd()
    if not cwd.endswith(os.path.join('FRENSIE', 'scripts')):
        print 'This script must be run in \"FRENSIE/scipts\"'
        print 'Your CWD is', cwd
        return 1

    os.chdir('../../')
    os.mkdir('frensie_build_tree')
    #os.renames('FRENSIE', 'frensie_build_tree/FRENSIE')
    os.symlink(os.path.abspath('FRENSIE'), 'frensie_build_tree/FRENSIE')
    os.chdir('frensie_build_tree')
    os.symlink('FRENSIE', 'src')
    os.mkdir('deps')
    os.mkdir('deps/install')
    os.mkdir('deps/tars')
    os.mkdir('build')
    shutil.copyfile('src/scripts/makefile.deps', 'deps/makefile')
    shutil.copyfile('src/scripts/lazy.sh', 'deps/lazy.sh')
    shutil.copyfile('src/scripts/frensie.sh', 'build/frensie.sh')
    #shutil.copyfile('src/scripts/source_deps.sh', 'build/source_deps.sh')

    print """
To build dependencies move necessary tars to deps/tars.
cd to frensie_build_tree/deps and run make all.

To once all dependencies exist in frensie_build_tree/deps/install
cd to frensie_build_tree/build and run bash frensie.sh
"""


if __name__ == '__main__':
    main()
