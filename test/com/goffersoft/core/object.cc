/**
 **
 ** This file is part of goffersoft.
 **
 ** goffersoft is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** goffersoft is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with goffersoft. If not, see <http://www.gnu.org/licenses/>.
 ** 
 ** This file contains test code for the object.h class
 **/
#include "object.h"
#include "iostream"

using std::endl;
using std::cout;
using com::goffersoft::core::Object;

class A : public Object {
    private :
        int a;
 
    public :
        A(int a) {
            this->a = a;
        }

        int cmp(const Object& obj) const {
            cout << "In A" << endl;
            if(((A *)(&obj))->a == a)
                return 0;
            else if(((A *)(&obj))->a < a)
                return -1;
            else
                return 1;
        }
};

class B : public A {
    private :
        int b;
 
    public :
        B(int b):A(b) {
            this->b = b;
        }

        int cmp(const Object& obj) const {
            cout << "In B" << endl;
            if(((B *)(&obj))->b == b)
                return 0;
            else if(((B *)(&obj))->b < b)
                return -1;
            else
                return 1;
        }
};

class C : public Object {
    private :
        string c;
 
    public :
        C(string c) {
            this->c = c;
        }

        int cmp(const Object& obj) const {
            cout << "In C" << endl;
            if(((C *)(&obj))->c == c)
                return 0;
            else if(((C *)(&obj))->c < c)
                return -1;
            else
                return 1;
        }
};


int test_object_main (int argc, char **argv) {
    A a1(1);
    A a2(2);
    B b1(1);
    B b2(1);
    C c1("Hello World");
    Object *obj1 = &a1;
    Object *obj2 = &a2;
    Object *obj3 = &b1;
    Object *obj4 = &b2;
    Object *obj5 = &c1;

    cout << string(*obj1) << " " << (*obj1 == *obj2) << endl;
    cout << string(*obj2) << " " << (*obj3 == *obj4) << endl;
    cout << string(*obj3) << " " << (*obj1 == *obj4) << endl;
    cout << string(*obj4) << " " << (*obj3 == *obj1) << endl;
    cout << string(*obj5) << " " << (*obj5 == *obj1) << endl;

    return 0;
}
