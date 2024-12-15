#pragma once
#include <unistd.h>
#include <sys/syscall.h>

namespace CurrentThread {
	thread_local int _tid = -1;
	void recordTid();
	inline int tid() {
		if (_tid < 0) {
			recordTid();
		}
		return _tid;
	}
}
