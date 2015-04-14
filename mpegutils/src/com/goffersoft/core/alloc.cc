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
 ** This class contains code to rlated to memory management.
 **/
#include <iostream>
#include <string>
#include "list.h"
#include "hash.h"
#include "array.h"
#include "assert_helper.h"

using std::cout;
using std::endl;
using std::hex;
using std::string;
using com::goffersoft::core::SLink;
using com::goffersoft::core::DLink;
using com::goffersoft::core::SList;
using com::goffersoft::core::ISList;
using com::goffersoft::core::DList;
using com::goffersoft::core::IDList;
using com::goffersoft::core::AssertHelper;

static char membase[1024];
static char poolbase[256];
char* membase_ptr = membase;
char* poolbase_ptr = poolbase;

struct mem;

struct Pool : public SLink {
  unsigned sz;
  mem* mempool;
};

struct mem : public SLink {
  Pool* pool;
};

static Pool* list_of_pools;

#if 0
void* operator new(size_t sz) throw(std::bad_alloc) {
  cout<< "My New Called" << endl;
  Pool* x = list_of_pools;
  bool create_pool = true;

  while (x) {
    if (x->sz == sz) {
      create_pool = false;
      if (x->mempool) {
        void* ptr = (void*)(x->mempool + sizeof(mem));
        x->mempool = (mem*)x->mempool->get_next();
        return ptr;
      }
      break;
    }
    x = (Pool*)x->get_next();
  }
  membase_ptr += sz + sizeof(mem);
  char* mem_ptr = membase_ptr - sz - sizeof(mem);
  if (create_pool) {
    x = (Pool*)poolbase_ptr;
    poolbase_ptr += sizeof(Pool);
    x->set_next(0);
    x->sz = sz;
    x->mempool = 0;
    if (list_of_pools) {
      x->set_next((SLink*)list_of_pools);
    }
    list_of_pools = x;
  }
  ((mem*)mem_ptr)->pool = x;
  return (void *)(mem_ptr + sizeof(mem));
}

void operator delete(void* ptr) throw() {
  cout<< "My Delete Called" << endl;
  mem* mem_ptr = (mem*)((char*)ptr - sizeof(mem));

  Pool* x = mem_ptr->pool;

  if (x->mempool) {
    mem_ptr->set_next(x->mempool);
  }
  x->mempool = mem_ptr;
  return;
}
#endif

void print_mem_pool() {
  Pool* x = list_of_pools;
  mem* y;
  while (x) {
    cout<<"{pool=0x"<<hex<<(long)x<<", sz="<<x->sz<<"}"<<endl;
    y = x->mempool;
    while (y) {
      cout<<"\t{ptr=0x"<<hex<<(long)y<<"}"<<endl;
      y = (mem*)y->get_next();
    }
    cout<<endl;
    x = (Pool*)(x->get_next());
  }
}

struct isl : public SLink {
  int a;
  isl(int aaa) : a(aaa) {}
};

struct dsl : public DLink {
  int a;
  dsl(int aaa) : a(aaa) {}
};

int func(int a[], int size) {
  for (int i = 0; i < size; i++) {
    cout << a[i] << endl;
  }
  return size;
}

int alloc_test_main(int argc, char** argv) {
  int *i = new int(10);
  int *j = new int(20);
  string *s = new string("Hello World");

  int *arr = new int[10];
  int *elem = new int;

  func(arr, 10);
  func(elem, 1);

  SList<int> l1;
  ISList<isl> l2;
  DList<int> l3;
  IDList<dsl> l4;
  int a = 1;

  isl aa(1);
  dsl aaa(1);
  l1.append(a);
  l2.append(aa);
  l3.append(a);
  l4.append(aaa);

  cout << *i << ' ' << *j << ' ' << *s << endl;

  delete i;

  print_mem_pool();
    
  delete j;
    
  print_mem_pool();
    
  delete s;

  AssertHelper::equals(1, *i);
  AssertHelper::not_equals(1, *i);
   
  print_mem_pool();

  return 0;
}
