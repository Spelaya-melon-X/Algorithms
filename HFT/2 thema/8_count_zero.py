def f(n) : 
    if ( n == 0 ) : 
        return 0 ; 
    return f(n // 10 ) + ( n % 10 == 0 )


n = int(input())
print(f(n))


