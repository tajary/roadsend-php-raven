/* ***** BEGIN LICENSE BLOCK *****
;; Roadsend PHP Compiler
;;
;; Copyright (c) 2009 Shannon Weyrick <weyrick@roadsend.com>
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

#ifndef RPHP_PCODEGEN_H_
#define RPHP_PCODEGEN_H_

#include <queue>
#include <string>

#include <boost/unordered_map.hpp>

#include <llvm/Support/IRBuilder.h>

#include "rphp/IR/pIRHelper.h"
#include "rphp/analysis/pASTVisitors.h"

namespace llvm {
    class Module;
    class Value;
}

namespace rphp { namespace IR {

// TODO: llvm has structures for this. use those?
typedef boost::unordered_map<pIdentString, llvm::Value*> symbolTableType;

class pIRHelper;

class pCodeGen: public AST::baseVisitor {

public:
    typedef std::vector<llvm::Value*> valueVectorType;

private:
    llvm::Module* llvmModule_; // won't free
    pIdentString functionSymbol_;
    pIRHelper IRHelper_;

    llvm::IRBuilder<> currentBlock_;
    llvm::Value* runtimeEngine_; // don't own

    llvm::Function* thisFunction_;

    std::queue<llvm::Value*> valueStack_;
    std::queue<valueVectorType> destructList_;

    symbolTableType symTable_;

    llvm::Value* newVarOnStack(const char*);

public:

    pCodeGen(llvm::Module* mod, const pIdentString& funSym);
    ~pCodeGen(void);

    void finalize(void);

    // nodes
    void visit_echoStmt(AST::echoStmt*);
    void visit_inlineHtml(AST::inlineHtml*);
    void visit_literalString(AST::literalString*);
    void visit_literalInt(AST::literalInt*);
    void visit_literalFloat(AST::literalFloat*);
    void visit_literalBool(AST::literalBool*);
    void visit_literalNull(AST::literalNull*);
    void visit_literalArray(AST::literalArray*);
    void visit_assignment(AST::assignment*);
    void visit_var(AST::var*);
    void visit_functionInvoke(AST::functionInvoke*);

};

} } // namespace

#endif /* RPHP_PCODEGEN_H_ */