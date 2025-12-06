from  functools import lru_cache

d = dict()

@lru_cache
def calculate(n):
    if n <= 1:
        return 1
    
    initial_value = (n * n) // 3 + func(n - 2)
    while initial_value % 2 == 0:
        initial_value = initial_value // 2

    initial_value += func(2 * n // 3)
    value = func(initial_value % n)

    return value + func(n // 2) + n


def  func( n) : 
    if ( n in d ) : 
        return d[n] 
    else : 
        d[n] = calculate(n) 
        return d[n]
    
for i in range(1, 1000) :
    func(i)


n = int(input())
print(calculate(n))