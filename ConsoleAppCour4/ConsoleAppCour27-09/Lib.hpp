#include <unordered_map>
#include <ctime>

#include <chrono>

using namespace std;
using namespace std::chrono;

class Lib {
public:
	int random() {
		static bool isInit = false;
		if (!isInit) {
			clock_t now = clock();
			srand(now);
			isInit = true;
		}

		return ::rand();
	}

	double GetTimeStamp() {
		std::chrono::nanoseconds ns = duration_cast<nanoseconds>(system_clock::now().time_since_epoch());

		return ns.count() / 1000000000.0;
	}
};