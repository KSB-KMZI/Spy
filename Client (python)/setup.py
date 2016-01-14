from distutils.core import setup
import py2exe

setup(options = {"py2exe":{"compressed": 0,
                           "optimize": 2,
                           "ascii": 1,
                           "bundle_files": 3,
                           "includes":['ftplib.*']}},windows=["client_cnc.py"])