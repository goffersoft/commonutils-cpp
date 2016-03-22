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
 ** This file descrbes the various exception classes of the
 ** template project.
 **      not_implmeneted_error exception class
 **/
#ifndef __EXCEPT_H__
#define __EXCEPT_H__

#include<exception>
#include<string>

namespace com {
namespace goffersoft {
namespace core {

using std::exception;
using std::string;

class not_implemented_error : public exception {
    private :
        string msg;

    public :
        not_implemented_error(
            const string& m =
                    "function not implemented") : exception(), msg(m){}

        const char* what() const noexcept override {
            return msg.c_str();
        }
};

} //com
} //goffersoft
} //core

#endif /* __EXCEPT_H__ */
