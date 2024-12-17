#pragma once

#include <functional>
#include <thread>
#include <atomic>
#include <string>
#include <memory>

class Thread {
	public:
		using ThreadFunc = std::function<void()>;
		
		explicit Thread(ThreadFunc f, const std::string &name = "");
		~Thread();
		
		void start();
		void join();
		
		const std::string& name() const {return _name;}
		pid_t tid() const {return _tid;}
		static int numCreated() {return _numCreated;}
	private:
		bool _started = false;
		bool _joined = false;
		std::shared_ptr<std::thread> _thread;
		std::string _name;
		pid_t _tid;
		ThreadFunc _f;
		static std::atomic_int _numCreated;
};

