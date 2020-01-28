// Benjamin Le Heup
// V3
// 1/27/2020


#include <iostream>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <unistd.h>
#include <string>
#include <queue>

#define PHILOSOPHER 5
#define Interation 3
using namespace std;

mutex* Chopstick[5];
mutex printlinelock;
mutex enterLine;

bool canEat[5] = {true,true,true,true,true};
queue<int> eatingOrder;

int flag = 1;
bool pickup(int philNumber)
{
     enterLine.lock();
     if(eatingOrder.front() == philNumber)
     {
          eatingOrder.pop();
          enterLine.unlock();
          return true;
     }
     else
     {
          enterLine.unlock();
          return false;
     }
}
void enterLineFunc(int philNumber)
{
     enterLine.lock();
     eatingOrder.push(philNumber);
     enterLine.unlock();
}
void printString(string printit)
{
     printlinelock.lock();
     cout << printit;
     printlinelock.unlock();
}
void philosopherLivingRighty(int philosopherNumber)
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
          enterLineFunc(philosopherNumber);
          while(1)
          {
               if(pickup(philosopherNumber))
                    break;

          }
          Chopstick[(philosopherNumber+1) % PHILOSOPHER]->lock();
          Chopstick[philosopherNumber]->lock();
          eatbegin = "Philosopher " + to_string(philosopherNumber + 1) + " is now eating.\n";
          printString(eatbegin);
          usleep(100);
          Chopstick[(philosopherNumber+1) % PHILOSOPHER]->unlock();
          Chopstick[philosopherNumber]->unlock();
     }

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
          enterLineFunc(philosopherNumber);
          while(1)
          {
               if(pickup(philosopherNumber))
                    break;

          }
          Chopstick[philosopherNumber]->lock();
          Chopstick[(philosopherNumber+1) % PHILOSOPHER]->lock();
          eatbegin = "Philosopher " + to_string(philosopherNumber + 1) + " is now eating.\n";
          printString(eatbegin);
          usleep(100);
          Chopstick[philosopherNumber]->unlock();
          Chopstick[(philosopherNumber+1) % PHILOSOPHER]->unlock();
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
     /*for(i= 0 ; i< PHILOSOPHER; i++)
     {
          philosopher[i] = thread(philosopherLiving, i);
     }*/
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
