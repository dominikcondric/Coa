#pragma once
#include <vector>
#include <stdint.h>
#include <cassert>

namespace Coa {
	template<typename T>
	class ConsistentVector {
	public:
		using iterator = typename std::vector<T>::iterator;
		using const_iterator = typename std::vector<T>::const_iterator;

	public:
		ConsistentVector() = default;
		~ConsistentVector() = default;

		size_t size() const
		{
			return vector.size();
		}

		void erase(uint32_t index)
		{
			assert(index < vector.size());
			vector[index] = std::move(vector.back());
			vector.pop_back();
			if (vector.capacity() - vector.size() > 20)
				vector.shrink_to_fit();
		}

		IterableVector<T> makeIterableVector()
		{
			return IterableVector<T>(vector);
		}

	public:
		std::vector<T> vector;
	};
}
