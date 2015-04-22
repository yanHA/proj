#! user/bin/python
# -*- encoding:utf-8 -*-

import time, threading

#假定这是你的银行存款
balance = 0
lock = threading.Lock()

def change_it(n):
    #先存后取
    global balance
    balance = balance + n
    balance = balance - n

def run_thread(n):
    for i in range(100000):
        #先获取锁
        lock.acquire()
        try:
            #修改
            change_it(n)
        finally:
            #释放锁
            lock.release()

if __name__ == '__main__':
    t1 = threading.Thread(target=run_thread, args=(5,))
    t2 = threading.Thread(target=run_thread, args=(8,))
    t1.start()
    t2.start()
    t1.join()
    t2.join()
    print balance