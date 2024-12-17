#include <time.h>
#include <string>
#include <iostream>

class TimeStamp {
	public:
		TimeStamp(int64_t microSecondSinceEpoch): _ms(microSecondSinceEpoch) {}
		
		static TimeStamp now() {
			return TimeStamp(time(nullptr));
		}
		
		std::string toString() {
			char buf[128] = {0};
			tm *tm_time = localtime(&_ms);
			snprintf(buf, 128, "%4d/%02d/%02d %02d:%02d:%02d",
				tm_time->tm_year + 1900,
				tm_time->tm_mon + 1,
				tm_time->tm_mday,
				tm_time->tm_hour,
				tm_time->tm_min,
				tm_time->tm_sec);
			return buf;
		}
	
	private:
		int64_t _ms;
};

/*
 * for smoke test
int main() {
	auto t = TimeStamp::now();
	std::cout << t.toString() <<std::endl;
}
*/
	
