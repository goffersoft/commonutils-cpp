/** 
 **
 ** This file is part of template.
 **
 ** template is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** template is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with template. If not, see <http://www.gnu.org/licenses/>.
 **
 ** This file descrbes the object class of the template project.
 ** This class is the root class of all other classes.
 **/
#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <string>
#include <typeinfo>

using std::string;

namespace com {
namespace goffersoft {
namespace core {

class object {
    public :
        operator string() const {
          return to_string();
        }

        bool equals(const object& that) const {
            if (typeid(*this) != typeid(that))
                return false;

            if(this == &that) 
                return true; 

            return is_equal(that);
        }
         
        bool operator ==(const object& that) const {
            if (typeid(*this) != typeid(that))
                return false;

            if (this == &that)
                return true;
      
            return (this->cmp(that) == 0);
        }

        bool operator !=(const object& that) const {
            if (typeid(*this) != typeid(that))
                return false;

            if (this == &that)
                return false;
 
            return (this->cmp(that) != 0);
        }

        bool operator <=(const object& that) const {
            if (typeid(*this) != typeid(that))
                return false;

            if (this == &that)
                return true;
      
            return (this->cmp(that) <= 0);
        }

        bool operator >=(const object& that) const {
            if (typeid(*this) != typeid(that))
                return false;

            if (this == &that)
                return true;
      
            return (this->cmp(that) >= 0);
        }

        bool operator <(const object& that) const {
            if (typeid(*this) != typeid(that))
                return false;

            if (this == &that)
                return false;
      
            return (this->cmp(that) < 0);
        }

        bool operator >(const object& that) const {
            if (typeid(*this) != typeid(that))
                return false;

            if (this == &that)
                return false;
      
            return (this->cmp(that) > 0);
        }

/*        friend bool operator ==(const object& lhs, 
                               const object& rhs) {
            if (typeid(lhs) != typeid(rhs))
                return false;

            return lhs.operator ==(rhs);

        }
        friend bool operator !=(const object& lhs, 
                               const object& rhs) {
            if (typeid(lhs) != typeid(rhs))
                return false;

            return lhs.operator !=(rhs);
        }

        friend bool operator <=(const object& lhs, 
                                const object& rhs) {
            if (typeid(lhs) != typeid(rhs))
                return false;

            return lhs.operator <=(rhs);
        }

        friend bool operator >=(const object& lhs,
                               const object& rhs) {
            if (typeid(lhs) != typeid(rhs))
                return false;

            return lhs.operator >=(rhs);
        }

        friend bool operator <(const object& lhs, 
                               const object& rhs) {

            if (typeid(lhs) != typeid(rhs))
                return false;

            return lhs.operator <(rhs);
        }

        friend bool operator >(const object& lhs, 
                              const object& rhs) {
            if (typeid(lhs) != typeid(rhs))
                return false;

            return lhs.operator >(rhs);
        }*/

        virtual size_t hash_code() const {
            return size_t(this);
        }

    protected :
        object() {}
        virtual ~object() {}

        virtual int cmp(const object& obj) const {
            if (this == &obj)
                return 0;
            else if (this < &obj)
                return -1;
            else
                return 1;
        }

        virtual bool is_equal(const object& obj) const {
            return false;
        }

        virtual string to_string() const {
            return string("string rep of the object");
        }
};

} /* com */
} /* goffersoft */
} /* core */

#endif /* __OBJECT_H__ */
