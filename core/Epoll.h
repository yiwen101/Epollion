#include <vector>
#include <unordered_map>

class Channel;
class EventLoop;
class TimeStamp;

class Poller {
	public:
		Poller(EventLoop* loop);
		~Poller();

		virtual TimeStamp poll(int timeOutMS, std::vector<Channel*>* channels);
		virtual void mustAddChannel(Channel* channel);
		virtual void mustDeleteChannel(Channel* channel);
		bool hasChannel(Channel* channel);

	protected:
		std::unordered_map<int,Channel*> channelMap;

	private:
		EventLoop* ownerLoop;
};


