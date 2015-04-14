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
 ** This class contains code to manipulate hash tables.
 **/
#include "hash.h"

template<>
size_t com::goffersoft::core::get_keylen<char>(const char& k ) { return sizeof(char); }

template<>
size_t
com::goffersoft::core::get_keylen<unsigned char>(const unsigned char& k ) {
  return sizeof(unsigned char);
}

template<>
size_t
com::goffersoft::core::get_keylen<short>(const short& k ) {
  return sizeof(short);
}

template<>
size_t
com::goffersoft::core::get_keylen<unsigned short>(const unsigned short& k ) {
  return sizeof(unsigned short);
}

template<>
size_t
com::goffersoft::core::get_keylen<int>(const int& k ) {
  return sizeof(int);
}

template<>
size_t
com::goffersoft::core::get_keylen<unsigned int>(const unsigned int& k ) {
  return sizeof(unsigned);
}

template<>
size_t
com::goffersoft::core::get_keylen<long>(const long& k ) {
  return sizeof(long);
}

template<>
size_t
com::goffersoft::core::get_keylen<unsigned long>(const unsigned long& k ) {
  return sizeof(unsigned long);
}
