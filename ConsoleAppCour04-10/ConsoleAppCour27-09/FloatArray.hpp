#pragma

#include <functional>

class FloatArray {
public:
	FloatArray(int maxSize);

	void set(int idx, float value);

	int get(int idx);

	void Resize(int newsize);

	void shiftright();

	void pushFirst(float value);

	void pushLast(float value);

	void print();

	void iter(std::function<void(float)> f) {
		for (int i = 0; i < currentSize; i++)
			f(data[i]);
	}

protected:
	float* data = nullptr;
	int allocSize = 0;
	int currentSize = 0;
};