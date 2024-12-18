#pragma once

#include <functional>
#include <vector>
#include <memory>
class Channel;
class Epoll;
class EventLoop {
	public:
		EventLoop();
		~EVentLoop();
		
		void run();
		void quit();
		using Task = std::function<void()>;
		void addTask(Task t);
		void wakeUp();
		
		void mustAddChannel(Channel *c);
		void mustDeleteChannel(Channel *c);
		bool hasChannel(Channel *c);
	private:
		std::vector<Channel*> _channels;
		std::unique_ptr<Epoll> _epoll;
		std::vector<Task> _tasks;
		
};

