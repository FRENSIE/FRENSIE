import os
import subprocess as sp
import sys
def getExisting(var):
    try:
        return  os.environ[var]
    except:
        return ''

def dedup(lin):
    l = [i for i in lin]
    for x in list(set(l)):
        i = l.index(x)+1
        while True:
            try:
                index = l[i:].index(x)
            except ValueError:
                break
            l.pop(i+index)

    return l

def gen_cmd(prefix):
    prefix = os.path.abspath(prefix)
    dirs = sorted([i for i in os.listdir(prefix) if not i.startswith('.') and os.path.isdir(os.path.join(prefix, i))])

    det = dict()
    det['PATH'] = ['bin']
    det['LIBRARY_PATH'] = ['lib', 'lib64']
    det['LD_LIBRARY_PATH'] = det['LIBRARY_PATH']
    det['C_INCLUDE_PATH'] = ['include']
    det['CPLUS_INCLUDE_PATH'] = det['C_INCLUDE_PATH']

    cmds = dict()

    for install in dirs:
        root = os.path.join(prefix, install)
        for var, l in det.items():
            for i in l:
                path = os.path.join(prefix, install, i)
                cmds[var] = cmds.get(var, '') + path + ':'

    for var, l in cmds.items():
        cmds[var] = cmds.get(var, '') + getExisting(var)
        l = cmds[var].strip(':').split(':')
        l = dedup(l)
        cmd = ''.join(map(lambda x: x+':', l)).strip(':')
        cmds[var] = cmd


    cmd = ''
    for var, l in cmds.items():
        cmd += var + '=' + l + ' '

    return 'export ' + cmd

def main():
    try:
        cmd = gen_cmd(sys.argv[1])
    except:
        return

    print cmd




if __name__ == '__main__':
    main()
