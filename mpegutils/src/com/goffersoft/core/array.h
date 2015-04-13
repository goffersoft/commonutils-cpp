/** 
 **
 ** This file is part of mepgutils.
 **
 ** mpegutils is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** mpegutils is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with mpegutils. If not, see <http://www.gnu.org/licenses/>.
 **
 ** This file descrbes the object class of the mpegutils project.
 ** This class contains code to manipulate arrays.
 **/
#ifndef __ARRAY__H__
#define __ARRAY__H__

#include <stdexcept>

namespace com {
namespace goffersoft {
namespace core {

using std::out_of_range;

template <typename T>
struct Array {
  private:
    T* array;

    Array(): array(nullptr) {}

  public:
    Array(T* arr): array(arr) {}
    Array(const Array& arr): array(arr.array) {}

    Array& operator =(T* arr) {
      array = arr;
      return *this;
    }

    Array& operator =(const Array& arr) {
      array = arr.array;
      return *this;
    }

    T& operator [](const unsigned index) {
      return array[index];
    }

    operator T*() { return array; }
};

template <typename T>
struct SafeArray {
  private:
    T* array;
    unsigned size;
  
    SafeArray(): array() {}

  public:

    SafeArray(T* arr, unsigned sz): array(arr), size(sz) { }
    SafeArray(const SafeArray& arr): array(arr.array) {}

    SafeArray& operator =(T* arr) {
      array = arr;
      return *this;
    }

    SafeArray& operator =(const SafeArray& arr) {
      array = arr.array;
      return *this;
    }

    T& operator [](const unsigned index) throw(out_of_range){
      if(index >= size) throw out_of_range("index > size");

      return array[index];
    }

    operator T*() { return array; }

    unsigned get_size() const { return size; }
    void set_size(unsigned sz) const { return size = sz; }
};

template <typename T, unsigned size>
struct StaticArray {
  private:
    T* array;

    StaticArray(): array() {}

   public:
     StaticArray(T* arr): array(arr) {}
     StaticArray(const StaticArray& arr): array(arr.array) {}

     StaticArray& operator =(T* arr) {
       array = arr;
       return *this;
     }

     StaticArray& operator =(const StaticArray& arr) {
       array = arr.array;
       return *this;
     }

     T& operator [](const unsigned index) throw(out_of_range){
       if(index >= size) throw out_of_range("index > size");

       return array[index];
     }
};

} /* com */
} /* goffersoft */
} /* core */

#endif /* __ARRAY_H__ */
