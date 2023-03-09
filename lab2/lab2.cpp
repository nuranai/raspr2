// lab2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "queue.h"
#include <thread>

using namespace std;

int main()
{
    Queue<int> base;

    for (int i = 0; i < 10; i++) {
        base.Push(i);
    }

    int threadNum = 4;
	int elementsToPush = 20;
	int elementsToPop = 21;

    thread* threadArr = new thread[threadNum];

    for (int i = 0; i < 2; i++) {
		threadArr[i] = thread([&base, &elementsToPush]() mutable {
			for (int j = 0; j < elementsToPush; j++) {
				base.Push(j);
			}
			});
    }
	for (int i = 2; i < 4; i++) {
		threadArr[i] = thread([&base, &elementsToPop]() mutable {
			for (int j = 0; j < elementsToPop; j++) {
				int val = base.Pop();
			}
			});
	}
    for (int i = 0; i < 4; i++) {
        threadArr[i].join();
    }

	int leftoutElements = 10 + elementsToPush * 2 - elementsToPop * 2;
	cout << "queue length::" << base.getLength() << " leftout Elements::" << leftoutElements << endl;
	cout << "are equal?::" << (leftoutElements == base.getLength()) << endl;
	while (!base.isEmpty())
	{
		cout << base.Pop() << ' ';
	}
}

