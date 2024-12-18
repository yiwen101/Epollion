#pragma once

#include "../common/TimeStamp.h"
#include <sys/epoll.h>
#include <functional>
#include <memory>

class EventLoop;
class Channel {
	public:
		using CallBack = std::function<void()>;
		using ReadCallBack = std::function<void(TimeStamp)>;
		
		Channel(EventLoop *loop, int fd);
		~Channel();
		
		void onEvent(TimeStamp t);
		
		void onRead(ReadCallBack f) {_onRead = f;}
		void onWrite(CallBack f) {_onWrite = f;}
		void onClose(CallBack f) {_onClose = f;}
		void onError(CallBack f) {_onError = f;}
		
		void enableRead() {_enable(_readEvent);}
		void enableWrite() {_enable(_writeEvent);}
		void disableRead() {_disable(_readEvent);}
		void disableWrite() {_disable(_writeEvent);}
		void disableAll() { _events = _noneEvent; update();}


	private:
		int _events;
		int _revents;
		ReadCallBack _onRead;
		CallBack _onWrite;
		CallBack _onClose;	
		CallBack _onError;
		const int _noneEvent = 0;
		const int _readEvent = EpollIn | EPOLLPRI;
		const int _writeEvent = EPOLLOUT;
		void _enable(int flag) {
			_events |= flag; 
			update();
		}
		void _disable(int flag) {
			_events &= ~flag;
			update();
		}
};
		
