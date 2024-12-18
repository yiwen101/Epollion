#pragma once
#include <vector>
#include <unordered_map>

#include "../common/TimeStamp.h"

#include <vector>
#include <sys/epoll.h>

class Channel;
class EventLoop;

class Epoll {
	public:
		using Channels = std::vector<Channel*>;
		Epoll(EventLoop* loop);
		~Epoll();

		virtual TimeStamp poll(int timeOutMS, Channels* channels);
		virtual void mustAddChannel(Channel* chan);
		virtual void mustDeleteChannel(Channel* chan);
		bool hasChannel(Channel* chan);

	protected:
		std::unordered_map<int,Channel*> _channelMap;

	private:
		int _fd;
		EventLoop* _ownerLoop;
		std::vector<epoll_event> _events;

		void _update(int operation, Channel* chan);
		void _fillActiveChannels(int numEvents, Channels* activeChans);

};

