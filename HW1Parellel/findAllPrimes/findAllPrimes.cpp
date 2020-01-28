#include <iostream>
#include <thread>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <cmath>
using namespace std;
#define threadNumber 8

mutex lockit;
unsigned long long int total = 2;
bool isPrime(int);
vector<int> allPrimes;

// outputs <execution time> <total number of primes found> <sum of all primes found>
// <top ten maximum primes, listed in order from lowest to highest>

// since negative numbers are not prime I have written this function to only
// check positive numbers to have a higher upper bound
void findPrimes(int start, int end)
{
     for(unsigned int i = start; i<= end; i+=16)
     {
          if(isPrime(i))
          {
               lockit.lock();
               allPrimes.push_back(i);
               total += i;
               lockit.unlock();
          }
     }
}

// credits goes to https://www.geeksforgeeks.org/prime-numbers/
// minor change have been made to the function it will only check for roots up to the square root of the number being checked
bool isPrime(int n)
{
    // Corner case
    if (n <= 1)
        return false;
    // this line of code is left here if even numbers are added to the pool of numbers to be checked
    /*if(n%2 == 0)
    {
         return false;
    }*/

    // Check from 3 to sqrt(n)
    for (int i = 3; i <= sqrt(n); i+=2)
        if (n % i == 0)
            return false;

    return true;
}

// Thread will be spawn in the main function
// The threads in main will use findPrimes to check for primes
int main(int argc, char** argv)
{
     int start = 3;
     unsigned long long int end = 100000000;
     thread primeFinder[threadNumber];
     int startingArray[8] = {3,5,7,9,11,13,15,17};
     unsigned long long int startTime = clock();
     allPrimes.push_back(2);
     for(int i = 0; i<threadNumber;i++)
     {
          primeFinder[i] = thread(findPrimes, startingArray[i], end);
     }
     for(int i = 0; i<threadNumber; i++)
     {
          primeFinder[i].join();
     }

     // this part of the program will print the results as the following:
     // <Execution time> <number of Primes> <sum of all the primes> <list of the 10 greatest prime numbers>
     sort(allPrimes.begin(), allPrimes.end());
     unsigned long long int endTime = clock();
     std::cout << " <"<< (endTime - startTime)/ double(CLOCKS_PER_SEC) << ">";
     cout << " <" << allPrimes.size() << ">";
     cout << " <" << total << " >";
     cout << " <";
     for(int i = 0;i<10 ;i++)
     {
          cout << allPrimes[allPrimes.size()-10+i];
          if(i != 9)
          {
               cout << ", ";
          }
     }
     cout << ">\n";
}
