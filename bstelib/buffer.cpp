#pragma once
#include <cstring>

namespace JLib
{

	template<typename T>
	class Buffer {
	public:

		Buffer() : Buffer(0){

		}

		Buffer(size_t Size) {
			data_size = Size;
			init_data(Size);
		}

		Buffer(T* input, size_t Size) :  Buffer(Size) {
			memmove(data, input, Size);
		}

		~Buffer() = default;

		size_t size() {
			return data_size;
		}

		Buffer<T>* const operator+=(Buffer<T> rhs) {

			size_t old_size = size();
			init_data(size() + rhs.size());
			memcpy(data + old_size, rhs.data, rhs.size());

			return this;
		}

		T* getData() {

			return data;
		}

	private:
		void init_data(size_t size) {
			data_size = size;
			T* new_data = new T[size+1];

			if (data != nullptr) {
				memcpy(new_data, data, size);
				delete[] data;
			}
			new_data[size] = (T)nullptr;

			data = new_data;
		}

		size_t data_size = 0;
		T* data = nullptr;

	};

}