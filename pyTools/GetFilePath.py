#! /user/bin/python
# -*- encoding: utf-8 -*-

import os
import os.path

rootdir = "e:\samples\positives";                   #被遍历的文件夹根目录

file_writepath = "e:\samples\AllFile_Path.txt";     #遍历后保存的结果文件路径
#file_writepath = rootdir + "\AllFile_Path.txt"     #遍历后保存的结果文件路径
fout = open(file_writepath, 'w')

for dirpath, dirnames, filenames in os.walk(rootdir):
    for dirname in dirnames:
        print "dirpath is: " + dirpath
        print "dirname is: " + dirname
        print  "\n"

    for filename in filenames:
        print "dirpath is: " + dirpath
        print "filename is: " + filename
        print "full path of the file is : " + os.path.join(dirpath, filename)
        fout.write(os.path.join(dirpath, filename) + "\n")

fout.close()
