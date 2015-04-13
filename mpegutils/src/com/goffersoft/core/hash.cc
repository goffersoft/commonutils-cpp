#include "hash.h"

using com::goffersoft::core::get_keylen;

template<>
size_t get_keylen<char>(const char& k ) { return sizeof(char); }

template<>
size_t get_keylen<unsigned char>(const unsigned char& k ) { return sizeof(unsigned char); }

template<>
size_t get_keylen<short>(const short& k ) { return sizeof(short); }

template<>
size_t get_keylen<unsigned short>(const unsigned short& k ) { return sizeof(unsigned short); }

template<>
size_t get_keylen<int>(const int& k ) { return sizeof(int); }

template<>
size_t get_keylen<unsigned int>(const unsigned int& k ) { return sizeof(unsigned); }

template<>
size_t get_keylen<long>(const long& k ) { return sizeof(long); }

template<>
size_t get_keylen<unsigned long>(const unsigned long& k ) { return sizeof(unsigned long); }
