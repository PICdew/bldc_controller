#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import os.path

# All the file path include following keywords will be not be formated
exceptionList = ['lib/DEE_Emulation_16-bit', 'lib/freemodbus/modbus', 'source/qpc', 'main.c']

path = os.getcwd() + '/../'
for root, dirs, files in os.walk(path):
    for name in files:
        needFormat = True
        localpath = root + '/' + name
        localpath = localpath.replace("scripts/../", "").replace("\\", "/")

        for exceptElement in exceptionList:
            if (-1 != localpath.find(exceptElement)):
                # print '[Except]' + localpath
                needFormat = False
                break

        if ((name.endswith(".h") or name.endswith(".c")) and needFormat):
            print '[Process]' + localpath
            os.system(
                path + "/bin/clang-format -i %s -style=File -sort-includes=false" % (localpath))

raw_input("Press any key to continue...")
