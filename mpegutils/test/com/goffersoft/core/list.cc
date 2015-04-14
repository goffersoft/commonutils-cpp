/**
 **
 ** This file is part of mpegutils.
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
 ** This file contains test code for the list.h class
 **/
#include <iostream>
#include <typeinfo>

#include "list.h"
#include "hash.h"

using std::endl;
using std::cout;
using std::default_random_engine;
using std::uniform_int_distribution;
using com::goffersoft::core::_SLink;
using com::goffersoft::core::_DLink;
using com::goffersoft::core::SLink;
using com::goffersoft::core::CSLink;
using com::goffersoft::core::DLink;
using com::goffersoft::core::CDLink;
using com::goffersoft::core::TLink;
using com::goffersoft::core::ListBase;
using com::goffersoft::core::ISList;
using com::goffersoft::core::SList;
using com::goffersoft::core::ForwardListIterator;
using com::goffersoft::core::Hash;
using com::goffersoft::core::HashType;

template <typename T, bool circular = false>
void
print_list(T* head) {
  T* link = head;
  T* test_link = nullptr;
  int i = 1;

  if (circular) {
    test_link = head;
  }

  if (link == nullptr) {
    cout << "printing List : <empty>" << endl;
    return;
  } else {
    cout << "printing List :" << endl;
  }

  do {
    cout << "[" << i << "] = "
         << *link->get_info() << endl;
    link = (T*)link->get_next();
    i++;
  } while (link != test_link);
}

template <typename T>
void
delete_slist(T* head, T* tail) {
  T* link;
  cout << "deleting list :" << endl;
  while (head) {
    link = head;
    head = T::remove_head(head, tail);
    delete link;
  }
}

template <typename T>
void
delete_dlist(T* head) {
  T* link;
  cout << "deleting list :" << endl;
  while (head) {
    link = head;
    head = T::remove_head(head);
    delete link;
  }
}

struct TestSLink: public SLink {
  TestSLink(int ii): i(ii) {}
  int i;
  int* get_info() { return &i; }
};

struct TestObject {
  TestObject(int ii): i(ii) {}
  int i;
  int* get_info() { return &i; }
  inline operator int() { return i; }
};

struct TestSLinkCircular: public CSLink {
  TestSLinkCircular(int ii): i(ii) {}
  int i;
  int* get_info() { return &i; }
};

struct TestDLink: public DLink {
  TestDLink(int ii): i(ii) {}
  int i;
  int* get_info() { return &i; }
};

struct TestDLinkCircular : public CDLink {
  TestDLinkCircular(int ii): i(ii) {}
  int i;
  int* get_info() { return &i; }
};

template <typename T, bool circular = false>
void
list_test_dlink() {
  T* head;

  for(int i = 0;  i < 2; i++) {
    head = nullptr;

    print_list<T, circular>(head);

    head = new T(1);

    print_list<T, circular>(head);

    head->insert(new T(2));

    print_list<T, circular>(head);

    head = (T*)T::insert_head(head,
                              new T(3));
 
    head->insert(new T(4));

    print_list<T, circular>(head);

    delete_dlist<_DLink<circular> >(head);
  }
}

template <typename T, bool circular = false>
void
list_test_slink() {
  T* head;
  T* tail;

  for(int i = 0; i < 2; i++) { 
    head = nullptr;
    tail = nullptr;

    print_list<T, circular>(head);

    head = new T(1);

    print_list<T, circular>(head);

    tail = new T(2);
    head->insert(tail);

    print_list<T, circular>(head);

    head = (T*)T::insert_head(head,
                              new T(3),
                              tail);
 
    head->insert(new T(4));

    print_list<T, circular>(head);

    delete_slist<_SLink<circular> >(head, tail);
  }
}
  
template <typename T, typename L, bool circular = false>
void list_test_listbase() {
  ListBase<T> lb;

  T* link = new T(1);
  
  lb.set_head(link);
  lb.set_tail(link);
  lb.set_size(1);

  cout << "List Size:" << lb.get_size() << endl;
    
  print_list<T, circular>(lb.get_head());
  
  delete_slist<L>(lb.get_head(), lb.get_tail());
}

template <typename T, bool circular>
void list_test_islist() {
  ISList<T> list;

  T* link1 = new T(1);
  T* link2 = new T(2);
  T* link3 = new T(3);

  list.append(*link1);
  list.append(*link2);
  list.append(*link3);

  ForwardListIterator<ISList<T>, T> it = list.begin();

  for(int i = 0; it != list.end(); ++it, i++) {
    cout << "list["<<i<<"]="<<*((*it)->get_info()) << endl;
  }

  cout << "List Size:" << list.get_size() << endl;

  delete_slist<_SLink<circular> >(list.get_head(), list.get_tail());
}

template <typename T, bool circular>
void list_test_slist() {
  SList<T> list;

  T* link1 = new T(1);
  T* link2 = new T(2);
  T* link3 = new T(3);
  T* link4 = new T(4);
  T* link5 = new T(5);
  T* link6 = new T(6);

  list.insert(*link4);
  list.append(*link1);
  list.append(*link2);
  list.append(*link3);
  list.insert(*link5);
  list.insert(*link6, 4);

  //print_list<typename SList<T>::AnchorType,
  //           circular>((typename SList<T>::AnchorType *)list.get_head());
  ForwardListIterator<SList<T>, typename SList<T>::AnchorType> it = list.begin();

  for(int i = 0; it != list.end(); ++it, i++) {
    cout << "list["<<i<<"]="<<*(*it)->get_info()->get_info() << endl;
  }

  cout << "List Size:" << list.get_size() << endl;

  delete_slist<_SLink<circular> >(list.get_head(), list.get_tail());

  delete link1;
  delete link2;
  delete link3;
  delete link4;
  delete link5;
  delete link6;
}

int list_test_main (int argc, char **argv) {
  cout << "**Test SLink : " << endl;
  list_test_slink<TestSLink>();

  cout << "**Test TLink(SLink) : " << endl;
  list_test_slink<TLink<int, SLink>, false>();

  cout << "**Test SLink Circular : " << endl;
  list_test_slink<TestSLinkCircular, true>();

  cout << "**Test TLink(SLink) Circular : " << endl;
  list_test_slink<TLink<int, CSLink >, true>();

  cout << "**Test DLink : " << endl;
  list_test_dlink<TestDLink>();

  cout << "**Test TLink(DLink) : " << endl;
  list_test_dlink<TLink<int, DLink > >();

  cout << "**Test DLink Circular : " << endl;
  list_test_dlink<TestDLinkCircular, true>();

  cout << "**Test TLink(DLink) Circular : " << endl;
  list_test_dlink<TLink<int, CDLink >, true>();
 
  cout << "**Test ListBase : " << endl;
  list_test_listbase< TLink<int, SLink>, SLink, false>();
  
  cout << "**Test ISList : " << endl;
  list_test_islist<TestSLink, false>();

  cout << "**Test SList : " << endl;
  list_test_slist<TestObject, false>();

  cout << "**Test IDList : " << endl;
  list_test_islist<TestSLink, false>();

  cout << "**Test DList : " << endl;
  list_test_slist<TestObject, false>();

  default_random_engine generator;
  uniform_int_distribution<unsigned> distribution;

  for(int i = 0; i < 5; i++) {
    cout << distribution(generator) << endl;
  }
  
  Hash<int, int>* h = new Hash<int, int>(10);

  h->put(5, 5);

  cout << h->get(5) << endl;

  delete h;

  return 0;
}
