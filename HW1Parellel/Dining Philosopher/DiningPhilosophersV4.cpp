// Benjamin Le Heup
// V4
// 1/27/2020


#include <iostream>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <unistd.h>
#include <string>
#include <queue>

using namespace std;

mutex *Chopstick;
mutex printlinelock;
mutex enterLine;

queue<int> eatingOrder;

int flag = 1;
int numPhilosopher;
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
          Chopstick[philosopherNumber].lock();
          Chopstick[(philosopherNumber+1) % numPhilosopher].lock();
          eatbegin = "Philosopher " + to_string(philosopherNumber + 1) + " is now eating.\n";
          printString(eatbegin);
          usleep(100);
          Chopstick[philosopherNumber].unlock();
          Chopstick[(philosopherNumber+1) % numPhilosopher].unlock();
     }

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
          Chopstick[(philosopherNumber+1) % numPhilosopher].lock();
          Chopstick[philosopherNumber].lock();
          eatbegin = "Philosopher " + to_string(philosopherNumber + 1) + " is now eating.\n";
          printString(eatbegin);
          usleep(100);
          Chopstick[(philosopherNumber+1) % numPhilosopher].unlock();
          Chopstick[philosopherNumber].unlock();
     }

}

int main(int argc, char** argv)
{
     int i;
     char stop=' ';
     numPhilosopher = atoi(argv[1]);
     Chopstick = new mutex[numPhilosopher];
     thread* philosopher = new thread[numPhilosopher];
     /*for(i= 0 ; i< numPhilosopher; i++)
     {
          philosopher[i] = thread(philosopherLiving, i);
     }*/
     for(i= 0 ; i< numPhilosopher; i++)
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
     for(int i = 0; i<numPhilosopher; i++)
     {
          philosopher[i].join();
     }

     return 0;
}
