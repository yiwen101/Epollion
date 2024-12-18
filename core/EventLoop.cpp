#include "EventLoop.h"
#include <sys/eventfd.h>

// ensure no multi creation per thread;
thread_local EventLoop *thread_loop = nullptr;

EventLoop::EventLoop() {
	if (thread_loop != nullptr) {
		// todo: fatal, log and  exit
	}
	thread_loop = this;
	
	_wakeupFd = ::eventfd(0, EFD_NONBLOCK|EFD_CLOEXEC);
	if (_wakeUpFd < 0) {
		// fatal
	}
	_wakeupChannel = new Channel(this, _wakeupFd);
	_wakeupChannel->onRead(std::bind(&EventLoop::_tryGotWokeup, this));
	_wakeupChannel->enableRead();
	
}
	
EventLoop::~EventLoop() {
	_wakeupChannel->disableAll();
		

