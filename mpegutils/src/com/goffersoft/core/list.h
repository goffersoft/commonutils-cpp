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

struct slink;
struct dlink;

struct slink {
    private :
        slink* next;

    public :
        slink(slink* n = nullptr):next(n){}
        slink(const slink& s):next(s.get_next()){}
        slink* get_next() const { return (slink*)next;}
        void set_next(slink* s) {next=s;}
        inline operator dlink() const;
};
 
struct dlink {
    private :
        dlink* next;
        dlink* prev;

    public :
        dlink(dlink* n = nullptr,
              dlink* p = nullptr):next(n), prev(p){}
        dlink(const dlink& d):next(d.get_next()),
                              prev(d.get_prev()){}
        dlink* get_next() const { return (dlink*)next;}
        dlink* get_prev() const { return (dlink*)prev;}
        void set_next(dlink* s) {next=s;}
        void set_prev(dlink* s) {prev=s;}
        inline operator slink() const;
};

template<class T, class S = slink>
struct tlink : public S {
    private :
        T info;

    public :
        tlink(T i):info(i) {} 
        inline T& get_info() { return info; }
        inline void set_info(T& i) { info = i; }
};

template<class T>
class list_base {
    private:
        T* first;
        T* last;

    public:
        list_base(): first(nullptr), last(nullptr) {}
        inline T* get_first() { return first; }
        inline T* get_last() { return last; }
        inline void set_first(T* f) { first = f; }
        inline void set_last(T* l) { last = l; }
};

class slist_base : public list_base<slink> {
    public:
        slist_base(): list_base() {}
        inline void append(slink* s);
        inline void insert(slink* s, slink* prev);
        inline void insert(slink* s, int i = 0);
        inline void remove(slink* s, slink* prev = nullptr);
        inline slink* remove(int i = 0);
        inline slink* get(int i = 0, bool del = true);
};

class circular_slist_base : public list_base<slink> {
    public:
        circular_slist_base(): list_base() {}
        inline void append(slink* s);
        inline void insert(slink* s, slink* prev);
        inline void insert(slink* s, int i = 0);
        inline void remove(slink* s, slink* prev = nullptr);
        inline slink* remove(int i = 0);
        inline slink* get(int i = 0, bool del = true);
};

template<class T, class S = slist_base>
class islist : public S {
    public :
        islist():S(){}
        inline T* get(int i = 0, bool del = true);
        inline T* remove(int i = 0);
        inline void append(T& a);
        inline void insert(T& a, int i = 0);
};

template<class T, class S = slist_base>
class slist : public S {
    public :
        slist():S(){}
        inline T* get(int i = 0, bool del = true);
        inline T* remove(int i = 0);
        inline void append(T& a);
        inline void insert(T& a, int i = 0);
};

template<class T>
class circular_islist : public islist<T, circular_slist_base> {
};

template<class T>
class circular_slist : public slist<T, circular_slist_base> {
};

class dlist_base : public list_base<dlink> {
    public:
        dlist_base(): list_base() {}
        inline void append(dlink* s);
        inline void insert(dlink* s, dlink* prev = nullptr);
        inline void insert(dlink* s, int i = 0);
        inline void remove(dlink* s);
        inline dlink* remove(int i = 0);
        inline dlink* get(int i = 0, bool del = true);
};

class circular_dlist_base : public list_base<dlink> {
    public:
        circular_dlist_base(): list_base() {}
        inline void append(dlink* s);
        inline void insert(dlink* s, dlink* prev = nullptr);
        inline void insert(dlink* s, int i = 0);
        inline void remove(dlink* s);
        inline dlink* remove(int i = 0);
        inline dlink* get(int i = 0, bool del = true);
};

template<class T, class S = dlist_base>
class idlist : public S {
    public :
        idlist():S(){}
        inline T* get(int i = 0, bool del = true);
        inline T* remove(int i = 0);
        inline void append(T& a);
        inline void insert(T& a, int i = 0);
};

template<class T, class S = dlist_base>
class dlist : public S {
    public :
        dlist():S(){}
        inline T* get(int i = 0, bool del = true);
        inline T* remove(int i = 0);
        inline void append(T& a);
        inline void insert(T& a, int i = 0);
};

//slink
slink::
operator
dlink() const {
    return dlink((dlink*)next, nullptr);
}

//dlink
dlink::
operator
slink() const {
    return slink((slink*)next);
}

//slist_base
void
slist_base::
append(slink* s) {
    if(s == nullptr) {
        return;
    }
    s->set_next(nullptr);

    if(get_last()) {
        get_last()->set_next(s);
        set_last(s);
    } else {
        set_first(s);
        set_last(s);
    }
}

void
slist_base::
insert(slink* s, int i) {
    if(i <= 0) {
        insert(s, nullptr);
        return;
    }
    slink* prev = get(i-1, false);
    if(prev == nullptr) {
        append(s);
    } else {
        insert(s, prev);
    }
}

void
slist_base::
insert(slink* s, slink* prev) {
    if(prev) {
        s->set_next(prev->get_next());
        prev->set_next(s);
        if(get_last() == prev) {
            set_last(s);
        }
    } else if(get_first()) {
        s->set_next(get_first());
        set_first(s);
    } else {
        set_first(s);
        set_last(s);
    }
}
 
slink* 
slist_base::
remove(int i) {
    return get(i);
}

void
slist_base::
remove(slink* s, slink* prev) {
    if(prev) {
        if(prev->get_next() == s) {
            prev->set_next(s->get_next());
            if(get_last() == s) {
                set_last(prev);
            }
        }
    } else if(get_first() == s) {
        set_first(get_first()->get_next());
        if(get_first() == nullptr)
            set_last(nullptr);
    }
}

slink*
slist_base::
get(int i, bool del) {
    slink* prev = nullptr;
    slink* s = get_first();

    for(int j = 0; s; s = s->get_next(), j++) {
       if(j == i)
           break;
       prev = s;
    }
    if(del == true && s!= 0) {
         remove(s, prev);
    }
    return s;
}


//circular_slist_base
void
circular_slist_base::
append(slink* s) {
    if(s == nullptr) {
        return;
    }
    if(get_last()) {
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
circular_slist_base::
insert(slink* s, int i) {
    if(i <= 0) {
        insert(s, nullptr);
        return;
    }
    slink* prev = get(i-1, false);
    if(prev == nullptr) {
        append(s);
    } else {
        insert(s, prev);
    }
}


void
circular_slist_base::
insert(slink* s, slink* prev) {
    if(prev) {
        s->set_next(prev->get_next());
        prev->set_next(s);
        if(get_last() == prev) {
            set_last(s);
        }
    } else if(get_first()) {
        s->set_next(get_first());
        set_first(s);
        get_last()->set_next(s);
    } else {
        set_first(s);
        set_last(s);
        s->set_next(s);
    }
}
 
slink*
circular_slist_base::
remove(int i) {
    return get(i);
}

void
circular_slist_base::
remove(slink* s, slink* prev) {
    if(prev) {
        if(prev->get_next() == s) {
            prev->set_next(s->get_next());
            if(get_last() == s) {
                set_last(prev);
            }
        }
    } else if(get_first() == s) {
        if(get_first() == get_last()) {
            set_first(nullptr);
            set_last(nullptr);
        } else {
            set_first(get_first()->get_next());
            get_last()->set_next(get_first());
        }
    }
}

slink*
circular_slist_base::
get(int i, bool del) {
    slink* prev = nullptr;
    slink* s = get_first();
    int j = 0;

    while (s != get_last()) {
        if(j == i)
            break;
        prev = s;
        s = s->get_next();
        j++;
   }
   if(del == true && s!= 0) {
       remove(s, prev);
   }
   return s;
}


//islist
template<class T, class S>
T*
islist<T, S>::get(int i, bool del) {
    return (T*)(S::get(i, del));
}

template<class T, class S>
T*
islist<T, S>::remove(int i) {
    return (T*)(S::remove(i));
}

template<class T, class S>
void
islist<T, S>::insert(T& a, int i) {
    S::insert(&a, i);
}

template<class T, class S>
void
islist<T, S>::append(T& a) {
    S::append(&a);
}

//slist
template<class T, class S>
T*
slist<T, S>::get(int i, bool del) {
    tlink<T>* t = (tlink<T>*)S::get(i, del);
    T *val;
    if(t) {
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
slist<T, S>::remove(int i) {
    tlink<T>* t = (tlink<T>*)(S::remove(i));
    T *val = nullptr;

    if(t) {
        val = &t->get_info();
        delete t;
    }
    return val;
}

template<class T, class S>
void
slist<T, S>::append(T& a) {
    S::append(new tlink<T>(a));
}

template<class T, class S>
void
slist<T, S>::insert(T& a, int i) {
    S::insert(new tlink<T>(a), i);
}


//dlist_base
void
dlist_base::
append(dlink* d) {
    if(get_last()) {
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
dlist_base::
insert(dlink* d, int i) {
    if(i == 0) {
        insert(d, nullptr);
        return;
    }
    dlink* prev = get(i-1, false);
    if(prev == nullptr) {
        append(d);
    } else {
        insert(d, prev);
    }
}

void
dlist_base::
insert(dlink* d, dlink* prev) {
    if(prev) {
        d->set_next(prev->get_next());
        d->set_prev(prev);
        if(prev->get_next()) {
            prev->get_next()->set_prev(d);
        }
        prev->set_next(d);
        if(get_last() == prev) {
            set_last(d);
        }
    } else if(get_first()) {
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

dlink*
dlist_base::
remove(int i) {
    return get(i);
}

void
dlist_base::
remove(dlink* l) {
}

dlink*
dlist_base::
get(int i, bool del) {
    dlink* d = get_first();

    for(int j = 0; d; d = d->get_next(), j++) {
       if(j == i)
           break;
    }
    if(del == true && d != 0) {
         remove(d);
    }
    return d;
}

//circular_dlist_base
void
circular_dlist_base::
append(dlink* d) {
    if(get_last()) {
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
circular_dlist_base::
insert(dlink* d, int i) {
    if(i <= 0) {
        insert(d, nullptr);
        return;
    }

    dlink* prev = get(i-1, false);

    if(prev == nullptr) {
        append(d);
    } else {
        insert(d, prev);
    }
}

void
circular_dlist_base::
insert(dlink* d, dlink* prev) {
    if(prev) {
        d->set_next(prev->get_next());
        d->set_prev(prev);
        prev->get_next()->set_prev(d);
        prev->set_next(d);
        if(get_last() == prev) {
            set_last(d);
        }
    } else if(get_first()) {
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

dlink*
circular_dlist_base::
remove(int i) {
    return get(i);
}

void
circular_dlist_base::
remove(dlink* d) {
    if (get_first() == get_last()) {
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

dlink*
circular_dlist_base::
get(int i, bool del) {
    dlink* d = get_first();
    int j =  0;

    while(d != get_last()) {
       if(j == i)
           break;
       d = d->get_next();
       j++;
    }
    if(del == true && d != nullptr) {
         remove(d);
    }
    return d;
}

//idlist
template<class T, class S>
T*
idlist<T, S>::get(int i, bool del) {
    return (T*)(S::get(i, del));
}

template<class T, class S>
T*
idlist<T, S>::remove(int i) {
    return S::remove(i);
}

template<class T, class S>
void
idlist<T, S>::insert(T& a, int i) {
    S::insert(&a, i);
}

template<class T, class S>
void
idlist<T, S>::append(T& a) {
    S::append(&a);
}

//dlist
template<class T, class S>
T*
dlist<T, S>::get(int i, bool del) {
    tlink<T, dlink>* t = (tlink<T, dlink>*)S::get(i, del);
    T *val;

    if(t) {
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
dlist<T, S>::remove(int i) {
    tlink<T, dlink>* t = (tlink<T, dlink>*)S::remove(i);
    T *val = nullptr;

    if(t) {
        val = &t->get_info();
        delete t;
    }
    return val;
}

template<class T, class S>
void
dlist<T, S>::append(T& a) {
    S::append(new tlink<T, dlink>(a));
}

template<class T, class S>
void
dlist<T, S>::insert(T& a, int i) {
    S::insert(new tlink<T, dlink>(a), i);
}

#endif /* __LIST_H__ */
