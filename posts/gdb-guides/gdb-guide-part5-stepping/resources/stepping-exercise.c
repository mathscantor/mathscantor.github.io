#include <stdio.h>
#include <stdlib.h>

int fib_num(int n) {

    int left = 0;
    int right = 1;
    int new = 0;

    if (n == 0)
        return left;
    if (n == 1) 
        return right;
    
    for (int i = 1; i < n; i++) {
        new = left + right;
        left = right;
        right = new;
    }

    return new;
}

int main(void) {
    int fib_seq_num;
    printf("Enter Fibonacci Sequence: ");
    scanf("%d", &fib_seq_num);
    printf("Fibonacci Number: %d\n", fib_num(fib_seq_num));
    return 0;
}