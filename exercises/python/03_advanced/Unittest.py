
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
        
#TESTS
        
list(range(1))  #OK
list(myrange(1))

list(range(2))  #OK
list(myrange(2))

list(range(2.2))    #error
list(myrange(2.2))  #no error (should show error)

list(range(-2)) #OK
list(myrange(-2))

list(range(2,10))   #OK
list(myrange(2,10))

list(range("Tornatore")) #OK
list(myrange("Cozzini"))

list(range(2,10))   #ok
list(myrange(2,10))

list(range(2,-10))  #ok
list(myrange(2,-10))

list(range(2,2))   #ok
list(myrange(2,2))

list(range(2,10,1)) #ok
list(myrange(2,10,1))

list(range(2,10,11))    #ok
list(myrange(2,10,11))

list(range(2,-10,-1))   #ok
list(myrange(2,-10,-1))

list(range(0,-10,1))    #ok
list(myrange(0,-10,1))

list(range(0.5,1.5,0.5))    #error
list(myrange(0.5,1.5,0.5))  #myrange is better
        
        
        
        
