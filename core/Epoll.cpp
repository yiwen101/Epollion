#pragma once

#include "Epoll.h"
#include "Channel.h"


Epoll::Epoll(EventLoop *loop) {
	_ownerLoop = loop;
	_fd = ::epoll_create1(EPOLL_CLOEXE);
	if (_fd < 0) {
		//todo
	}
	_events = new std::vector<epoll_event>(16);
}

Epoll::~Epoll() {
	::close(_fd);
}

TimeStamp Epoll::poll(int timeOutMs, Channels* channels) {
	int numEvents = ::epoll_wait(_fd, &*_events.begin(), static_cast<int>(_events.size()), timeOutMs);
	TimeStamp now = TimeStamp::now();
	// save here as errno is volatile
	int savedErrno = errno
	if(numEvents > 0) {
		_fillActiveChannels(int numEvents, Channels* channels);
		if (numEvents == _events.size()) {
			_events.resize(_events.size() * 2);
		}
	} else if (numEvents == 0) {
		//log timeout
	} else {
		//EINTR means interrupted system call, nothing to do with epoll mechanism itself
		if (savedErrno != EINTR) {
			//todo log fatal
		}
	}
	return now;
}
			




bool Epoll::hasChannel(Channel* chan) {
	auto pt = _channelMap.find(chan->fd());_
	return pt != _channelMap.end() && pt->second == chan;
}
	
