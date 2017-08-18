// Consumer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "pc.h"

int main()
{
	PCP pc;
	for (int i = 0; i < 100; i++)
	{
		auto t = thread([&] { pc.produce(); });
		t.detach();
	}

	for (int i = 0; i < 100; i++)
	{
		auto t = thread([&] {pc.consume(); });
		t.detach();
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	cout << "hhhhh" << pc.cnt << endl;
	return getchar();
}

