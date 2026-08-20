// Juan Angel Narvaez Torres
// A00843809

#include <iostream>
using namespace std;

int factorial(int n){
    if (n<=1){
        return 1;
    }
    return n * factorial(n-1);
}

int sumIterative(int n){
    int suma = 0;
    for (int i = 1; i <=n; i++){
        suma += i;
    }
    return suma;
}

int sumRecursive(int n){
    if (n == 1){
        return 1;
    }
    return n + sumRecursive(n-1);
}

int sumFormula(int n){
    return n*(n+1)/2;
}

int fibonacciIterative(int n){
    if ( n == 1 || n == 2){
        return 1;
    }

    if (n <= 0){
        return 0;
    }
    
    int num1 = 1;
    int num2 = 1;
    int fibonacci = 0;

    for (int i = 3; i <= n; ++i) {
        fibonacci = num1 + num2;

        num1 = num2;
        num2 = fibonacci;
    }
    return fibonacci;
}

int fibonacciRecursive(int n){


    if ( n == 1 || n == 2){
        return 1;
    }

    if ( n == 0){
        return 0;
    }

    return fibonacciRecursive(n-1) + fibonacciRecursive(n-2);
}

int bacteriasIterative(int n){
    double born = 3.78;
    double died = 2.34;
    int sum = 1;
    for (int i = 1; i <= n; i++){
        int bacBorn = sum * born;
        int bacDied = sum * died;
        sum += bacBorn - bacDied;
    }
    return sum;
}

int bacteriasRecursive(int n){
    if (n==0){
        return 1;
    }
    int bacterias = bacteriasRecursive(n-1);
    int born = bacterias * 3.78;
    int died = bacterias * 2.34;
    return bacterias + born - died;
}

int investmentIterative(double amount, int n){
    for (int i = 0; i < n; i++){
        amount += (amount * 0.1875);
    }
    return amount;
}
int investmentRecursive(double amount, int n){
    if (n == 0){
        return amount;
    }
    return investmentRecursive(amount +(amount * 0.1875), n-1);
}

int powIterative(int n, int y){
    int resultado = 1;
    for (int i=0; i < y; i++){
        resultado *= n;
    }
    return resultado;
}
int powRecursive(int n, int y){
    if (y == 0){
        return 1;
    }
    return n * powRecursive(n, y-1);
}


int main(){
    cout << "El factorial de 5 es: " << factorial(5) << endl;
    // Suma Iterativa
    cout << "La suma iterativa de 5 es: " << sumIterative(5) << endl;
    // Suma Recursiva
    cout << "La suma recursiva de 5 es: " << sumRecursive(5) << endl;
    // Suma Formula
    cout << "La suma de 5 es: " << sumFormula(5) << endl;
    // Fibonacci Iterativa
    cout << "El sexto numero de la serie Fibonacci es: " << fibonacciIterative(6) << endl;
    // Fibonacci Recursiva
    cout << "El sexto numero de la serie Fibonacci es: " << fibonacciRecursive(6) << endl;
    // Bacteria Iterativo
    cout << "La cantidad de bacterias al dia 5 es: " << bacteriasIterative(5) << endl;
    // Bacteria Recursiva
    cout << "La cantidad de bacterias al dia 5 es: " << bacteriasRecursive(5) << endl;
    // Inversion Iterativa
    cout << "La cantidad de dinero despues de 5 años es: " << investmentIterative(1000, 5) << endl;
    // Inversion Recursiva
    cout << "La cantidad de dinero despues de 5 años es: " << investmentRecursive(1000, 5) << endl;
    // Potencia Iterativa
    cout << "El resultado de 2^5 es: " << powIterative(2, 5) << endl;
    // Potencia Recursiva
    cout << "El resultado de 2^5 es: " << powRecursive(2, 5) << endl;
}