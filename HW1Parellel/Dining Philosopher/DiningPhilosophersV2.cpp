// Benjamin Le Heup
// V2
// 1/27/2020


#include <iostream>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <unistd.h>
#include <string>

#define PHILOSOPHER 5
#define Interation 3
using namespace std;

mutex* Chopstick[5];
mutex printlinelock;

int flag = 1;
void printString(string printit)
{
     printlinelock.lock();
     cout << printit;
     printlinelock.unlock();
}

void philosopherLivingLefty(int philosopherNumber)
{
     int i;
     string thinking;
     string eatbegin;
     string hungry;
     int philoNum = philosopherNumber + 1;

     while(flag)
     {
          thinking = "Philosopher " + to_string(philosopherNumber + 1) + " is now thinking\n";
          printString(thinking);
          usleep(500);
          hungry = "Philosopher " + to_string(philosopherNumber + 1) + " is now hungry.\n";
          printString(hungry);
          Chopstick[philosopherNumber]->lock();
          Chopstick[(philosopherNumber+1) % PHILOSOPHER]->lock();
          eatbegin = "Philosopher " + to_string(philosopherNumber + 1) + " is now eating.\n";
          printString(eatbegin);
          usleep(100);
          Chopstick[philosopherNumber]->unlock();
          Chopstick[(philosopherNumber+1) % PHILOSOPHER]->unlock();
     }

}

void philosopherLivingRighty(int philosopherNumber)
{
     int i;
     int iteration = Interation;
     string thinking;
     string eatbegin;
     string hungry;
     int philoNum = philosopherNumber + 1;

     while(flag)
     {
          thinking = "Philosopher" + to_string(philosopherNumber + 1) + " is now thinking\n";
          printString(thinking);
          usleep(500);
          hungry = "Philosopher" + to_string(philosopherNumber + 1) + " is now hungry.\n";
          printString(hungry);
          Chopstick[(philosopherNumber+1) % PHILOSOPHER]->lock();
          Chopstick[philosopherNumber]->lock();
          eatbegin = "Philosopher" + to_string(philosopherNumber + 1) + " is now eating.\n";
          printString(eatbegin);
          usleep(100);
          Chopstick[(philosopherNumber+1) % PHILOSOPHER]->unlock();
          Chopstick[philosopherNumber]->unlock();
     }

}



int main(int argc, char** argv)
{
     thread philosopher[PHILOSOPHER];
     int i;
     char stop=' ';
     for(i = 0;i< PHILOSOPHER;i++)
     {
          Chopstick[i] = new mutex();
     }
     for(i= 0 ; i< PHILOSOPHER; i++)
     {
          if(i % 2 == 1)
               philosopher[i] = thread(philosopherLivingLefty, i);
          if(i % 2 == 0)
               philosopher[i] = thread(philosopherLivingRighty, i);
     }
     while(stop!='n')
     {
          cin >> stop;
     }
     flag = 0;
     for(int i = 0; i<PHILOSOPHER; i++)
     {
          philosopher[i].join();
     }

     return 0;
}
