#pragma once
#include <unistd.h>
#include <sys/syscall.h>

namespace CurrentThread {
	extern thread_local int _tid;
	void recordTid();
	inline int tid() {
		if (_tid < 0) {
			recordTid();
		}
		return _tid;
	}
}
