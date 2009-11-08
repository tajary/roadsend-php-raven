/* ***** BEGIN LICENSE BLOCK *****
;; Roadsend PHP Compiler
;;
;; Copyright (c) 2008-2009 Shannon Weyrick <weyrick@roadsend.com>
;;
;; This program is free software; you can redistribute it and/or
;; modify it under the terms of the GNU General Public License
;; as published by the Free Software Foundation; either version 2
;; of the License, or (at your option) any later version.
;;
;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with this program; if not, write to the Free Software
;; Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
   ***** END LICENSE BLOCK *****
*/

#include "rphp/analysis/pSourceFile.h"

#include "rphp/analysis/pParseError.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

#include <unicode/ustring.h>
#include <unicode/unistr.h>
#include <unicode/schriter.h>
#include <stdio.h>

namespace rphp { 

pSourceFile::pSourceFile(const pSourceFileDesc& file):
    file_(file)
{

    std::ifstream instream(file_.get<0>().c_str());
    if (!instream.is_open()) {
        throw pParseError("couldn't open file [" + file_.get<0>() + "]");
    }
    instream.unsetf(std::ios::skipws);

    // first we get a raw bytewise buffer

    if ((file_.get<1>() == "ASCII") || (file_.get<1>() == "UTF8")) {

        // basic case
        contents_.assign(std::istreambuf_iterator<std::string::value_type>(instream.rdbuf()),
                         std::istreambuf_iterator<std::string::value_type>());

    }
    else {    

        // charset conversion
        std::string rawBuffer(std::istreambuf_iterator<std::string::value_type>(instream.rdbuf()),
                              std::istreambuf_iterator<std::string::value_type>());

        // charset conversion we leave to UnicodeString
        // note this "pivots" through a 16 bit UChar, but so does the C ucnv_ interface
        UnicodeString ubuffer(rawBuffer.data(), rawBuffer.length(), file_.get<1>().c_str());
        if (ubuffer.isBogus()) {
            throw pParseError("could not perform character conversion in file [" + file_.get<0>() + "] from charset [" + file_.get<1>() + "]");
        }

        // finally to wchar_t for lexer
        int32_t bsize = ubuffer.countChar32();

        char* buffer = new char[bsize];
        int32_t newLength;
        UErrorCode errorCode(U_ZERO_ERROR);
        u_strToUTF8(buffer,
                    ubuffer.countChar32(),
                    &newLength,
                    ubuffer.getBuffer(),
                    ubuffer.length(),
                    &errorCode);
        assert(U_SUCCESS(errorCode));

        contents_.assign(buffer, newLength);
        delete buffer;
        
    }
    
}


} // namespace

