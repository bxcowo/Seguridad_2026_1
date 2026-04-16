#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    long long p, q;
} FactorizationValues;

int isPerfectSquare(long long x);
long long gcd(long long a, long long b);
FactorizationValues fermat_factorization(long long n);
FactorizationValues sqrt_reduction(long long n);

int main(void) {
    srand(time(0));

    long long n, fermat_n, even_factor = 1, even_counter = 0;
    scanf("%lld", &n);
    fermat_n = n;

    while(fermat_n % 2 == 0) {
        fermat_n /= 2;
        even_counter++;
    }

    FactorizationValues fermat_results = fermat_factorization(fermat_n);

    printf("p: %lld\n", fermat_results.p);
    printf("q: %lld\n", fermat_results.q);

    if (even_counter != 0) {
        even_factor = (long long) pow(2, even_counter);
        printf("r: %lld\n", even_factor);
        printf("n = p * q * r = %lld\n", fermat_results.p * fermat_results.q * even_factor);
    } else {
        printf("n = p * q = %lld\n", fermat_results.p * fermat_results.q);
    }

    printf("=========================================================================\n");

    if (n < 4){
        printf("El número debe de ser mayor o igual que 4 para usar la factorización de reducción a cuadrado");
    } else {
        FactorizationValues sqrt_results = sqrt_reduction(n);

        printf("p: %lld\n", sqrt_results.p);
        printf("q: %lld\n", sqrt_results.q);
        printf("n = p * q = %lld\n", sqrt_results.p * sqrt_results.q);
    }

    return 0;
}

int isPerfectSquare(long long x) {
    long long root = (long long) sqrt(x);
    return root * root == x;
}

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

FactorizationValues fermat_factorization(long long n) {
    int coincidence = -1;
    long long x, y, diff;
    x = ceil(sqrt(n));

    while (coincidence == -1) {
        diff = (x * x) - n;
        printf("%lld\n", x*x);
        if (isPerfectSquare(diff)) {
            coincidence = 1;
        } else {
            x++;
        }
    }

    y = (long long) sqrt(diff);

    return (FactorizationValues) {x + y, x - y};
}

FactorizationValues sqrt_reduction(long long n) {
    long long i, curr_value, curr_mod, y, a, p;
    y = 2 + ((long long) rand() * (long long) rand()) % (n - 3);
    a = (y * y) % n;
    p = 1;

    for (i = 1; i < n; i++) {
        curr_mod = (i * i) % n ;
        if (curr_mod == a) {
            curr_value = i;
            if ((curr_value % n != y) && (((-curr_value % n) + n) % n != y)) {
                p = gcd(llabs(curr_value - y), n);
                if (p != 1 && p != n) break;
            }
        }
    }

    return (FactorizationValues){ p, n/p };
}
