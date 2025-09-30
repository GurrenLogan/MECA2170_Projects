import ctypes
import os
import scripts.genpts as gen
from HalfEdge import *

#Exemple of how to use C librara
# # Load the shared library
# lib = ctypes.CDLL(os.path.abspath("libmycode.so")) # "mycode.dll" on Windows
# # Tell ctypes the function signature
# lib.double_value.argtypes = [ctypes.c_int]
# lib.double_value.restype = ctypes.c_int
# # Call the C function
# x = 7
# result = lib.double_value(x)
# print(f"C function returned: {result}")