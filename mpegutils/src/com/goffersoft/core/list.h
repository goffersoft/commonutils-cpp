#ifndef __LIST__H__
#define __LIST__H__


struct slink {
    private :
        slink* next;

    public :
        slink():next(0){}
        slink* get_next() { return next;}
        void set_next(slink* s) {next=s;}
};

template<class T>
struct tlink : public slink {
    private :
        T info;
    
    public :
        tlink(T i):info(i) {} 
        inline T& get_info() { return info; }
        inline void set_info(T& i) { info = i; }
};

class slist_base {
    private:
        slink* first;
        slink* last;

    public:
        slist_base(): first(0), last(0) {}
        inline void append(slink* s);
        inline void insert(slink* s, slink* prev);
        inline void insert(slink* s, int i = 0);
        inline void remove(slink* s, slink* prev);
        inline void remove(int i = 0);
        inline slink* get(int i = 0, bool del = true);
        inline slink* get_first() { return first; }
        inline slink* get_last() { return last; }
};

void
slist_base::
append(slink* s) {
    s->set_next(0);
    if(last) {
        last->set_next(s);
        last = s;
    } else {
        last = first = s;
    }
}

void
slist_base::
insert(slink* s, int i) {
    if(i == 0) {
        insert(0, s);
        return;
    }
    slink* prev = get(i-1, false);
    if(prev == 0) {
        append(s);
    } else {
        insert(prev, s);
    }
}


void
slist_base::
insert(slink* prev, slink* s) {
    if(prev) {
        s->set_next(prev->get_next());
        prev->set_next(s);
        if(last == prev) {
            last = s;
        }
    } else if(first) {
        s->set_next(first);
        first = s;
    } else {
        s->set_next(0);
        first = last = s;
    }
}
 

void
slist_base::
remove(int i) {
    get(i);
}


void
slist_base::
remove(slink* prev, slink* s) {
    if(prev) {
        prev->set_next(s->get_next());
        if(last == s) {
            last = prev;
        }
    } else if(first == s) {
        first = first->get_next();
    }
}

slink*
slist_base::
get(int i, bool del) {
    slink* prev = 0;
    slink* s = get_first();

    for(int j = 0; s; s = s->get_next(), j++) {
       if(j == i)
           break;
       prev = s;
    }
    if(del == true && s!= 0) {
         remove(prev, s);
    }
    return s;
}

template<class T>
class islist : public slist_base {
    private :
        

    public :
        islist():slist_base(){}
        inline T* get(int i = 0, bool del = true);
        inline void remove(int i = 0);
        inline void append(T& a);
        inline void insert(T& a, int i = 0);
};

template<class T>
T*
islist<T>::get(int i, bool del) {
    return (T*)(slist_base::get(i, del));
}

template<class T>
void
islist<T>::remove(int i) {
    slist_base::remove(i);
}

template<class T>
void
islist<T>::insert(T& a, int i) {
    slist_base::insert(&a, i);
}

template<class T>
void
islist<T>::append(T& a) {
    slist_base::append(&a);
}

template<class T>
class slist : public slist_base {
    private :

    public :
        slist():slist_base(){}
        inline T* get(int i = 0, bool del = true);
        inline void remove(int i = 0);
        inline void append(T& a);
        inline void insert(T& a, int i = 0);
};

template<class T>
T*
slist<T>::get(int i, bool del) {
    tlink<T>* t = (tlink<T>*)slist_base::get(i, del);
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

template<class T>
void
slist<T>::remove(int i) {
    tlink<T>* t = (tlink<T>*)slist_base::get(i, true);
   
    if(t) { 
        delete t;
    } 
}

template<class T>
void
slist<T>::append(T& a) {
    slist_base::append(new tlink<T>(a));
}

template<class T>
void
slist<T>::insert(T& a, int i) {
    slist_base::insert(new tlink<T>(a), i);
}


#endif /* __LIST_H__ */
