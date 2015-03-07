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
 **/
#include <main>
#include <hello>

using std::cout;
using std::endl;
using com::goffersoft::hello::HelloWorld;
using com::goffersoft::hello::hello_world;

int main(int argc, char **argv) {
  HelloWorld h;

  cout << (string)h << endl;
  
  cout << hello_world()  << endl;
}
