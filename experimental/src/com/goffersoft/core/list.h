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
 ** This class contains code to manipulate lists.
 **/
#ifndef __LIST__H__
#define __LIST__H__

namespace com {
namespace goffersoft {
namespace core {

struct SLink;
struct DLink;

struct SLink {
  private :
    SLink* next;

  public :
    SLink(SLink* n = nullptr):next(n){}
    SLink(const SLink& s):next(s.get_next()){}
    SLink* get_next() const { return (SLink*)next;}
    void set_next(SLink* s) {next=s;}
    inline operator DLink() const;
};
 
struct DLink {
  private :
    DLink* next;
    DLink* prev;

  public :
    DLink(DLink* n = nullptr,
          DLink* p = nullptr):next(n), prev(p){}
    DLink(const DLink& d):next(d.get_next()),
                          prev(d.get_prev()){}
    DLink* get_next() const { return (DLink*)next;}
    DLink* get_prev() const { return (DLink*)prev;}
    void set_next(DLink* s) {next=s;}
    void set_prev(DLink* s) {prev=s;}
    inline operator SLink() const;
};

template<class T, class S = SLink>
struct TLink : public S {
  private :
    T info;

  public :
    TLink(T i):info(i) {} 
    inline T& get_info() { return info; }
    inline void set_info(T& i) { info = i; }
};

template<class T>
class ListBase {
  private:
    T* first;
    T* last;
    unsigned size;

  protected:
    inline void set_size(unsigned sz) { size = sz; }
    inline void incr_size() { size++; }
    inline void decr_size() { size--; }

  public:
    ListBase(): first(nullptr), last(nullptr) {}
    inline T* get_first() const { return first; }
    inline T* get_last() const { return last; }
    inline void set_first(T* f) { first = f; }
    inline void set_last(T* l) { last = l; }
    inline unsigned get_size() const { return size; }
};

class SListBase : public ListBase<SLink> {
  public:
    SListBase(): ListBase() {}
    inline void append(SLink* s);
    inline void insert(SLink* s, SLink* prev);
    inline void insert(SLink* s, int i = 0);
    inline void remove(SLink* s, SLink* prev = nullptr);
    inline SLink* remove(int i = 0);
    inline SLink* get(int i = 0, bool del = true);
};

class CircularSListBase : public ListBase<SLink> {
  public:
    CircularSListBase(): ListBase() {}
    inline void append(SLink* s);
    inline void insert(SLink* s, SLink* prev);
    inline void insert(SLink* s, int i = 0);
    inline void remove(SLink* s, SLink* prev = nullptr);
    inline SLink* remove(int i = 0);
    inline SLink* get(int i = 0, bool del = true);
};

template<class T, class S = SListBase>
class ISList : public S {
  public :
    ISList():S(){}
    inline T* get(int i = 0, bool del = true);
    inline T* remove(int i = 0);
    inline void append(T& a);
    inline void insert(T& a, int i = 0);
};

template<class T, class S = SListBase>
class SList: public S {
  public :
    SList():S(){}
    inline T* get(int i = 0, bool del = true);
    inline T* remove(int i = 0);
    inline void append(T& a);
    inline void insert(T& a, int i = 0);
};

template<class T>
class CircularISList : public ISList<T, CircularSListBase> {
};

template<class T>
class CircularSList : public SList<T, CircularSListBase> {
};

class DListBase : public ListBase<DLink> {
  public:
    DListBase(): ListBase() {}
    inline void append(DLink* s);
    inline void insert(DLink* s, DLink* prev = nullptr);
    inline void insert(DLink* s, int i = 0);
    inline void remove(DLink* s);
    inline DLink* remove(int i = 0);
    inline DLink* get(int i = 0, bool del = true);
};

class CircularDListBase : public ListBase<DLink> {
  public:
    CircularDListBase(): ListBase() {}
    inline void append(DLink* s);
    inline void insert(DLink* s, DLink* prev = nullptr);
    inline void insert(DLink* s, int i = 0);
    inline void remove(DLink* s);
    inline DLink* remove(int i = 0);
    inline DLink* get(int i = 0, bool del = true);
};

template<class T, class S = DListBase>
class IDList : public S {
  public :
    IDList():S(){}
    inline T* get(int i = 0, bool del = true);
    inline T* remove(int i = 0);
    inline void append(T& a);
    inline void insert(T& a, int i = 0);
};

template<class T, class S = DListBase>
class DList : public S {
  public :
    DList():S(){}
    inline T* get(int i = 0, bool del = true);
    inline T* remove(int i = 0);
    inline void append(T& a);
    inline void insert(T& a, int i = 0);
};

//SLink
SLink::
operator
DLink() const {
  return DLink((DLink*)next, nullptr);
}

//DLink
DLink::
operator
SLink() const {
  return SLink((SLink*)next);
}

//SListBase
void
SListBase::
append(SLink* s) {
  if (s == nullptr) {
    return;
  }
  s->set_next(nullptr);

  if (get_last()) {
    get_last()->set_next(s);
    set_last(s);
  } else {
    set_first(s);
    set_last(s);
  }
}

void
SListBase::
insert(SLink* s, int i) {
  if (i <= 0) {
    insert(s, nullptr);
    return;
  }
  SLink* prev = get(i-1, false);
  if (prev == nullptr) {
    append(s);
  } else {
    insert(s, prev);
  }
}

void
SListBase::
insert(SLink* s, SLink* prev) {
  if (prev) {
    s->set_next(prev->get_next());
    prev->set_next(s);
    if(get_last() == prev) {
        set_last(s);
    }
  } else if (get_first()) {
    s->set_next(get_first());
    set_first(s);
  } else {
    set_first(s);
    set_last(s);
  }
}
 
SLink* 
SListBase::
remove(int i) {
  return get(i);
}

void
SListBase::
remove(SLink* s, SLink* prev) {
  if (prev && (prev->get_next() == s)) {
    prev->set_next(s->get_next());
    if(get_last() == s) {
      set_last(prev);
    }
  } else if (get_first() == s) {
    set_first(get_first()->get_next());
    if(get_first() == nullptr)
      set_last(nullptr);
  }
}

SLink*
SListBase::
get(int i, bool del) {
  SLink* prev = nullptr;
  SLink* s = get_first();

  for (int j = 0; s; s = s->get_next(), j++) {
    if (j == i)
      break;
       prev = s;
  }
  if (del == true && s!= 0) {
    remove(s, prev);
  }
  return s;
}


//CircularSListBase
void
CircularSListBase::
append(SLink* s) {
  if (s == nullptr) {
    return;
  }
  if (get_last()) {
    get_last()->set_next(s);
    s->set_next(get_first());
    set_last(s);
  } else {
    s->set_next(s);
    set_first(s);
    set_last(s);
  }
}

void
CircularSListBase::
insert(SLink* s, int i) {
  if (i <= 0) {
    insert(s, nullptr);
    return;
  }
  SLink* prev = get(i-1, false);
  if (prev == nullptr) {
    append(s);
  } else {
    insert(s, prev);
  }
}


void
CircularSListBase::
insert(SLink* s, SLink* prev) {
  if (prev) {
    s->set_next(prev->get_next());
    prev->set_next(s);
    if(get_last() == prev) {
      set_last(s);
    }
  } else if (get_first()) {
    s->set_next(get_first());
    set_first(s);
    get_last()->set_next(s);
  } else {
    set_first(s);
    set_last(s);
    s->set_next(s);
  }
}
 
SLink*
CircularSListBase::
remove(int i) {
  return get(i);
}

void
CircularSListBase::
remove(SLink* s, SLink* prev) {
  if (prev && (prev->get_next() == s)) {
    prev->set_next(s->get_next());
    if (get_last() == s) {
      set_last(prev);
    }
  } else if (get_first() == s) {
    if (get_first() == get_last()) {
      set_first(nullptr);
      set_last(nullptr);
    } else {
      set_first(get_first()->get_next());
      get_last()->set_next(get_first());
    }
  }
}

SLink*
CircularSListBase::
get(int i, bool del) {
  SLink* prev = nullptr;
  SLink* s = get_first();
  int j = 0;

  while (s != get_last()) {
    if (j == i)
      break;
    prev = s;
    s = s->get_next();
    j++;
  }
  if (del == true && s!= 0) {
    remove(s, prev);
  }
  return s;
}


//ISList
template<class T, class S>
T*
ISList<T, S>::get(int i, bool del) {
  return (T*)(S::get(i, del));
}

template<class T, class S>
T*
ISList<T, S>::remove(int i) {
  return (T*)(S::remove(i));
}

template<class T, class S>
void
ISList<T, S>::insert(T& a, int i) {
  S::insert(&a, i);
}

template<class T, class S>
void
ISList<T, S>::append(T& a) {
  S::append(&a);
}

//SList
template<class T, class S>
T*
SList<T, S>::get(int i, bool del) {
  TLink<T>* t = (TLink<T>*)S::get(i, del);
  T *val;
  if (t) {
    val = &t->get_info();
    if(del == true) {
      delete t;
    }
  } else {
    val = 0;
  }
  return val;
}

template<class T, class S>
T*
SList<T, S>::remove(int i) {
  TLink<T>* t = (TLink<T>*)(S::remove(i));
  T *val = nullptr;

  if(t) {
    val = &t->get_info();
    delete t;
  }
  return val;
}

template<class T, class S>
void
SList<T, S>::append(T& a) {
  S::append(new TLink<T>(a));
}

template<class T, class S>
void
SList<T, S>::insert(T& a, int i) {
  S::insert(new TLink<T>(a), i);
}


//DListBase
void
DListBase::
append(DLink* d) {
  if (get_last()) {
    get_last()->set_next(d);
    d->set_prev(get_last());
    set_last(d);
  } else {
    set_first(d);
    set_last(d);
    d->set_prev(nullptr);
  }
  d->set_next(nullptr);
}

void
DListBase::
insert(DLink* d, int i) {
  if (i == 0) {
    insert(d, nullptr);
    return;
  }
  DLink* prev = get(i-1, false);
  if (prev == nullptr) {
    append(d);
  } else {
    insert(d, prev);
  }
}

void
DListBase::
insert(DLink* d, DLink* prev) {
  if (prev) {
    d->set_next(prev->get_next());
    d->set_prev(prev);
    if (prev->get_next()) {
      prev->get_next()->set_prev(d);
    }
    prev->set_next(d);
    if (get_last() == prev) {
      set_last(d);
    }
  } else if (get_first()) {
    d->set_next(get_first());
    d->set_prev(nullptr);
    set_first(d);
  } else {
    d->set_next(nullptr);
    d->set_prev(nullptr);
    set_first(d);
    set_last(d);
  }
}

DLink*
DListBase::
remove(int i) {
  return get(i);
}

void
DListBase::
remove(DLink* l) {
  if ((l == get_first()) &&
      (l == get_last())) {
    set_first(nullptr);
    set_last(nullptr);
  } else if (l == get_first()) {
    l->get_next()->set_prev(nullptr);
    set_first(l->get_next());
  } else if (l == get_last()) {
    l->get_prev()->set_next(nullptr);
    set_last(l->get_prev());
  } else {
    l->get_prev()->set_next(l->get_next());
    l->get_next()->set_prev(l->get_prev());
  }
}

DLink*
DListBase::
get(int i, bool del) {
  DLink* d = get_first();

  for (int j = 0; d; d = d->get_next(), j++) {
    if (j == i)
      break;
  }
  if (del == true && d != 0) {
     remove(d);
  }
  return d;
}

//CircularDListBase
void
CircularDListBase::
append(DLink* d) {
  if (get_last()) {
    get_last()->set_next(d);
    d->set_next(get_first());
    d->set_prev(get_last());
    set_last(d);
  } else {
    set_first(d);
    set_last(d);
    d->set_next(d);
    d->set_prev(d);
  }
}

void
CircularDListBase::
insert(DLink* d, int i) {
  if (i <= 0) {
    insert(d, nullptr);
    return;
  }

  DLink* prev = get(i-1, false);

  if (prev == nullptr) {
    append(d);
  } else {
    insert(d, prev);
  }
}

void
CircularDListBase::
insert(DLink* d, DLink* prev) {
  if (prev) {
    d->set_next(prev->get_next());
    d->set_prev(prev);
    prev->get_next()->set_prev(d);
    prev->set_next(d);
    if (get_last() == prev) {
      set_last(d);
    }
  } else if (get_first()) {
    d->set_next(get_first());
    d->set_prev(get_last());
    get_last()->set_next(d);
    get_first()->set_prev(d);
    set_first(d);
  } else {
    d->set_next(d);
    d->set_prev(d);
    set_first(d);
    set_last(d);
  }
}

DLink*
CircularDListBase::
remove(int i) {
  return get(i);
}

void
CircularDListBase::
remove(DLink* d) {
  if ((d == get_first()) &&
      (d == get_last())) {
    set_first(nullptr);
    set_last(nullptr);
  } else if(d == get_first()) {
    set_first(d->get_next());
    get_first()->set_prev(get_last());
  } else if(d == get_last()) {
    set_last(d->get_prev());
    get_last()->set_next(get_first());
  } else {
    d->get_prev()->set_next(d->get_next());
    d->get_next()->set_prev(d->get_prev());
  }
}

DLink*
CircularDListBase::
get(int i, bool del) {
  DLink* d = get_first();
  int j =  0;

  while(d != get_last()) {
   if (j == i)
     break;
     d = d->get_next();
     j++;
  }
  if (del == true && d != nullptr) {
     remove(d);
  }
  return d;
}

//IDList
template<class T, class S>
T*
IDList<T, S>::get(int i, bool del) {
  return (T*)(S::get(i, del));
}

template<class T, class S>
T*
IDList<T, S>::remove(int i) {
  return S::remove(i);
}

template<class T, class S>
void
IDList<T, S>::insert(T& a, int i) {
  S::insert(&a, i);
}

template<class T, class S>
void
IDList<T, S>::append(T& a) {
  S::append(&a);
}

//DList
template<class T, class S>
T*
DList<T, S>::get(int i, bool del) {
  TLink<T, DLink>* t = (TLink<T, DLink>*)S::get(i, del);
  T *val;

  if (t) {
    val = &t->get_info();
    if (del == true) {
        delete t;
    }
  } else {
    val = 0;
  }
  return val;
}

template<class T, class S>
T*
DList<T, S>::remove(int i) {
  TLink<T, DLink>* t = (TLink<T, DLink>*)S::remove(i);
  T *val = nullptr;

  if (t) {
    val = &t->get_info();
    delete t;
  }
  return val;
}

template<class T, class S>
void
DList<T, S>::append(T& a) {
  S::append(new TLink<T, DLink>(a));
}

template<class T, class S>
void
DList<T, S>::insert(T& a, int i) {
  S::insert(new TLink<T, DLink>(a), i);
}

} /* com */
} /* goffersoft */
} /* core */

#endif /* __LIST_H__ */
