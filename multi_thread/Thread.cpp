#pragma once
#include "Thread.h"

Thread::Thread(ThreadFunc f, const std::string &name ="") {
	_tid = -1;
	_f = f;
	_numCreated++;
	_name = name ? name : "Thread" + std::to_string(_numCreated); 
}

Thread::~Thread() {
	if (_started && !joined) {
		_thread->detach();
	}
}

