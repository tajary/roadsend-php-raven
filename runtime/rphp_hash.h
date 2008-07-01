/* ***** BEGIN LICENSE BLOCK *****
 * Roadsend PHP Compiler Runtime Libraries
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 * ***** END LICENSE BLOCK ***** */

#ifndef RPHP_HASH_H_
#define RPHP_HASH_H_

#include <iostream>

namespace rphp {

// XXX placeholder
class phash {
    private:
        int size;
    public:
        phash(int sizevar) : size(sizevar) { }

        phash(const phash& h) {
            size = h.size;
        }
        int getSize() const { return size; }
        ~phash() { std::cout << "destorying php_hash with " << size << " fake elements" << std::endl; }

};

std::ostream& operator << (std::ostream& os, const rphp::phash& h)
{
    return os << "php_hash" << std::endl;
}

} /* namespace rphp */

#endif /* RPHP_HASH_H_ */