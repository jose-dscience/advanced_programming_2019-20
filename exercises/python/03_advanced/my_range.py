#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#def myrange(start=0,end=None,step=1):
def myrange(*argv):    
    def argvalidation(numargs, start, end, step):
        if(numargs < 1 or len(args) > 3): raise SyntaxError("The number of arguments must be compressed between 1 and 3.")
        try:
            float(start)
            float(end)
            float(step)
        except:
            raise TypeError("function arguments must be \"int\" of \"float\".")
    
    import math
    args = list(argv)
    numargs = len(args)
    
    if numargs == 1:
        end = args[0]
        start=0
        step=1
    elif numargs == 2:
        start = args[0]
        end = args[1]
        step=1
    elif numargs == 3:
        start = args[0]
        end = args[1]
        step = args[2]
    else:
        start = end = step = 0
    
    argvalidation(numargs, start, end, step)            
    
    i = start
    while i*math.copysign(1,step) < end*math.copysign(1,step):
        yield i
        i += step


    

