/**
 **
 ** This file is part of <template>.
 **
 ** <template> is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** <template> is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with <template>. If not, see <http://www.gnu.org/licenses/>.
 **
 ** This file descrbes the HelloWorld class of the <template> project.
 ** This class is the root class of all other classes.
 **/
#ifndef __HELLO_WORLD__
#define __HELLO_WORLD__

#include "object.h"


#ifdef __cplusplus
namespace com {
namespace goffersoft {
namespace hello {

extern "C" {
#endif

const char *hello_world();

#ifdef __cplusplus
}
#endif

using com::goffersoft::core::Object;

class HelloWorld : public Object {
    protected:
        string to_string() const {
            return string("Hello C++ World!");
        }
        
};

#ifdef __cplusplus
} /* com */
} /* goffersoft */
} /* hello */
#endif

#endif /* __HELLO_WORLD__ */
