#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import os.path

path = os.getcwd() + '/../'
for root, dirs, files in os.walk(path):
    for name in files:
        if (name.endswith(".h") or name.endswith(".c")):
            localpath = root + '/' + name
            print localpath
            os.system(path + "/bin/clang-format -i %s -style=File -sort-includes=false" %(localpath))

print ''
raw_input("Press any key to continue...")
