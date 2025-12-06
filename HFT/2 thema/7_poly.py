
def f(s) : 
    if ( len(s) == 1 or len(s) == 2) : 
        return True ; 
    if ( s[0] != s[-1]): 
        return False; 
    return f(s[1:-1])


s = str(input())

print(f(s))
