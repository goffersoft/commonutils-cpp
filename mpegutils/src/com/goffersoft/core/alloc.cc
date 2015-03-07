#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::hex;
using std::string;

#include "list.h"

static char membase[1024];
static char poolbase[256];
char* membase_ptr = membase;
char* poolbase_ptr = poolbase;

struct mem;

struct Pool : public slink {
    unsigned sz;
    mem* mempool;
};

struct mem : public slink {
    Pool* pool;
};

static Pool* list_of_pools;

void* operator new(size_t sz) throw(std::bad_alloc) {
    cout<< "My New Called" << endl;
    Pool* x = list_of_pools;
    bool create_pool = true;

    while(x) {
        if(x->sz == sz) {
            create_pool = false;
            if(x->mempool) {
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
    if(create_pool) {
        x = (Pool*)poolbase_ptr;
        poolbase_ptr += sizeof(Pool);
        x->set_next(0);
        x->sz = sz;
        x->mempool = 0;
        if(list_of_pools) {
            x->set_next((slink*)list_of_pools);
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

    if(x->mempool) {
        mem_ptr->set_next(x->mempool);
    }
    x->mempool = mem_ptr;
    return;
}

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


int alloc_test_main(int argc, char** argv) {
    int *i = new int(10);
    int *j = new int(20);
    string *s = new string("Hello World");

    cout << *i << ' ' << *j << ' ' << *s << endl;

    delete i;

    print_mem_pool();
    
    delete j;
    
    print_mem_pool();
    
    delete s;
    
    print_mem_pool();

    return 0;
}
