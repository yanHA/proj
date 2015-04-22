#! /user/bin/python
# -*- encoding: utf-8 -*-

#mysql
import time, MySQLdb, sys

#connect
conn = MySQLdb.connect(host="localhost", user="root", passwd="password", db="icvmp_smartpark", charset="utf8")
cursor = conn.cursor()

#查询
n = cursor.execute("select * from sp_parkingstatus")
for row in cursor.fetchall():
    for r in row:
        print r

cursor.close
conn.close
