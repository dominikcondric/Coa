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
		ConsistentVector(const ConsistentVector& other) = default;
		ConsistentVector& operator=(const ConsistentVector& other) = default;
		ConsistentVector(ConsistentVector&& other) noexcept = default;
		ConsistentVector& operator=(ConsistentVector&& other) noexcept = default;

		T& operator[](uint32_t index) 
		{
			return data[index];
		}

		const T& operator[](uint32_t index) const
		{
			return data[index];
		}

		std::size_t size() const
		{
			return data.size();
		}

		bool empty() const
		{
			return size() == 0;
		}

		void erase(uint32_t index)
		{
			assert(index < data.size());
			data[index] = std::move(data.back());
			data.pop_back();
			if (data.capacity() - data.size() > 20)
				data.shrink_to_fit();
		}

		template<typename ...Args>
		T& emplaceBack(Args&& ...args)
		{
			return data.emplace_back(std::forward<Args>(args)...);
		}

		void pushBack(T&& element)
		{
			return data.push_back(std::move(element));
		}

		void pushBack(const T& element)
		{
			return data.push_back(element);
		}

		IterableVector<T> makeIterableVector()
		{
			return IterableVector<T>(data);
		}

	protected:
		std::vector<T> data;
	};
}
