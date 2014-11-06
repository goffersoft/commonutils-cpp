#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <string>
#include <typeinfo>

using std::string;

namespace com {
namespace goffersoft {
namespace core {

class Object {

    protected :

        Object() {}
        virtual ~Object() {}


        virtual int cmp(const Object& obj) const {
            if(this == &obj)
                return 0;
            else if(this < &obj)
                return -1;
            else
                return 1;
        }

        virtual string to_string() const {
            return string("string rep of the Object");
        }

    public :

        operator string() const {
            return to_string();
        }

        friend int operator ==(const Object& lhs, 
                         const Object& rhs) {
            if(typeid(lhs) != typeid(rhs))
                return false;

            return (lhs.cmp(rhs) == 0);
        }

        friend int operator !=(const Object& lhs, 
                                const Object& rhs) {
            if(typeid(lhs) != typeid(rhs))
                return true;

            return (lhs.cmp(rhs) != 0);
        }
         
        friend int operator <=(const Object& lhs, 
                                const Object& rhs) {
            if(typeid(lhs) != typeid(rhs))
                return false;

            return !(lhs.cmp(rhs) > 0);
        }

        friend int operator >=(const Object& lhs, 
                                const Object& rhs) {
            if(typeid(lhs) != typeid(rhs))
                return false;

            return !(lhs.cmp(rhs) < 0);
        }

        friend int operator >(const Object& lhs, 
                                const Object& rhs) {
            if(typeid(lhs) != typeid(rhs))
                return false;

            return (lhs.cmp(rhs) > 0);
        }

        friend int operator <(const Object& lhs, 
                                const Object& rhs) {
            if(typeid(lhs) != typeid(rhs))
                return false;

            return (lhs.cmp(rhs) < 0);
        }
};

} /* com */
} /* goffersoft */
} /* core */

#endif /* __OBJECT_H__ */
