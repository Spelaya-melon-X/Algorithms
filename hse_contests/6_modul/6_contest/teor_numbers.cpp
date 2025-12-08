#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;



// 3 реализации поиска простых чисел чрезе Eratosthenes sieve за O( n log n log n ) только они отличаются на констату 
vector<bool> get_vector_prime_Eratosthenes_sieve_1(int n) {
    std::vector<bool> primes(n , true ); 
    primes[0] = primes[1] = false ;

    for ( int i = 2 ; i <= n ; i++) {
        if (primes[i]) {
            for ( int j = i + i ; j <= n ; j += i) { // помечаем , что все кратные i - не простые 
                primes[j] = false ;
            }
        }
    }
    return primes ;
} 

vector<bool> get_vector_prime_Eratosthenes_sieve_2(int n) {
    std::vector<bool> primes(n , true ); 
    primes[0] = primes[1] = false ;

    for ( int i = 2 ; i * i  <= n ; i++) {
        if (primes[i]) {
            for ( int j = i * i ; j <= n ; j += i) { 
                primes[j] = false ;
            }
        }
    }
    return primes ;
} 

vector<int> help_get_vector_odd_numbers(int n) {
    vector<int> odds ; 
    for ( int i = 0 ; i <= n ; i++) {
        if ( i % 2 == 1 ) {
            odds.push_back(i) ;
        }
    }
    return odds ;
}

vector<bool> get_vector_prime_Eratosthenes_sieve_3(int n) {
    std::vector<bool> primes(n , true ); 
    primes[0] = primes[1] = false ;
    vector<int> odds = help_get_vector_odd_numbers(n) ;

    for ( int i : odds) {
        if (primes[i]) {
            for ( int  j = i + i ; j <= n ; j += 2*i) {
                primes[j] = false ;
            }
        }
    }
    return primes ;
} 


// решето Эратосфера за O(n) и массивы primes , d 
std::pair<std::vector<int > , std::vector<int> > get_vector_prime_Eratosthenes_sieve_line_algoritm(int n) {
    vector<int> primes  , d( n + 1 , -1 ); 
    for ( int y = 2 ; y <= n ; y++) {
        if (d[y] == - 1) {
            d[y] = primes.size() , primes.push_back(y) ; 
        }
        for (int i = 0 ; i <= d[y] && y * primes[i] <= n ; i++) {
            d[y * primes[i]] = i ; 
        }
    }
    return {primes , d} ;
}

// мультипликатинвые функции 
std::tuple<vector<int> , vector<int> , vector<int> , vector<int>  , vector<int>  > create_vector_deg_and_rest_for_multiplicativ_function(int n ) {
    auto [primes , d] = get_vector_prime_Eratosthenes_sieve_line_algoritm(n) ;
    vector<int> p( n +1 , 0 ) , y( n + 1 , 0 ) ;
    for ( int i = 0 ; i <= n ; i++) {
        p[i] = primes[d[i]] ;
    }
    for ( int i = 0 ; i <= n ; i++) {
        y[i] = i / p[i] ;
    }

    vector<int> deg(n + 1 , 0) , rest(n + 1 , 0) ;
    for ( int x = 0 ; x <= n ; x++) {
        if (d[y[x]] == d[x]) {
            deg[x] = deg[y[x]] + 1 ;
            rest[x] = rest[y[x]] ;
        } else {
            deg[x] = 1 ;
            rest[x] = y[x] ;
        }
    }
    return {deg , rest , p , y , d} ;
}

int get_omega_0_numbers_of_divisors(int n  ) { // omega_0
    auto [deg , rest , p , y , d] = create_vector_deg_and_rest_for_multiplicativ_function(n) ;
    vector<int> omega_0(n + 1 , 0) ;
    omega_0[1] = 1 ;
    for ( int x = 2 ; x <= n ; x++) {
        omega_0[x] = omega_0[rest[x]] * (deg[x] + 1) ;
    }
    return omega_0[n] ;
}

int get_eiler_function(int n ) { // phi
    auto [deg , rest , p , y , d] = create_vector_deg_and_rest_for_multiplicativ_function(n) ;
    vector<int> term(n+1 , 0) ;
    for (int i = 0 ; i <= n ; i++) {
        term[i] = i / rest[i] ;
    }
    vector<int> phi(n + 1 ) ;
    phi[1] = 1 ;
    for ( int i = 2 ; i <= n ; i++) {
        phi[i] = phi[rest[i]]  * (term[i] / p[i]) * (p[i] - 1) ; 
    }
    return phi[n] ;
}

int get_summ_devisors(int n ) { // omega_1
    auto [deg , rest , p , y , d] = create_vector_deg_and_rest_for_multiplicativ_function(n) ;
    vector<int> term(n+1 , 0) ;
    for (int i = 0 ; i <= n ; i++) {
        term[i] = i / rest[i] ;
    }
    vector<int> omega_1(n + 1 ) ;
    omega_1[1] = 1 ;
    for ( int i = 2 ; i <= n ; i++) {
        omega_1[i] = omega_1[rest[i]]  * (p[i]* term[i] - 1) / (p[i] - 1 ) ; 
    }
    return omega_1[n] ;
}



tuple<int , int , int > evclid_advenced(int a , int b) {
    if ( b== 0 ) {
        return  {a , 1 , 0} ;
    }

    auto [gcd , x1 , y1 ] = evclid_advenced(b , a % b) ; 
    int x = y1  ,  y = x1 - (a / b) * y1 ;
    return {gcd , x , y} ;
}



tuple<int, int , int >  iter_evclid_advenced(int a , int b) {
    int r0 = a ;  int x0 = 1 ; int y0 = 0 ;
    int r1 = b ; int x1 = 0 ; int y1 = 1; 

    while(r1 != 0 ) {
        int k = r0 / r1 ; 
        int r2 = r0 - k * r1 ; 
        int x2 = x0 - k * x1 ;
        int y2 = y0 - k * y1 ;

        r0  = r1 ; x0 = x1 ; y0 = y1 ;
        r1  = r2 ; x1 = x2 ; y1 = y2 ; 
    }
    return {r0 , x0 , y0} ;
}

std::pair<int , int> Diofant_equation(int a , int b , int c) {
    auto [gcd , x , y] = iter_evclid_advenced(a , b) ; 
    if (c % gcd != 0) return {-1 , -1} ;
    int k = c / gcd ; 
    return {x * k , y * k} ;
}

std::pair<std::string  ,std::string > Diofant_equation_full(int a , int b , int c) {
    
    auto [gcd , x , y ] = iter_evclid_advenced(a,  b) ; 
    if ( c % gcd != 0) return {"-1" , "-1"} ;
    int k = c / gcd ; 
    std::string x1 = to_string(x * k) + "+" + to_string(b / gcd) + "t" ; 
    std::string y1 = to_string(y * k) + "-" + to_string(a / gcd) + "t"  ; 
    return { x1 ,   y1} ;
}


int main() {
    std::cout << get_summ_devisors(72) ; 

    return 0;
}