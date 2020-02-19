
def is_palindrome(string_var):     
    '''
    returns True if string_var is palindrome, False otherwise
    '''
    ret = None
    ########################
    string_var_list = list(string_var)
    
    for i in range(int(len(string_var_list)/2+1)):
        if string_var_list[i] != string_var_list[-i-1]:
            return False
    ret = True
    ########################
    return ret 

def histogram_letters(string_var):     
    '''
    count how many times a letter is present in the string_var
    and returns a dict

    '''
    ret = None
    ########################
    string_var_list = list(string_var)
    histogram = {}
    for letter in string_var_list:
        if letter not in histogram.keys():
            histogram[letter] = 1
        else:
            histogram[letter] += 1
    ret = histogram
    ########################
    return ret 

def get_most_frequent(list_var):
    '''
    returns a tuple with the most frequent object in the list with the 
    corresponing number
    '''
    ret = None
    ########################
    histogram = {}
    for element in list_var:
        if element not in histogram.keys():
            histogram[element] = 1
        else:
            histogram[element] += 1
    
    for element in histogram.items():
        if(element[1] == max(histogram.values())):
            ret = element
    ########################
    return ret

def which_duplicates(list_var):
    '''
    return a dict with containing the repeted object and the number of repetitions
    '''
    ret = None
    ########################
    histogram = {}
    for element in list_var:
        if element not in histogram.keys():
            histogram[element] = 1
        else:
            histogram[element] += 1
    
    k=len(histogram)
    items = list(histogram.keys())
    for i in range(0,k):
        element = items[i]
        if(histogram[element] == 1):
           del histogram[items[i]]
    
    ret = histogram
    ########################
    return ret


def compute_factorial(int_val):
    '''
    returns factorial of a number
    '''
    ret = None
    ########################
    ret = 1
    if int_val < 1:
        ret = 1
    else:
        for i in range(1,int_val+1):
            ret*=i
    ########################
    return ret


def is_prime(int_val):
    '''
    returns True if int_val is prime, False otherwise
    '''
    ret = None
    ########################
    ret = True
    if int_val == 2:
        return ret
    if int_val%2 == 0:
        return False
    for i in range(3,int(int_val/2),2):
        if int_val%i == 0:
            return False
    ########################
    return ret

        

