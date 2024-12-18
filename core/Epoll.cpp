#pragma once

#include "Epoll.h"
#include "Channel.h"

const int kNew = -1;
const int kAdded = 1;
const int kDeleted = 2;

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
			
void updateChannel(Channel* chan) {
	int status = channel->status();
	if(status == kNew || status == kDeleted) {
		if (status == kNew) {
			int fd = chan->fd();
			_channels[fd] = chan;
		}
		chan->setStatus(kAdded);
		_update(EPOLL_CTL_ADD, chan);
	} else {
		int fd = chan->fd();
		if(! chan->hasInterestedEvent) {
			_update(EPOLL_CTL_DEL, chan);
			chan->set_status(kDeleted);
		} else {
			_update(EPOLL_CTL_MOD, chan);
		}
	}
}

void Epoll::mustDeleteChannel(Channel* chan) {
	int fd = chan->fd();
	_channelMap.erase(fd);
	int status = chan->status();
	if(status == kAdded) {
		_update(EPOLL_CTL_DEL, chan);
	}
	chan->setStatus(kNew);
}

void Epoll::_update(int operation, Channel* chan) {
	epoll_event event;
	bzero(&event, sizeof event);
	
	int fd = chan->fd();
	event.events = chan->getInterestedEventMask();
	event.data.fd = fd;
	event.data.ptr = chan;
	
	if(::epoll_ctl(_fd, operation, fd, &event) != 0) {
		//todo log error
	}
}

void Epoll::_fillActiveChannels(int numEvents, Channels* activeChans) {
	for(int i=0;i<numEvents;i++) {
		epoll_event event = _events[i];
		Channel* chan = static_cast<Channel*> (event.data.ptr);
		activeChans.push_back(chan);
		chan->setRevents(event.events);
	}
}

bool Epoll::hasChannel(Channel* chan) {
	auto pt = _channelMap.find(chan->fd());_
	return pt != _channelMap.end() && pt->second == chan;
}	
