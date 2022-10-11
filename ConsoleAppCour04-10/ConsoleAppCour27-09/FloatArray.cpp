#include "FloatArray.hpp"

#include <string>

using namespace std;

FloatArray::FloatArray(int maxsize) {
	data = (float*)malloc(maxsize * sizeof(float));
	allocSize = maxsize;
	for (int i = 0; i < allocSize - 1; i++)
	{
		data[i] = 0;
	}
}

void FloatArray::set(int idx, float value)
{
	data[idx] = value;
	currentSize++;
}

int FloatArray::get(int idx)
{
	return data[idx];
}

void FloatArray::Resize(int newsize) {
	if (newsize < allocSize)
		return;
	data = (float*)realloc(data, newsize * sizeof(float));
	for (int i = allocSize; i < newsize; i++)
		data[i] = 0;
	allocSize = newsize;
}

void FloatArray::pushFirst(float value)
{
	if(currentSize >= allocSize-1)
		Resize(allocSize + 1);

	shiftright();
	data[0] = value;
	currentSize++;
}

void FloatArray::shiftright() {
	for (int i = currentSize; i > 0; i--)
	{
		data[i] = data[i - 1];
	}
}

void FloatArray::pushLast(float value)
{
	Resize(allocSize + 1);
	data[currentSize] = value;
	currentSize++;
}

void FloatArray::print()
{
	for (int i = 0; i < currentSize; i++)
	{
		printf("%f ", data[i]);
	}
	printf("\n");
}
