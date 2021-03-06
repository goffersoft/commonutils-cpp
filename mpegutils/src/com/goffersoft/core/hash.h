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
#ifndef __HASH_H__
#define __HASH_H__

#include "list.h"

#include "array.h"
#include "hash_types.h"

namespace com {
namespace goffersoft {
namespace core {

using com::goffersoft::core::SLink;
using com::goffersoft::core::ISList;
using com::goffersoft::core::SafeArray;
using com::goffersoft::core::HashType;
using com::goffersoft::core::ForwardListIterator;

template<typename K> size_t get_keylen(const K& k ) { return k.length(); }

template<> size_t get_keylen<char>(const char& k );

template<> size_t get_keylen<unsigned char>(const unsigned char& k );

template<> size_t get_keylen<short>(const short& k );

template<> size_t get_keylen<unsigned short>(const unsigned short& k );

template<> size_t get_keylen<int>(const int& k );

template<> size_t get_keylen<unsigned int>(const unsigned int& k );

template<> size_t get_keylen<long>(const long& k );

template<> size_t get_keylen<unsigned long>(const unsigned long& k );

template <typename K, typename V>
struct HashBucket;

template <typename K, typename V>
struct HashEntry : public SLink {
  private :
    const K& key;
    V& value;

  public :
    typedef HashEntry<K, V> NodeType;
    HashEntry(const K& k, const V& v) : key(k), value((V&)v) {}
    const K& get_key() const { return key; }
    const V& get_value() const { return value; }
    void set_key(const K& k) { key = k; }
    void set_value(const V& v) { value = v; }
};

template <typename K, typename V>
class Hash;

template <typename K, typename V>
struct HashBucket {
  public:
    typedef ISList<HashEntry<K, V> > ListType;
    typedef ForwardListIterator<ListType,
                                HashEntry<K, V> > IteratorType;

  private:
    ListType list;
    const HashType<K>& hash_type;

    const V* create_node(const K& key,
                         const V& value,
                         HashEntry<K, V>* prev) {
      HashEntry<K, V>* node = new HashEntry<K, V>(key, value);
      list.insert(node, prev);
      return &value;
    }

    const V* delete_node(HashEntry<K, V>* node,
                         HashEntry<K, V>* prev) {
      list.remove(node, prev);
      const V& v = node->get_value();
      delete node;
      return v;
    }

  public:
    HashBucket(const HashType<K>& ht) : hash_type(ht) {}
    ListType* get_list() { return &list; }

   
    const V* put(const K& key, const V& value) {
      IteratorType it = list.begin();
      IteratorType it_end = list.end();
      HashEntry<K, V>* node = nullptr;
      HashEntry<K, V>* prev= nullptr;
      int cmp;

      for (; it != it_end; ++it) {
        node = *it;
        cmp = hash_type.compare()(node->get_key(), key); 
        if (cmp == 0) {
          node->set_value(value);
          return nullptr;
        } else if (cmp > 0) {
          return create_node(key, value, prev);
        }
        prev = node;
      }
      return create_node(key, value, prev);
    }

    const V* del(const K& key) {
      IteratorType it = list.begin();
      IteratorType it_end = list.end();
      HashEntry<K, V>* node = nullptr;
      HashEntry<K, V>* prev = nullptr;
      int cmp;

      for (; it != it_end; ++it) {
        node = *it;
        cmp = hash_type.compare()(node->get_key(), key); 
        if (cmp == 0) {
          return delete_node(node, prev);
        } else if (cmp > 0) {
          break;
        }
        prev = node;
      }
      return nullptr;
    }
 
    const V* get(const K& key) const {
      IteratorType it = list.begin();
      IteratorType it_end = list.end();
      HashEntry<K, V>* node = nullptr;
      int cmp;

      for (; it != it_end; ++it) {
        node = *it;
        cmp = hash_type.compare()(node->get_key(), key); 
        if (cmp == 0) {
          return &node->get_value();
        } else if (cmp > 0) {
          break;
        }
      }
      return nullptr;
    }

    bool has_key(const K& key) const {
      return get(key)?true:false;;
    }

    const K** get_keys() const {
      IteratorType it = list.begin();
      IteratorType it_end = list.end();
      const K** karray = new const K*[get_size()];

      for (int i; it != it_end; ++it) {
        karray[i] = &(*it)->get_key();
      }
      return karray;
    }

    const K** get_keys(const K** karray, unsigned offset) const {
      IteratorType it = list.begin();
      IteratorType it_end = list.end();

      for (int i = offset; it != it_end; ++it, i++) {
        karray[i] = &(*it)->get_key();
      }
      return karray;
    }

    const V** get_values() {
      IteratorType it = list.begin();
      IteratorType it_end = list.end();
      const V** varray = new const V*[get_size()];

      for (int i = 0; it != it_end; ++it, i++) {
        varray[i] = &(*it)->get_value();
      }
      return varray;
    }

    const V** get_values(const V** varray, unsigned offset) {
      IteratorType it = list.begin();
      IteratorType it_end = list.end();

      for (int i = offset; it != it_end; ++it, i++) {
        varray[i] = &(*it)->get_value();
      }
      return varray;
    }

    unsigned get_size() {
        return list.get_size();
    }
};

template <typename K, typename V>
class Hash {
  private :
    unsigned num_buckets;
    HashType<K> hash_type;
    unsigned size;
    HashBucket<K, V>** buckets;

  protected:
    inline void set_size(unsigned sz) { size = sz; }
    inline void incr_size() { size++; }
    inline void decr_size() { size--; }
    inline void set_num_buckets(unsigned nb) { num_buckets = nb; }

    inline HashBucket<K, V>* get_or_create_hash_bucket(const K& key) const {
      unsigned hash = hash_type.hash()(key, get_keylen<K>(key));
      hash &= (get_num_buckets() - 1);
      if(buckets[hash] == nullptr) {
        buckets[hash] = new HashBucket<K, V>(hash_type);
      }
      return buckets[hash];
    }

    inline HashBucket<K, V>* get_hash_bucket(const K& key) const {
      unsigned hash = hash_type.hash()(key, get_keylen<K>(key));
      hash &= (get_num_buckets() - 1);
      return buckets[hash];
    }

  public:
    static const HashType<K>& default_hash_type;

    Hash(unsigned nb,
         const HashType<K>& ht = default_hash_type)
          : hash_type(ht) {
      unsigned j = 0;
      if(nb <= 1) {
        nb = 2;
      } else {
        for(unsigned i = 31; i > 0; i--) {
          j = 1 << i;
          if ((nb & j) == j )
            break;
        }
        num_buckets = j*2;
      }
      buckets = new HashBucket<K, V>*[num_buckets];
      for(unsigned i = 0; i < num_buckets; i++) {
        buckets[i] = nullptr;
      }
    }

    ~Hash() {
      for(unsigned i = 0; i < num_buckets; i++) {
        if(buckets[i])
          delete buckets[i];
      }
      delete[] buckets;
    }

    inline unsigned get_size() const { return size; }
    inline unsigned get_num_buckets() const { return num_buckets; }

    void put(const K& key, const V& value) {
     if(get_or_create_hash_bucket(key)->put(key, value) != nullptr) 
       incr_size();
    }

    void del(const K& key) {
      HashBucket<K, V>* bkt = get_hash_bucket(key);
      if(bkt == nullptr)
        return;
      if(bkt->del(key) != nullptr)
        decr_size();
    }
 
    V* get(const K& key) {
      HashBucket<K, V>* bkt = get_hash_bucket(key);
      if(bkt == nullptr)
        return nullptr;
      return (V*)(bkt->get(key));
    }

    V* operator [](const K& key) {
      return get(key);
    }

    bool has_key(const K& key) const {
      HashBucket<K, V>* bkt = get_hash_bucket(key);
      if(bkt == nullptr)
        return false;
      return bkt->has_key(key);
    }

    SafeArray<const K*> get_keys() {
        K **array = new const K*[get_size()];
        unsigned offset = 0;
        for(int i = 0; i < get_num_buckets(); i++) {
          if(buckets[i] == nullptr) {
            continue;
          }
          buckets[i]->get_keys(array, offset);
          offset += buckets[i]->get_size();
        }
        return SafeArray<const K*>(array, offset);
    }

    SafeArray<const V*> get_values() {
        V **array = new const V*[get_size()];
        unsigned offset = 0;
        for(int i = 0; i < get_num_buckets(); i++) {
          if(buckets[i] == nullptr) {
            continue;
          }
          buckets[i]->get_values(array, offset);
          offset += buckets[i]->get_size();
        }
        return SafeArray<const V**>(array, offset);
    }
};

template <typename K, typename V>
const HashType<K>&
Hash<K,V>::
default_hash_type = HashType<K>();

} /* com */
} /* goffersoft */
} /* core */

#endif /* __HASH_H__ */
