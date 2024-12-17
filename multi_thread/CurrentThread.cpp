#include "CurrentThread.h"
#include <iostream>

namespace CurrentThread {
	thread_local int _tid = -1;
	void recordTid() {
		if (_tid < 0) {
			_tid = static_cast<pid_t>(::syscall(SYS_gettid));
		}
	}
}
/* smoke test
#include <vector>
#include <thread>

void f(int i) {
	std::cout << "Thread " << i <<" tid " << CurrentThread::tid() <<std::endl;
}

int main() {
	const int numThreads = 10;
	std::vector<std::thread> threads;
	for (int i=0;i<numThreads;i++) {
		threads.emplace_back(f,i);
	}
	
	for(auto& t:threads) {
		t.join();
	}
	return 0;
}
*/
