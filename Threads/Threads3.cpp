#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

using namespace System;
using namespace System::Threading;

public ref class Philosopher
{
public:
    int id;
    Mutex^ leftChopstick;
    Mutex^ rightChopstick;

    Philosopher(int philosopherId, Mutex^ left, Mutex^ right)
    {
        id = philosopherId;
        leftChopstick = left;
        rightChopstick = right;
    }

    void Start()
    {
        while (true)
        {
            PickUpChopsticks();
            EatMeal();
            PutDownChopsticks();
        }
    }

    void PickUpChopsticks()
    {
        Console::WriteLine("������� {0} ��������� ����� �������.", id);

        leftChopstick->WaitOne();
        rightChopstick->WaitOne();

        Console::WriteLine("������� {0} ���� �������.", id);
    }

    void EatMeal()
    {
        Console::WriteLine("������� {0} ���.", id);
        Thread::Sleep(2000);
    }

    void PutDownChopsticks()
    {
        Console::WriteLine("������� {0} ������ �������.", id);

        leftChopstick->ReleaseMutex();
        rightChopstick->ReleaseMutex();
    }
};

int main()
{
    array<Mutex^>^ chopsticks = gcnew array<Mutex^>(5);

    for (int i = 0; i < 5; ++i)
    {
        chopsticks[i] = gcnew Mutex();
    }

    array<Philosopher^>^ philosophers = gcnew array<Philosopher^>(5);

    for (int i = 0; i < 5; ++i)
    {
        philosophers[i] = gcnew Philosopher(i + 1, chopsticks[i], chopsticks[(i + 1) % 5]);
    }

    array<Thread^>^ philosopherThreads = gcnew array<Thread^>(5);

    for (int i = 0; i < 5; ++i)
    {
        philosopherThreads[i] = gcnew Thread(gcnew ThreadStart(philosophers[i], &Philosopher::Start));
        philosopherThreads[i]->Start();
    }


    Thread::Sleep(10000);

    //��������� �������
    for (int i = 0; i < 5; ++i)
    {
        philosopherThreads[i]->Interrupt();
        philosopherThreads[i]->Join();
    }

    return 0;
}
