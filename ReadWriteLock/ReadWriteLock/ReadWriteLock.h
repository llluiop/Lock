#pragma once

#include <mutex>
#include <condition_variable>
#include <iostream>

using namespace std;

class ReadWriteLock
{
public:
	class ReadLock 
	{
	public:
		void lock(ReadWriteLock* rws)
		{
			std::unique_lock<mutex> l(rws->m);
			rws->cv.wait(l, [&] {return rws->writer == false; });
			rws->reader++;
			cout << "readlock lock reader cnt: " << rws->reader << endl << flush;
		}

		void unlock(ReadWriteLock* rws)
		{
			std::unique_lock<mutex> l(rws->m);
			rws->reader--;
			if (rws->reader == 0)
			{
				rws->cv.notify_one();
			}
			cout << "readlock unlock reader cnt: " << rws->reader << endl << flush;
		}
	};

	class WriteLock 
	{
	public:
		void lock(ReadWriteLock* rws)
		{
			std::unique_lock<mutex> l(rws->m);
			rws->cv.wait(l, [&] {return rws->writer == false && rws->reader == 0; });
			rws->writer = true;
			cout << "writelock lock reader cnt: " << rws->reader << endl << flush;

		}

		void unlock(ReadWriteLock* rws)
		{
			std::unique_lock<mutex> l(rws->m);
			rws->writer = false;
			rws->cv.notify_all();
			cout << "writelock unlock reader cnt: " << rws->reader << endl << flush;
		}
	};

public:
	ReadLock read()
	{
		return readlock;
	}

	WriteLock write()
	{
		return writelock;
	}

private:
	int reader = 0;
	bool writer = false;
	ReadLock readlock;
	WriteLock writelock;
	mutex m;
	condition_variable cv;
};
