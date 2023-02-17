# -*- coding: utf-8 -*-
"""
Created on Fri Feb 17 05:02:45 2023

@author: Mahmut Osmanovic
"""

import ctypes

# type in command in workspaceFolder (gets shared library)
# gcc -fPIC -shared -o lib.so testPy.c
# gcc -shared -o lib.dll testPy.c
lib = ctypes.CDLL("./lib.dll")

lib.display()