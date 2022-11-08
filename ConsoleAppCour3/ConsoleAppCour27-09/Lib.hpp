#include <unordered_map>
#include <ctime>

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
};