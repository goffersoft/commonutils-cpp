/** 
 **
 ** This file is part of algs4cc.
 **
 ** algs4cc is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** algs4cc is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with algs4cc. If not, see <http://www.gnu.org/licenses/>.
 **
 ** This file descrbes the object class of the algs4cc project.
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

    virtual string to_string() const {
      return string("string rep of the object");
    }

  public :

    operator string() const {
      return to_string();
    }

    friend int operator ==(const object& lhs, 
                           const object& rhs) {
      if (typeid(lhs) != typeid(rhs))
        return false;

      return (lhs.cmp(rhs) == 0);
    }

    friend int operator !=(const object& lhs, 
                           const object& rhs) {
      if (typeid(lhs) != typeid(rhs))
        return true;

      return (lhs.cmp(rhs) != 0);
    }
         
    friend int operator <=(const object& lhs, 
                           const object& rhs) {
      if (typeid(lhs) != typeid(rhs))
        return false;

      return !(lhs.cmp(rhs) > 0);
    }

    friend int operator >=(const object& lhs, 
                           const object& rhs) {
      if (typeid(lhs) != typeid(rhs))
        return false;

      return !(lhs.cmp(rhs) < 0);
    }

    friend int operator >(const object& lhs, 
                          const object& rhs) {
      if (typeid(lhs) != typeid(rhs))
        return false;

      return (lhs.cmp(rhs) > 0);
    }

    friend int operator <(const object& lhs, 
                          const object& rhs) {
      if (typeid(lhs) != typeid(rhs))
        return false;

      return (lhs.cmp(rhs) < 0);
    }
};

} /* com */
} /* goffersoft */
} /* core */

#endif /* __OBJECT_H__ */
