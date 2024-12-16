#pragma once
#include "Thread.h"
#include "CurrentThread.h"
#include <semaphore.h>

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

void Thread::start() {
	_started = true;
	sem_t sem;
	sem_init(&sem, false, 0);
	
	_thread = std::shared_ptr<std::thread>(new std::thread([&](){
		_tid = CurrentThread::tid();
		sem_post(&sem);
		_f();
	}));
	
	sem_wait(&sem);
}

void Thread::join() {
	if(_started) {
		_joined = true;
		_thread->join();
	}
}

			
	










