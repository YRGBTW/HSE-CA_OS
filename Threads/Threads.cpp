#include <iostream>
#include <mutex>
#include <fstream>
#include <string>
using namespace std;
using namespace System;
using namespace System::Threading;

fstream file;

public ref class MyBuffer
{
public:
    int bufArr;
    bool availability, fileBuf;
    Mutex^ mx;  
    MyBuffer()
    {
        bufArr = 0;
        availability = false;
        mx = gcnew Mutex();
        fileBuf = false;
    }

    void Write(int value)
    {
        mx->WaitOne();
        if (!fileBuf) {
            bufArr = value;
            availability = true;
        }
        else {
            file.open("output.txt", ios::out);
            file << value << endl;
            if (!file) {
                cout << "Error while writing!" << file.rdstate() << endl;
            }
            file.close();
        }
        mx->ReleaseMutex();
    }

    int Read()
    {
        int value;
        mx->WaitOne();
        if (!fileBuf) {
            value = bufArr;
            availability = false;
        }
        else {
            file.open("output.txt", ios::in);
            string read;
            getline(file, read);
            if (!file) {
                cout << "Error while writing!" << file.rdstate() << endl;
            }
            file.close();
            value = stoi(read);
        }
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
        while (!bufArr->availability) {
            Thread::Sleep(500);
        }
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

