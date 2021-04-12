#!/usr/bin/env python
import contextlib as __stickytape_contextlib

@__stickytape_contextlib.contextmanager
def __stickytape_temporary_dir():
    import tempfile
    import shutil
    dir_path = tempfile.mkdtemp()
    try:
        yield dir_path
    finally:
        shutil.rmtree(dir_path)

with __stickytape_temporary_dir() as __stickytape_working_dir:
    def __stickytape_write_module(path, contents):
        import os, os.path

        def make_package(path):
            parts = path.split("/")
            partial_path = __stickytape_working_dir
            for part in parts:
                partial_path = os.path.join(partial_path, part)
                if not os.path.exists(partial_path):
                    os.mkdir(partial_path)
                    with open(os.path.join(partial_path, "__init__.py"), "wb") as f:
                        f.write(b"\n")

        make_package(os.path.dirname(path))

        full_path = os.path.join(__stickytape_working_dir, path)
        with open(full_path, "wb") as module_file:
            module_file.write(contents)

    import sys as __stickytape_sys
    __stickytape_sys.path.insert(0, __stickytape_working_dir)

    __stickytape_write_module('libpy/fenwick.py', b'class Fenwick:\n  def __init__(z,n):\n    z.n=n\n    z.t=[0 for i in range(n+1)]\n  def pfs(z,i):\n    i+=1\n    a=0\n    while i>0:\n      a+=z.t[i]\n      i-=i&-i\n    return a\n  def q(z,s,e):\n    if s>=e:\n      return 0\n    return z.pfs(e-1)-z.pfs(s-1)\n  def upd(z,i,d):\n    i+=1\n    while i<=z.n:\n      z.t[i]+=d\n      i+=i&-i')
    #import numpy as np
    import sys
    sys.setrecursionlimit(int(1e6))
    import math
    import libpy.fenwick as fw;
    
    z=fw.Fenwick(10)
    z.upd(1,3)
    z.upd(4,2)
    print(z.q(1,8))
    print(z.q(2,7))
    print(z.q(0,4))