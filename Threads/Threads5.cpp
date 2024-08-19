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
    SemaphoreSlim^ writeSemaphore; // ������� ��� �������� ������� ���������
    SemaphoreSlim^ readSemaphore;  // ������� ��� �������� ������� ���������
    MyBuffer()
    {
        writeIndex = 0;
        readIndex = 0;
        writeCount = 0;
        readCount = 0;
        mx = gcnew Mutex();
        writeSemaphore = gcnew SemaphoreSlim(1, 1); // ������������� �������� ��� ���������
        readSemaphore = gcnew SemaphoreSlim(5, 5);  // ������������� �������� ��� ��������� (5 ��������� ������������)
        fileBuf = false;
    }

    void Write(int value)
    {
        writeSemaphore->Wait(); // ����, ���� �� ����������� ������������ ������
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
        writeSemaphore->Release(); // ����������� ������������ ������
    }

    int Read()
    {
        readSemaphore->Wait(); // ����, ���� �� ����������� ������������ ������
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
        readSemaphore->Release(); // ����������� ������������ ������
        return value;
    }
};

void WriteThread(Object^ buffer)
{
    MyBuffer^ bufArr = (MyBuffer^)buffer;
    for (int i = 0; i < 5; i++)
    {
        bufArr->Write(i);
        Console::WriteLine("������� ������ (������)...: " + i);
        Thread::Sleep(500);
    }
}

void ReadThread(Object^ buffer)
{
    MyBuffer^ bufArr = (MyBuffer^)buffer;
    for (int i = 0; i < 5; i++)
    {
        int result = bufArr->Read();
        Console::WriteLine("������� ������ (������)...: " + result);
        Thread::Sleep(500);
    }
}

int main()
{
    setlocale(LC_ALL, "rus");

    MyBuffer^ bufArr = gcnew MyBuffer();
    vector<Thread^> writers;
    vector<Thread^> readers;

    for (int i = 0; i < 3; i++) // ������� ��� ������-��������
    {
        writers.push_back(gcnew Thread(gcnew ParameterizedThreadStart(&WriteThread)));
        writers[i]->Start(bufArr);
    }

    for (int i = 0; i < 2; i++) // ������� ��� ������-��������
    {
        readers.push_back(gcnew Thread(gcnew ParameterizedThreadStart(&ReadThread)));
        readers[i]->Start(bufArr);
    }

    for (int i = 0; i < 3; i++) // ���� ���������� �������-���������
    {
        writers[i]->Join();
    }

    for (int i = 0; i < 2; i++) // ���� ���������� �������-���������
    {
        readers[i]->Join();
    }

    return 0;
}
