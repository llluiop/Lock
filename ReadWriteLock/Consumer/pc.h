#pragma once

#include <vector>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <iostream>

using namespace std;


class PCP
{
public:
	PCP()
	{
		//buf.resize(5);
	}

	void produce()
	{
		unique_lock<mutex> l(m);

		while (buf.size() == 5)
		{
			cv.wait(l);
		}

		++cnt;
		buf.push_back(buf.size() + 1);
		cout << "produce size: " << buf.size() << endl;
		cv.notify_all();
	}

	void consume()
	{
		unique_lock<mutex> l(m);

		while (buf.size() == 0)
		{
			cv.wait(l);
		}

		buf.pop_back();
		cout << "consume size: " << buf.size() << endl;

		cv.notify_all();
	}

private:
	vector<int> buf;
	mutex m;
	condition_variable cv;

public:
	int cnt = 0;
};