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
 ** This class contains code to manipulate lists. The core design is
 ** is taken from stroutrups book on c++. Care has been taken not to add 
 ** virtual functions. Hnece some duplication of code among the classes.
 ** Hence these classes shouldnot have any hidden variables injected by
 ** the compiler (except the "this" variable). and all function bindings
 ** are determined at compile time.
 **
 ** list structures and calsses :
 ** 1) base singly linked list class(circular lists vs non-circular lists) 
 **      template<bool circular> struct _SLink;
 **
 ** 2) base doubly linked list class(circular lists vs non-circular lists) 
 **      template<bool circular> struct _DLink;
 **
 ** 3) some helper typedef for the above classes
 **      a) single linked list node
 **           typedef _SLink<false> SLink
 **
 **      b) circular singly linked list node
 **           typedef _SLink<true> CSLink
 **
 **      c) doubly linked list node
 **           typedef _DLink<false> DLink
 **
 **      d) circular doubly linked list node
 **           typedef _DLink<true> CDLink
 **
 ** 4) 1,2, and 3 above support the concept of intrinsic linked lists
 **     where the custom object to be linked is dervied from one
 **     of the above classes.    
 **
 ** 5) Generic TLink structure to facililate creating intrinsic linked lists.
 **      template<typename T, typename S> struct TLink;
 **      S: should be set to the link structures listed in 1,2 or 3 above
 **
 ** 6) List Base Classes
 **      a) Generic List Base Class
 **           template<typename T> class ListBase
 **
 **      b) Singly Linked List Base Class
 **           class SListBase
 **
 **      c) Circular Singly Linked List Base Class
 **           class CircularSListBase
 **
 **      d) Doubly Linked List Base Class
 **           class DListBase
 **
 **      e) Circular Doubly Linked List Base Class
 **           class CircularDListBase
 **
 ** 7) Intrinsic Singly Linked List
 **      template<typename T,
 **               typename S = SListBase> class ISList
 **
 ** 8) Intrinsic Circular Singly Linked List
 **      template<typename T> class CircularISList
 **
 ** 9) Non-Intrinsic Singly Linked List
 **      template<typename T,
 **               typename S = SListBase,
 **               bool circular = false> class SList
 **
 ** 10) Non-Intrinsic Circular Singly Linked List
 **      template<typename T> class CircularSList
 **
 ** 7) Intrinsic Doubly Linked List
 **      template<typename T,
 **               typename S = DListBase> class IDList
 **
 ** 8) Intrinsic Circular Doubly Linked List
 **      template<typename T> class CircularIDList
 **
 ** 9) Non-Intrinsic Doubly Linked List
 **      template<typename T,
 **               typename S = DListBase,
 **               bool circular = false> class DList
 **
 ** 10) Non-Intrinsic Circular Doubly Linked List
 **      template<typename T> class CircularDList
 **
 ** 11) List Iterators - all list iterators are exposed via
 **     public methods in the various List classes. Singly 
 **     linked list classes only support the ForwardIterator
 **     class. Doubly Linked Lists support all iterator
 **     classes. By default type A is equal to T::NodeType.
 **     Sometimes it is reuqired by nodetype to mimic target
 **     NodeType so that the operator *
 **     return the appropriate type.
 **     a) Genric List iterator base class
 **          template <typename T, typename A> class ListIterator
 **
 **     b) Forward List iterator base class - traverses a list
 **        from start to end.
 **          template <typename T, typename A> class ForwardListIterator
 **
 **     c) Reverse List iterator base class - traverses a list
 **        from end to start.
 **          template <typename T, typename A> class ReverseListIterator
 **
 **     d) Bidirectional List iterator base class - traverses a list
 **        in both directions.
 **          template <typename T, typename A> class BidirectionalListIterator
 **
 **/
#ifndef __LIST__H__
#define __LIST__H__

namespace com {
namespace goffersoft {
namespace core {

template<bool circular>
struct _SLink;

template<bool circular>
struct _DLink;

template<bool circular>
struct _SLink {
  private :
    _SLink* next;

  public :
    _SLink() {reset();}

    _SLink(const _SLink& s):next(s.get_next()){}
    
    _SLink(_SLink* s):next(s){}

    _SLink* get_next() const { return next;}

    void set_next(_SLink* link) {next=link;}

    inline operator _DLink<circular>() const;

    inline void insert(_SLink* link) {
      link->set_next(get_next());
      set_next(link);
    }

    inline _SLink* remove(_SLink* prev) {
      prev->set_next(get_next());
      set_next(nullptr);
      return this;
    }

    void reset() {
      if (circular == false) {
        set_next(nullptr);
      } else {
        set_next(this);
      }
    }

    static _SLink* insert_head(_SLink* head,
                              _SLink* link,
                              _SLink* tail = nullptr) {
      link->set_next(head);

      if (circular == true) {
        tail->set_next(link);
      }

      return link;
    }
    
    static _SLink* remove_head(_SLink* head,
                              _SLink* tail = nullptr) {
      _SLink* link = head->get_next();
     
      if (circular == true) {
        tail->set_next(link);
        if(link == head) {
          link = nullptr;
        }
      }
      
      head->set_next(nullptr);

      return link;
    }
};


typedef _SLink<false> SLink;
typedef _SLink<true> CSLink;
 
template<bool circular>
struct _DLink {
  private :
    _DLink* next;
    _DLink* prev;

  public :
    _DLink() {reset();}

    _DLink(const _DLink& d):next(d.get_next()),
                          prev(d.get_prev()){}
    
    _DLink(const _DLink* n, _DLink* p):next(n), prev(p){}

    _DLink* get_next() const { return next;}

    _DLink* get_prev() const { return prev;}

    void set_next(_DLink* link) {next=link;}

    void set_prev(_DLink* link) {prev=link;}

    inline operator _SLink<circular>() const;

    inline void insert(_DLink* link) {
      link->set_next(get_next());
      link->set_prev(this);
      if (get_next())
        get_next()->set_prev(link);
      set_next(link);
    }

    inline _DLink* remove() {
      if (get_next())
        get_next()->set_prev(get_prev());
      if (get_prev())
        get_prev()->set_next(get_next());
      set_next(nullptr);
      set_prev(nullptr);
      return this;
    }

    void reset() {
      if (circular == false) {
        set_next(nullptr);
        set_prev(nullptr);
      } else {
        set_next(this);
        set_prev(this);
      }
    }

    static _DLink* insert_head(_DLink* head,
                              _DLink* link) {
      link->set_next(head);
      if (circular == true) {
        head->get_prev()->set_next(link);
        link->set_prev(head->get_prev());
      } else {
        link->set_prev(nullptr);
      }
      head->set_prev(link);

      return link;
    }

    static _DLink* remove_head(_DLink* head) {
      _DLink* link = head->get_next();
     
      if (circular == true) {
        head->get_prev()->set_next(link);
        link->set_prev(head->get_prev());
        if(link == head) {
          link = nullptr;
        }
      } else if (link) {
        link->set_prev(nullptr);
      }
      
      head->set_next(nullptr);
      head->set_prev(nullptr);

      return link;
    }
};

typedef _DLink<false> DLink;
typedef _DLink<true> CDLink;

template<typename T, typename S>
struct TLink : public S {
  private :
    T info;

  public :
    TLink(T i):info(i) { }
    inline T* get_info() { return &info; }
    inline void set_info(T& i) { info = i; }
    inline operator T*() { return &info; }
    inline operator T&() { return info; }
};

template<typename T>
class ListBase {
  private:
    T* head;
    T* tail;
    unsigned size;

  public:
    typedef T NodeType;
    ListBase(): head(nullptr), tail(nullptr), size(0) {}
    inline void set_size(unsigned sz) { size = sz; }
    inline void incr_size() { size++; }
    inline void decr_size() { size--; }
    inline void set_head(T* f) { head = f; }
    inline void set_tail(T* l) { tail = l; }
    inline T* get_head() const { return head; }
    inline T* get_tail() const { return tail; }
    inline unsigned get_size() const { return size; }
};

template <typename T, typename A = typename T::NodeType >
class ListIterator {
  protected:
    typedef typename T::NodeType NodeType;
    inline void set_list(const T& l) { list = l; }
    inline void set_node(NodeType* n) { node = n; }
    inline NodeType* get_node() const { return node; }

  private:
    const T& list;
    NodeType* node;

    ListIterator() {}

  protected:
    ListIterator(const T& l): list(l) {}
    ListIterator(const ListIterator<T, A>&  it): 
                             list(it.get_list()),
                             node(it.get_node()) {}

  public :
    inline const T& get_list() const { return list; }

    bool operator ==(const ListIterator<T, A>& rhs) const {
      return ( (&list == &rhs.list) &&
               (node == rhs.node) );
    }

    bool operator !=(const ListIterator<T, A>& rhs) const {
      return ( (&list != &rhs.list) || 
               (node != rhs.node) );
    }

    A* operator *() { return (A*)get_node(); }

    ListIterator<T, A>& operator =(const ListIterator<T, A>& it) {
      set_list(it.get_list());
      set_node(it.get_node());
    }
};

template <typename T, typename A = typename T::NodeType>
class ForwardListIterator : public ListIterator<T, A> {
  private:
    using ListIterator<T, A>::get_node;
    using ListIterator<T, A>::set_node;
    using ListIterator<T, A>::get_list;
    using typename ListIterator<T, A>::NodeType;

    ForwardListIterator() {}

    ForwardListIterator(const T& l, bool end = false):
                                       ListIterator<T, A>(l) {
      if(end)
        set_node(nullptr);
      else
        reset();
    }

  public:
    ForwardListIterator(const ListIterator<T, A>&  it): ListIterator<T, A>(it) {}

    ForwardListIterator<T, A>& operator ++() {
      if(get_node() &&
         get_node()->get_next() != get_list().get_head()) {
        set_node(get_node()->get_next());
      }
      return *this;
    }

    ForwardListIterator<T, A> operator ++(int) {
      ForwardListIterator<T, A> it = ForwardListIterator<T, A>(*this);
      if(get_node() &&
         get_node()->get_next() != get_list().get_head()) {
        set_node(get_node()->get_next());
      }
      return it;
    }

    bool has_next() {
      return ( (get_node() == nullptr ||
                get_node()->get_next() == nullptr ||
                get_node()->get_next() == get_list().get_head()) ? false:true);
    }
    
    void reset() {
      set_node(get_list().get_head());
    }

    static ForwardListIterator<T, A> begin(const T& list) {
      return ForwardListIterator<T, A>(list);
    }
    
    static ForwardListIterator<T, A> end(const T& list) {
      return ForwardListIterator<T, A>(list, true);
    }
};

template <typename T, typename A = typename T::NodeType>
class ReverseListIterator : public ListIterator<T, A> {
  private:
    using ListIterator<T, A>::get_node;
    using ListIterator<T, A>::set_node;
    using ListIterator<T, A>::get_list;

    ReverseListIterator() {}
    ReverseListIterator(const T& l, bool end = false): ListIterator<T, A>(l) {
      if(end)
        set_node(nullptr);
      else
        reset();
    }

  public:
    ReverseListIterator(const ListIterator<T, A>&  it): ListIterator<T, A>(it) {}

    ReverseListIterator<T, A>& operator ++() {
      if(get_node() &&
         get_node()->get_prev() != get_list().get_tail()) {
        set_node(get_node()->get_prev());
      }
      return *this;
    }

    ReverseListIterator<T, A> operator ++(int) {
      ReverseListIterator<T, A> it = ReverseListIterator<T, A>(*this);
      if(get_node() &&
         get_node()->get_prev() != get_list().get_tail()) {
        set_node(get_node()->get_prev());
      }
      return it;
    }

    bool has_prev() {
      return ( (get_node() == nullptr ||
                get_node()->get_prev() == nullptr ||
                get_node()->get_prev() == get_list().get_tail()) ? false:true);
    }

    void reset() {
      set_node(get_list().get_tail());
    }

    static ReverseListIterator<T, A> begin(const T& list) {
      return ReverseListIterator<T, A>(list);
    }
    
    static ReverseListIterator<T, A> end(const T& list) {
      return ReverseListIterator<T, A>(list, true);
    }
};

template <typename T, typename A = typename T::NodeType>
class BidirectionalListIterator : public ListIterator<T, A> {
  private:
    using ListIterator<T, A>::get_node;
    using ListIterator<T, A>::set_node;
    using ListIterator<T, A>::get_list;

    BidirectionalListIterator() {}
    BidirectionalListIterator(const T& l, bool end = false): ListIterator<T, A>(l) {
      if(end)
        set_node(nullptr);
      else
        reset();
    }

  public:
    BidirectionalListIterator(const ListIterator<T, A>&  it): ListIterator<T, A>(it) {}

    BidirectionalListIterator<T, A>& operator ++() {
      if(get_node() &&
         get_node()->get_next() != get_list().get_head()) {
        set_node(get_node()->get_next());
      }
      return *this;
    }

    BidirectionalListIterator<T, A> operator ++(int) {
      BidirectionalListIterator<T, A> it = BidirectionalListIterator<T, A>(*this);
      if(get_node() &&
         get_node()->get_next() != get_list().get_head()) {
        set_node(get_node()->get_next());
      }
      return it;
    }

    BidirectionalListIterator<T, A>& operator --() {
      if(get_node() &&
         get_node()->get_prev() != get_list().get_tail()) {
        set_node(get_node()->get_prev());
      }
      return *this;
    }

    BidirectionalListIterator<T, A> operator --(int) {
      BidirectionalListIterator<T, A> it = BidirectionalListIterator<T, A>(*this);
      if(get_node() &&
         get_node()->get_prev() != get_list().get_tail()) {
        set_node(get_node()->get_prev());
      }
      return it;
    }

    bool has_next() {
      return ( (get_node() == nullptr ||
                get_node()->get_next() == nullptr ||
                get_node()->get_next() == get_list().get_head()) ? false:true);
    }

    bool has_prev () {
      return ( (get_node() == nullptr ||
                get_node()->get_prev() == nullptr ||
                get_node()->get_prev() == get_list().get_tail()) ? false:true);
    }

    void reset(bool head = true) {
      if(head)
        reset_head();
      else
        reset_tail();
    }

    void reset_head() {
      set_node(get_list().get_head());
    }

    void reset_tail() {
      set_node(get_list().get_tail());
    }

    static BidirectionalListIterator<T, A> begin(const T& list) {
      return BidirectionalListIterator<T, A>(list);
    }
    
    static BidirectionalListIterator<T, A> end(const T& list) {
      return BidirectionalListIterator<T, A>(list, true);
    }
};

class SListBase : public ListBase<SLink> {
  public:
    SListBase(): ListBase() {}
    inline SLink* get(int i = 0, bool del = false);
    inline void append(SLink* link);
    inline void insert(SLink* link, SLink* prev);
    inline void insert(SLink* link, int i = 0);
    inline void remove(SLink* link, SLink* prev = nullptr);
    inline SLink* remove(int i = 0);
    inline ForwardListIterator<SListBase> begin() const {
      return ForwardListIterator<SListBase>::begin(*this);
    }
    inline ForwardListIterator<SListBase> end() const {
      return ForwardListIterator<SListBase>::end(*this);
    }
};

class CircularSListBase : public ListBase<CSLink> {
  public:
    CircularSListBase(): ListBase() {}
    inline CSLink* get(int i = 0, bool del = false);
    inline void append(CSLink* link);
    inline void insert(CSLink* link, CSLink* prev);
    inline void insert(CSLink* link, int i = 0);
    inline void remove(CSLink* link, CSLink* prev = nullptr);
    inline CSLink* remove(int i = 0);
    inline ForwardListIterator<CircularSListBase> begin() const {
      return ForwardListIterator<CircularSListBase>::begin(*this);
    }
    inline ForwardListIterator<CircularSListBase> end() const {
      return ForwardListIterator<CircularSListBase>::end(*this);
    }
};

template<typename T, typename S = SListBase>
class ISList : public S {
  public:
    using S::insert;
    typedef T AnchorType;
    ISList():S(){}
    inline T* get(int i = 0, bool del = false);
    inline T* remove(int i = 0);
    inline void append(T& a);
    inline void insert(T& a, int i = 0);
    inline ForwardListIterator<ISList, AnchorType> begin() const {
      return ForwardListIterator<ISList, AnchorType>::begin(*this);
    }
    inline ForwardListIterator<ISList, AnchorType> end() const {
      return ForwardListIterator<ISList, AnchorType>::end(*this);
    }
};

template<typename T, typename S = SListBase, bool circular = false>
class SList: public S {
  public:
    typedef TLink<T, _SLink<circular> > AnchorType;
    SList():S(){}
    inline T* get(int i = 0, bool del = false);
    inline T* remove(int i = 0);
    inline void append(T& a);
    inline void insert(T& a, int i = 0);
    inline ForwardListIterator<SList, AnchorType> begin() const {
      return ForwardListIterator<SList, AnchorType>::begin(*this);
    }
    inline ForwardListIterator<SList, AnchorType> end() const {
      return ForwardListIterator<SList, AnchorType>::end(*this);
    }
};

template<typename T>
class CircularISList : public ISList<T, CircularSListBase> {
  using typename ISList<T, CircularSListBase>::AnchorType;

  public:
    inline ForwardListIterator<CircularISList, AnchorType> begin() const {
      return ForwardListIterator<CircularISList, AnchorType>::begin(*this);
    }
    inline ForwardListIterator<CircularISList, AnchorType> end() const {
      return ForwardListIterator<CircularISList, AnchorType>::end(*this);
    }
};

template<typename T>
class CircularSList : public SList<T, CircularSListBase, true> {
  using typename SList<T, CircularSListBase, true>::AnchorType;

  public:
    inline ForwardListIterator<CircularSList, AnchorType> begin() const {
      return ForwardListIterator<CircularSList, AnchorType>::begin(*this);
    }
    inline ForwardListIterator<CircularSList, AnchorType> end() const {
      return ForwardListIterator<CircularSList, AnchorType>::end(*this);
    }
};

class DListBase : public ListBase<DLink> {
  public:
    DListBase(): ListBase() {}
    inline DLink* get(int i = 0, bool del = false);
    inline void append(DLink* link);
    inline void insert(DLink* link, DLink* prev = nullptr);
    inline void insert(DLink* link, int i = 0);
    inline void remove(DLink* link);
    inline DLink* remove(int i = 0);
    inline ForwardListIterator<DListBase> begin() const {
      return ForwardListIterator<DListBase>::begin(*this);
    }
    inline ForwardListIterator<DListBase> end() const {
      return ForwardListIterator<DListBase>::end(*this);
    }
    inline ReverseListIterator<DListBase> rbegin() const {
      return ReverseListIterator<DListBase>::begin(*this);
    }
    inline ReverseListIterator<DListBase> rend() const {
      return ReverseListIterator<DListBase>::end(*this);
    }
    inline BidirectionalListIterator<DListBase> bbegin() const {
      return BidirectionalListIterator<DListBase>::begin(*this);
    }
    inline BidirectionalListIterator<DListBase> bend() const {
      return BidirectionalListIterator<DListBase>::end(*this);
    }
};

class CircularDListBase : public ListBase<CDLink> {
  public:
    CircularDListBase(): ListBase() {}
    inline void append(CDLink* link);
    inline void insert(CDLink* link, CDLink* prev = nullptr);
    inline void insert(CDLink* link, int i = 0);
    inline void remove(CDLink* link);
    inline CDLink* remove(int i = 0);
    inline CDLink* get(int i = 0, bool del = false);
    inline ForwardListIterator<CircularDListBase> begin() const {
      return ForwardListIterator<CircularDListBase>::begin(*this);
    }
    inline ForwardListIterator<CircularDListBase> end() const {
      return ForwardListIterator<CircularDListBase>::end(*this);
    }
    inline ReverseListIterator<CircularDListBase> rbegin() const {
      return ReverseListIterator<CircularDListBase>::begin(*this);
    }
    inline ReverseListIterator<CircularDListBase> rend() const {
      return ReverseListIterator<CircularDListBase>::end(*this);
    }
    inline BidirectionalListIterator<CircularDListBase> bbegin() const {
      return BidirectionalListIterator<CircularDListBase>::begin(*this);
    }
    inline BidirectionalListIterator<CircularDListBase> bend() const {
      return BidirectionalListIterator<CircularDListBase>::end(*this);
    }
};

template<typename T, typename S = DListBase>
class IDList : public S {
  public :
    typedef T AnchorType;
    IDList():S(){}
    inline T* get(int i = 0, bool del = false);
    inline T* remove(int i = 0);
    inline void append(T& a);
    inline void insert(T& a, int i = 0);
    inline ForwardListIterator<IDList, AnchorType> begin() const {
      return ForwardListIterator<IDList, AnchorType>::begin(*this);
    }
    inline ForwardListIterator<IDList, AnchorType> end() const {
      return ForwardListIterator<IDList, AnchorType>::end(*this);
    }
    inline ReverseListIterator<IDList, AnchorType> rbegin() const {
      return ReverseListIterator<IDList, AnchorType>::begin(*this);
    }
    inline ReverseListIterator<IDList, AnchorType> rend() const {
      return ReverseListIterator<IDList, AnchorType>::end(*this);
    }
    inline BidirectionalListIterator<IDList, AnchorType> bbegin() const {
      return BidirectionalListIterator<IDList, AnchorType>::begin(*this);
    }
    inline BidirectionalListIterator<IDList, AnchorType> bend() const {
      return BidirectionalListIterator<IDList, AnchorType>::end(*this);
    }
};

template<typename T, typename S = DListBase, bool circular = false>
class DList : public S {
  public :
    typedef TLink<T, _SLink<circular> > AnchorType;
    DList():S(){}
    inline T* get(int i = 0, bool del = false);
    inline T* remove(int i = 0);
    inline void append(T& a);
    inline void insert(T& a, int i = 0);
    inline ForwardListIterator<DList, AnchorType> begin() const {
      return ForwardListIterator<DList, AnchorType>::begin(*this);
    }
    inline ForwardListIterator<DList, AnchorType> end() const {
      return ForwardListIterator<DList, AnchorType>::end(*this);
    }
    inline ReverseListIterator<DList, AnchorType> rbegin() const {
      return ReverseListIterator<DList, AnchorType>::begin(*this);
    }
    inline ReverseListIterator<DList, AnchorType> rend() const {
      return ReverseListIterator<DList, AnchorType>::end(*this);
    }
    inline BidirectionalListIterator<DList, AnchorType> bbegin() const {
      return BidirectionalListIterator<DList, AnchorType>::begin(*this);
    }
    inline BidirectionalListIterator<DList, AnchorType> bend() const {
      return BidirectionalListIterator<DList, AnchorType>::end(*this);
    }
};

template<typename T>
class CircularIDList : public IDList<T, CircularDListBase> {
  using typename IDList<T, CircularDListBase>::AnchorType;

  public :
    inline ForwardListIterator<CircularIDList, AnchorType> begin() const {
      return ForwardListIterator<CircularIDList, AnchorType>::begin(*this);
    }
    inline ForwardListIterator<CircularIDList, AnchorType> end() const {
      return ForwardListIterator<CircularIDList, AnchorType>::end(*this);
    }
    inline ReverseListIterator<CircularIDList, AnchorType> rbegin() const {
      return ReverseListIterator<CircularIDList, AnchorType>::begin(*this);
    }
    inline ReverseListIterator<CircularIDList, AnchorType> rend() const {
      return ReverseListIterator<CircularIDList, AnchorType>::end(*this);
    }
    inline BidirectionalListIterator<CircularIDList, AnchorType> bbegin() const {
      return BidirectionalListIterator<CircularIDList, AnchorType>::begin(*this);
    }
    inline BidirectionalListIterator<CircularIDList, AnchorType> bend() const {
      return BidirectionalListIterator<CircularIDList, AnchorType>::end(*this);
    }
};

template<typename T>
class CircularDList : public DList<T, CircularDListBase, true> {
  using typename DList<T, CircularDListBase, true>::AnchorType;

  public :
    inline ForwardListIterator<CircularDList, AnchorType> begin() const {
      return ForwardListIterator<CircularDList, AnchorType>::begin(*this);
    }
    inline ForwardListIterator<CircularDList, AnchorType> end() const {
      return ForwardListIterator<CircularDList, AnchorType>::end(*this);
    }
    inline ReverseListIterator<CircularDList, AnchorType> rbegin() const {
      return ReverseListIterator<CircularDList, AnchorType>::begin(*this);
    }
    inline ReverseListIterator<CircularDList, AnchorType> rend() const {
      return ReverseListIterator<CircularDList, AnchorType>::end(*this);
    }
    inline BidirectionalListIterator<CircularDList, AnchorType> bbegin() const {
      return BidirectionalListIterator<CircularDList, AnchorType>::begin(*this);
    }
    inline BidirectionalListIterator<CircularDList, AnchorType> bend() const {
      return BidirectionalListIterator<CircularDList, AnchorType>::end(*this);
    }
};

//slink
template <bool circular>
_SLink<circular>::
operator
_DLink<circular>() const {
  return _DLink<circular>((_DLink<circular>*)next, nullptr);
}

//dlink
template <bool circular>
_DLink<circular>::
operator
_SLink<circular>() const {
  return _SLink<circular>((_SLink<circular>*)next);
}

//SListBase
void
SListBase::
append(SLink* link) {
  if (get_tail()) {
    get_tail()->insert(link);
  } else {
    set_head(link);
    link->reset();
  }

  set_tail(link);
  incr_size();
}

void
SListBase::
insert(SLink* link, int i) {
  if (i <= 0) {
    insert(link, nullptr);
  } else if ((unsigned)i >= get_size()) {
    insert(link, get_tail());
  } else {
    SLink* prev = get(i-1);
    insert(link, prev);
  }
}

void
SListBase::
insert(SLink* link, SLink* prev) {
  if (prev) {
    prev->insert(link);
    if(get_tail() == prev) {
        set_tail(link);
    }
  } else {
    if (get_head()) {
      set_head(SLink::insert_head(get_head(),
                                 link));
    }
    else {
      set_head(link);
      set_tail(link);
      link->reset();
    }
  }

  incr_size();
}
 
SLink* 
SListBase::
remove(int i) {
  return get(i, true);
}

void
SListBase::
remove(SLink* link, SLink* prev) {
  if (prev) {
    link->remove(prev);

    if(get_tail() == link) {
      set_tail(prev);
    }
    decr_size();
  } else if (get_head() == link) {
    set_head(SLink::remove_head(get_head()));
    if(get_head() == nullptr)
      set_tail(nullptr);

    decr_size();
  }
}

SLink*
SListBase::
get(int i, bool del) {
  SLink* prev = nullptr;
  SLink* link = get_head();
  int j = 0;

  if (i < 0 || (unsigned)i >= get_size()) {
    return nullptr;
  }

  while (link != get_tail()) {
    if (j == i)
      break;
    prev = link;
    link = link->get_next();
    j++;
  }

  if (del == true && link != nullptr) {
    remove(link, prev);
  }

  return link;
}


//CircularSListBase
void
CircularSListBase::
append(CSLink* link) {
  if (link == nullptr) {
    return;
  }
  if (get_tail()) {
    get_tail()->insert(link);
  } else {
    link->reset();
    set_head(link);
  }
  set_tail(link);
  incr_size();
}

void
CircularSListBase::
insert(CSLink* link, int i) {
  if (i <= 0) {
    insert(link, nullptr);
  } else if ((unsigned)i >= get_size()) {
    insert(link, get_tail());
  } else {
    CSLink* prev = get(i-1);
    insert(link, prev);
  }
}


void
CircularSListBase::
insert(CSLink* link, CSLink* prev) {
  if (prev == nullptr) {
    if (get_head()) {
      set_head(CSLink::insert_head(get_head(),
                                  link,
                                  get_tail()));
    } else {
      link->reset();
      set_head(link);
      set_tail(link);
    }
  } else {
    prev->insert(link);
    if (prev == get_tail()) {
      set_tail(link);
    }
  }
  incr_size();
}
 
CSLink*
CircularSListBase::
remove(int i) {
  return get(i, true);
}

void
CircularSListBase::
remove(CSLink* link, CSLink* prev) {
  if (link == prev) {
    CSLink::remove_head(get_head(), get_tail());
    set_tail(nullptr);
    set_head(nullptr);
  }
  else {
    if (get_tail() == link) {
      set_tail(prev);
      link->remove(prev);
    } else if (get_head() == link) {
      set_head(CSLink::remove_head(get_head(), get_tail()));
    } else {
      link->remove(prev);
    }
  }
  decr_size();
}

CSLink*
CircularSListBase::
get(int i, bool del) {
  CSLink* prev = get_tail();
  CSLink* link = get_head();
  int j = 0;

  if ( i < 0 || (unsigned)i >= get_size()) {
    return nullptr;
  }

  while (link != get_tail()) {
    if (j == i)
      break;
    prev = link;
    link = link->get_next();
    j++;
  }

  if (del == true && link != nullptr) {
    remove(link, prev);
  }

  return link;
}


//ISList
template<typename T, typename S>
T*
ISList<T, S>::get(int i, bool del) {
  return (T*)(S::get(i, del));
}

template<typename T, typename S>
T*
ISList<T, S>::remove(int i) {
  return (T*)(S::remove(i));
}

template<typename T, typename S>
void
ISList<T, S>::insert(T& a, int i) {
  S::insert(&a, i);
}

template<typename T, typename S>
void
ISList<T, S>::append(T& a) {
  S::append(&a);
}

//SList
template<typename T, typename S, bool circular>
T*
SList<T, S, circular>::get(int i, bool del) {
  TLink<T, _SLink<circular> >* t = (TLink<T, _SLink<circular> >*)S::get(i, del);
  T *val;
  if (t) {
    val = t->get_info();
    if(del == true) {
      delete t;
    }
  } else {
    val = 0;
  }
  return val;
}

template<typename T, typename S, bool circular>
T*
SList<T, S, circular>::remove(int i) {
  TLink<T, _SLink<circular> >* t = (TLink<T, _SLink<circular> >*)(S::remove(i));
  T *val = nullptr;

  if(t) {
    val = t->get_info();
    delete t;
  }
  return val;
}

template<typename T, typename S, bool circular>
void
SList<T, S, circular>::append(T& a) {
  S::append(new TLink<T, _SLink<circular> >(a));
}

template<typename T, typename S, bool circular>
void
SList<T, S, circular>::insert(T& a, int i) {
  S::insert(new TLink<T, _SLink<circular> >(a), i);
}


//DListBase
void
DListBase::
append(DLink* link) {
  if (get_tail()) {
    get_tail()->insert(link);
  } else {
    set_head(link);
    link->reset();
  }

  set_tail(link);
  incr_size();
}

void
DListBase::
insert(DLink* d, int i) {
  if (i <= 0) {
    insert(d, nullptr);
    return;
  } if ((unsigned)i >= get_size()) {
    insert(d, get_tail());
  } else {
    DLink* prev = get(i-1);
    insert(d, prev);
  }
}

void
DListBase::
insert(DLink* link, DLink* prev) {
  if (prev) {
    prev->insert(link);
    if (get_tail() == prev) {
      set_tail(link);
    }
  } else if (get_head()) {
    set_head(DLink::insert_head(get_head(),
                                link));
  } else {
    link->reset();
    set_head(link);
    set_tail(link);
  }
  incr_size();
}

DLink*
DListBase::
remove(int i) {
  return get(i, true);
}

void
DListBase::
remove(DLink* link) {
  if ((link == get_head()) &&
      (link == get_tail())) {
    set_head(nullptr);
    set_tail(nullptr);
  } else if (link == get_head()) {
    set_head(link->get_next());
  } else if (link == get_tail()) {
    set_tail(link->get_prev());
  }
  link->remove();
  decr_size();
}

DLink*
DListBase::
get(int i, bool del) {
  DLink* link = get_head();
  int j = 0;

  if (i < 0 || (unsigned)i >= get_size()) {
    return nullptr;
  }

  while (link != get_tail()) {
    if (j == i)
      break;
    link = link->get_next();
    j++;
  }

  if (del == true && link != nullptr) {
     remove(link);
  }

  return link;
}

//CircularDListBase
void
CircularDListBase::
append(CDLink* link) {
  if (get_tail()) {
    get_tail()->insert(link);
  } else {
    set_head(link);
    link->reset();
  }

  set_tail(link);
  incr_size();
}

void
CircularDListBase::
insert(CDLink* link, int i) {
  if (i <= 0) {
    insert(link, nullptr);
  } else if ((unsigned)i >= get_size()) {
    insert(link, get_tail());
  } else {
    CDLink* prev = get(i-1);
    insert(link, prev);
  }
}

void
CircularDListBase::
insert(CDLink* link, CDLink* prev) {
  if (prev) {
    prev->insert(link);
    if (get_tail() == prev) {
      set_tail(link);
    }
  } else if (get_head()) {
    set_head(CDLink::insert_head(get_head(),
                                link));
  } else {
    link->reset();
    set_head(link);
    set_tail(link);
  }

  incr_size();
}

CDLink*
CircularDListBase::
remove(int i) {
  return get(i, true);
}

void
CircularDListBase::
remove(CDLink* link) {
  if ((link == get_head()) &&
      (link == get_tail())) {
    set_head(nullptr);
    set_tail(nullptr);
  } else if(link == get_head()) {
    set_head(link->get_next());
  } else if(link == get_tail()) {
    set_tail(link->get_prev());
  }

  link->remove();
  decr_size();
}

CDLink*
CircularDListBase::
get(int i, bool del) {
  CDLink* link = get_head();
  int j =  0;

  if (i < 0 || (unsigned)i >= get_size()) {
    return nullptr;
  }

  while(link != get_tail()) {
   if (j == i)
     break;
     link = link->get_next();
     j++;
  }
  if (del == true && link != nullptr) {
     remove(link);
  }
  return link;
}

//IDList
template<typename T, typename S>
T*
IDList<T, S>::get(int i, bool del) {
  return (T*)(S::get(i, del));
}

template<typename T, typename S>
T*
IDList<T, S>::remove(int i) {
  return S::remove(i);
}

template<typename T, typename S>
void
IDList<T, S>::insert(T& a, int i) {
  S::insert(&a, i);
}

template<typename T, typename S>
void
IDList<T, S>::append(T& a) {
  S::append(&a);
}

//DList
template<typename T, typename S, bool circular>
T*
DList<T, S, circular>::get(int i, bool del) {
  TLink<T, _DLink<circular> >* t = (TLink<T, _DLink<circular> >*)S::get(i, del);
  T *val;

  if (t) {
    val = t->get_info();
    if (del == true) {
        delete t;
    }
  } else {
    val = 0;
  }
  return val;
}

template<typename T, typename S, bool circular>
T*
DList<T, S, circular>::remove(int i) {
  TLink<T, _DLink<circular> >* t = (TLink<T, _DLink<circular> >*)S::remove(i);
  T *val = nullptr;

  if (t) {
    val = t->get_info();
    delete t;
  }
  return val;
}

template<typename T, typename S, bool circular>
void
DList<T, S, circular>::append(T& a) {
  S::append(new TLink<T, _DLink<circular> >(a));
}

template<typename T, typename S, bool circular>
void
DList<T, S, circular>::insert(T& a, int i) {
  S::insert(new TLink<T, _DLink<circular> >(a), i);
}

} /* com */
} /* goffersoft */
} /* core */

#endif /* __LIST_H__ */
