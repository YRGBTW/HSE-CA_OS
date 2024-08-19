#include <iostream>
#include <mutex>
#include <string>
#include <vector>

using namespace std;
using namespace System;
using namespace System::Threading;
fstream file;
public ref class MyBuffer
{
public:
    int* bufArr = new int[5];
    int writeIndex, readIndex, writeCount, readCount;
    bool fileBuf;
    Mutex^ mx;
    SemaphoreSlim^ writeSemaphore; // Семафор для контроля доступа писателей
    SemaphoreSlim^ readSemaphore;  // Семафор для контроля доступа читателей
    MyBuffer()
    {
        writeIndex = 0;
        readIndex = 0;
        writeCount = 0;
        readCount = 0;
        mx = gcnew Mutex();
        writeSemaphore = gcnew SemaphoreSlim(1, 1); // Инициализация семафора для писателей
        readSemaphore = gcnew SemaphoreSlim(5, 5);  // Инициализация семафора для читателей (5 читателей одновременно)
        fileBuf = false;
    }

    void Write(int value)
    {
        writeSemaphore->Wait(); // Ждем, пока не освободится писательский ресурс
        mx->WaitOne();
        while (writeIndex == readIndex && writeCount != readCount)
        {
            mx->ReleaseMutex();
            Thread::Sleep(10);
            mx->WaitOne();
        }
        if (fileBuf) 
        {

        }
        bufArr[writeIndex] = value;
        writeIndex = (writeIndex + 1) % 5;
        writeCount++;
        mx->ReleaseMutex();
        writeSemaphore->Release(); // Освобождаем писательский ресурс
    }

    int Read()
    {
        readSemaphore->Wait(); // Ждем, пока не освободится читательский ресурс
        int value;
        while (writeIndex == readIndex && writeCount == readCount)
        {
            mx->ReleaseMutex();
            Thread::Sleep(10);
            mx->WaitOne();
        }
        value = bufArr[readIndex];
        readIndex = (readIndex + 1) % 5;
        readCount++;
        mx->ReleaseMutex();
        readSemaphore->Release(); // Освобождаем читательский ресурс
        return value;
    }
};

void WriteThread(Object^ buffer)
{
    MyBuffer^ bufArr = (MyBuffer^)buffer;
    for (int i = 0; i < 5; i++)
    {
        bufArr->Write(i);
        Console::WriteLine("Процесс потока (Запись)...: " + i);
        Thread::Sleep(500);
    }
}

void ReadThread(Object^ buffer)
{
    MyBuffer^ bufArr = (MyBuffer^)buffer;
    for (int i = 0; i < 5; i++)
    {
        int result = bufArr->Read();
        Console::WriteLine("Процесс потока (Чтение)...: " + result);
        Thread::Sleep(500);
    }
}

int main()
{
    setlocale(LC_ALL, "rus");

    MyBuffer^ bufArr = gcnew MyBuffer();
    vector<Thread^> writers;
    vector<Thread^> readers;

    for (int i = 0; i < 3; i++) // Создаем три потока-писателя
    {
        writers.push_back(gcnew Thread(gcnew ParameterizedThreadStart(&WriteThread)));
        writers[i]->Start(bufArr);
    }

    for (int i = 0; i < 2; i++) // Создаем два потока-читателя
    {
        readers.push_back(gcnew Thread(gcnew ParameterizedThreadStart(&ReadThread)));
        readers[i]->Start(bufArr);
    }

    for (int i = 0; i < 3; i++) // Ждем завершения потоков-писателей
    {
        writers[i]->Join();
    }

    for (int i = 0; i < 2; i++) // Ждем завершения потоков-читателей
    {
        readers[i]->Join();
    }

    return 0;
}
