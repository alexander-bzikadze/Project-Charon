#pragma once

#include <cstddef>

template<class T, size_t size>
class PCqueue
{
public:
	T top_front() const
	{
		return container[begin];
	}

	void push_front(T value)
	{
		begin = move_iterator_forward(begin);
		container[begin] = value;
	}

	T pop_back()
	{
		size_t prev_end = end;
		end = move_iterator_forward(end);
		return container[prev_end];
	}

	T sum() const
	{
		T sum = 0;
		for (auto i = end; i != begin; i = i != size - 1 ? i++ : 0)
		{
			sum += container[i];
		}
		return sum;
	}

	size_t element_number() const
	{
		return begin - end > 0 ? begin - end : begin - end + size;
	}

private:
	size_t move_iterator_forward(size_t iterator)
	{
		iterator++;
		if (iterator == size)
		{
			iterator = 0;
		}
		return iterator;
	}

	size_t begin = 0;
	size_t end = 0;
	T container[size] = {};
};