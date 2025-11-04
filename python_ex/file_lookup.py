import os
import argparse
import re

parser = argparse.ArgumentParser()
parser.add_argument("-f", "--file", help="file that you want to search")
parser.add_argument("-s", "--startdir", help="directory that you want to search for file in")
args = parser.parse_args()
file = args.file
startdir = args.startdir

if '*' in file:
    x = re.search(r"^\*(.*)[^\*]$",file)
    if x:
        for dirpath, dirnames, filenames in os.walk(startdir,topdown=True):
            for filename in filenames:
                if filename.startswith(x.group(1)):
                    print (filename)
    else:
        x = re.search(r"^([^\*].*)\*$",file)
        if x:
            for dirpath, dirnames, filenames in os.walk(startdir,topdown=True):
                for filename in filenames:
                    if filename.endswith(x.group(1)):
                        print (filename)
        else:
            x = re.search(r"^\*(.*)\*$",file)
            if x:
                for dirpath, dirnames, filenames in os.walk(startdir,topdown=True):
                    for filename in filenames:
                        if x.group(1) in filename:
                            print (filename)
else:
    for dirpath, dirnames, filenames in os.walk(startdir,topdown=True):
                for filename in filenames:
                    if filename == file:
                        print (filename)
