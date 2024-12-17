#pragma once
#include "Thread.h"
#include "CurrentThread.h"
#include <semaphore.h>

std::atomic_int Thread::_numCreated(0); 

Thread::Thread(ThreadFunc f, const std::string &name) {
	_tid = -1;
	_f = f;
	_numCreated++;
	_name = name !="" ? name : "Thread" + std::to_string(_numCreated); 
}

Thread::~Thread() {
	if (_started && !_joined) {
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
/* my smoke test
#include<vector>
#include<functional>
#include<iostream>
int main() {
	// test thread name
	std::vector<Thread> threads;
	for(int i=0; i<10;i++) {
		std::function<void()> f = [i](){
			int million = 1e6;
			for (int j = 1; j <= 100*million;j++) {
				if(j%(10*million) == 0) {
					std::cout<<"function " <<i <<"executed "<< j/million <<" million(s) times." << std::endl;
				}
			}	
		};
		threads.emplace_back(f);
		std::cout << threads[i].name() <<" created\n";
	}
	// test thread tid
	for(int i=0; i<10; i++) {
		threads[i].start();
		std::cout <<threads[i].name() <<" started, tid is " << threads[i].tid() <<"\n";
	}
	// test start and join
	for(int i=0;i<10;i++) {
		threads[i].join();
		std::cout << threads[i].name() <<" joined\n";
	}
}
		
*/
			
	










