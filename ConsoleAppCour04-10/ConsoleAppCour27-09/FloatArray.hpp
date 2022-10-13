#pragma

#include <functional>

class FloatArray {
public:
	FloatArray(int maxSize);

	FloatArray(const FloatArray& from) {
		Resize(from.currentSize);
		currentSize = from.currentSize;
		for (int i = 0; i < currentSize; i++)
			data[i] = from.data[i];
	};

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

	static FloatArray fromArray(float* data, int len) {
		FloatArray newArray(0);
		newArray.Resize(len);
		for (int i = 0; i < len; i++) {
			newArray.pushLast(i);
		}
		return newArray;
	};

protected:
	float* data = nullptr;
	int allocSize = 0;
	int currentSize = 0;
};;