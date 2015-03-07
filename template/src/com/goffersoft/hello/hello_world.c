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
 ** This file implements the hello_world_func class of the <template> project.
 ** This class is the root class of all other classes.
 **/

#include <stdio.h>
#include "hello_world_1.h"

const char *hello_world() {
    printf("%s\n", hello_world_1());
    return "Hello C World! ";
}
