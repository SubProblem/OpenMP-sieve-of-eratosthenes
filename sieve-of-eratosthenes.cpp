// TODO: implement Sieve of Eratosthenes
#include <iostream>
#include <vector>
#include <math.h>
#include <omp.h>


// Change maximum number of MaxNumif the inputed value is more than 10_000_000
#define MaxNum ((int) 100000000)

std::vector<int> vct(MaxNum, 1);

/* If you want to change the value and number of threads just assign the number you want to those variable*/
const int value=50000, number_of_threads=5;


// Void function to compute seed from 2 to sqrt(n)

void compute_seed(int n) {
    for (int i=2; i<=sqrt(n); i++) {
        if (vct[i] == 1) {
            for (int j=i*i; j<=n; j+=i) {
                vct[j] = 0;
            }
        }
    }
}

// Function to check whether the number k is prime or not
// if is prime return false, else true

bool check_number(int n, int k) {
    for (int i=2; i<=sqrt(n); i++) {
        if ((vct[i] == 1) && (k % i == 0)) {
            return true;
        }
    }
    return false;
}



int main(){

    compute_seed(value);

    // beginning of the chunk
    int start = sqrt(value)+1;

    #pragma omp parallel shared(start) num_threads(number_of_threads) 
    
    {

        #pragma omp for schedule(static)
        for (int i=start; i<value; i++){
            if (vct[i] == 1 && check_number(value, i)) {
                vct[i] = 0;
            }
        }
    }

    for (int i=2; i<=value; i++) {
        if (vct[i] == 1) {
        std::cout << i << " ";
        }   
    }     

    return 0;

}
