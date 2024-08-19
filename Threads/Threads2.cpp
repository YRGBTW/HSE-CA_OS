#include <iostream>
#include <mutex>
#include <string>
using namespace std;
using namespace System;
using namespace System::Threading;

public ref class MyBuffer
{
public:
    int* bufArr = new int [5];
    int writeIndex, readIndex, writeCount, readCount;
    Mutex^ mx;
    MyBuffer()
    {
        writeIndex = 0;
        readIndex = 0;
        writeCount = 0;
        readCount = 0;
        mx = gcnew Mutex();
    }

    void Write(int value)
    {
        mx->WaitOne();
        while (writeIndex == readIndex && writeCount != readCount)
        {
            mx->ReleaseMutex();
            Thread::Sleep(10);
            mx->WaitOne();
        }
        bufArr[writeIndex] = value;
        writeIndex = (writeIndex + 1) % 5;
        writeCount++;
        mx->ReleaseMutex();
    }

    int Read()
    {
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
    }
}

int main()
{
    setlocale(LC_ALL, "rus");

    MyBuffer^ bufArr = gcnew MyBuffer();
    Thread^ writer = gcnew Thread(gcnew ParameterizedThreadStart(&WriteThread));
    Thread^ reader = gcnew Thread(gcnew ParameterizedThreadStart(&ReadThread));

    writer->Start(bufArr);
    reader->Start(bufArr);

    writer->Join();
    reader->Join();

    return 0;
}

