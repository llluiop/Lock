// ReadWriteLock.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ReadWriteLock.h"
#include <thread>

using namespace std;

int main()
{
	ReadWriteLock rw;
	for (int i = 0; i < 10; i++)
	{
		auto t = thread([&] {rw.read().lock(&rw); cout << "thread run: " << this_thread::get_id() << endl << flush; rw.read().unlock(&rw); });
		t.detach();

		t = thread([&] {rw.write().lock(&rw); cout << "thread run: " << this_thread::get_id() << endl << flush; rw.write().unlock(&rw); });
		t.detach();
	}

    return getchar();
}

