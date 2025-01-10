#ifndef SEMANTIC_ANALYZER_HPP
#define SEMANTIC_ANALYZER_HPP

#include "visitor.hpp"
#include "symbolTable.hpp"
#include "output.hpp"
#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>


using namespace ast;

class SemanticAnalyzer : public Visitor {
private:
    // SymbolTable* symbolTable; 
    SymbolTable symbolTable;
    output::ScopePrinter printer;

public:
    // SemanticAnalyzer(SymbolTable* symbolTable)
    //     : symbolTable(symbolTable) {}
    SemanticAnalyzer() : symbolTable(), printer() {}

    // Start a new scope (for functions, blocks, if, while, etc.)
    void beginScope() {
        symbolTable.beginScope();
        printer.beginScope();
    }

    // End the current scope
    void endScope() {
        symbolTable.endScope();
        printer.endScope();
    }

    // Implementations of visit methods
    void visit(ast::Num& node) override { }

    void visit(ast::NumB& node) override {
        if (node.getValue() > 255) {
            errorByteTooLarge(node.getLine(), node.getValue());
        }
    }

    void visit(ast::String& node) override {}

    void visit(ast::Bool& node) override {}

    void visit(ast::ID& node) override {
        Symbol* var = symbolTable.getSymbol(node.getValue());
        if (!var) {
            errorUndef(node.getLine(), node.getValue());
        }
    }

    void visit(ast::BinOp& node) override {
        node.getLeft()->accept(*this);
        node.getRight()->accept(*this);

        
        // BuiltInType binopType = BuiltInType::TYPE_ERROR;
        // if ((node.getLeft()->getType() == BuiltInType::BYTE && node.getRight()->getType() == BuiltInType::BYTE)) {
        //         binopType = BuiltInType::BYTE;
        // }
        // else if (((node.getLeft()->getType() == BuiltInType::INT && node.getRight()->getType() == BuiltInType::INT) ||
        //         (node.getLeft()->getType() == BuiltInType::BYTE && node.getRight()->getType() == BuiltInType::INT) ||
        //         (node.getLeft()->getType() == BuiltInType::INT && node.getRight()->getType() == BuiltInType::BYTE))) {
        //         binopType = BuiltInType::INT;
        // }
        // node.setType(binopType);

        if (node.getType() == NODE_Undecided) {
            printf("Node error, not decided node\n");
            // errorMismatch(node.getLine());
        }
    }

    void visit(ast::RelOp& node) override {
        node.getLeft()->accept(*this);
        node.getRight()->accept(*this);

        std::cout << "Type of left --- " << typeid(*node.getLeft()).name() << std::endl;
        std::cout << "Type of right --- " << typeid(*node.getRight()).name() << std::endl;

        // BuiltInType leftType = BuiltInType::TYPE_ERROR == node.getLeft()->getType() ? symbolTable.getSymbol()        

        if (node.getType() == NODE_Undecided) {
            printf("Node error, not decided node\n");
            // errorMismatch(node.getLine());
        }
    }

    void visit(ast::Not& node) override {
        node.getExpr()->accept(*this);
        
        // BuiltInType binopType = BuiltInType::TYPE_ERROR;
        // binopType = node.getExpr()->getType() == BuiltInType::BOOL ? BuiltInType::BOOL : BuiltInType::TYPE_ERROR;

        // if (node.getType() == BuiltInType::TYPE_ERROR) {
        //     errorMismatch(node.getLine());
        // }
    }

    void visit(ast::And& node) override {
        node.getLeft()->accept(*this);
        node.getRight()->accept(*this);

        // BuiltInType binopType = BuiltInType::TYPE_ERROR;
        // if (node.getLeft()->getType() == BuiltInType::BOOL && node.getRight()->getType() == BuiltInType::BOOL) {
        //     binopType = BuiltInType::BOOL;
        // }

        // if (node.getType() == BuiltInType::TYPE_ERROR) {
        //     errorMismatch(node.getLine());
        // }
    }

    void visit(ast::Or& node) override {
        node.getLeft()->accept(*this);
        node.getRight()->accept(*this);

        // BuiltInType binopType = BuiltInType::TYPE_ERROR;
        // if (node.getLeft()->getType() == BuiltInType::BOOL && node.getRight()->getType() == BuiltInType::BOOL) {
        //     binopType = BuiltInType::BOOL;
        // }

        // if (node.getType() == BuiltInType::TYPE_ERROR) {
        //     errorMismatch(node.getLine());
        // }
    }

    void visit(ast::Type& node) override {}

    void visit(ast::Cast& node) override {
        node.getExpr()->accept(*this);

        // ??? check + errors ???

    }

    void visit(ast::ExpList& node) override {
        for (auto& expr : node.getExpressions()) {
            expr->accept(*this);
        }
    }

    void visit(ast::Call& node) override {
        Symbol* func = symbolTable.getSymbol(node.getFuncId());
        if (!func) {
            errorUndefFunc(node.getLine(), node.getFuncId());
        }

        node.getArgs()->accept(*this);

        // need to compare types of arguments from symbolTable to types of arguments from node.getArgs()->getType()
        // if there is at least one mismatch need to call error function with arguments types as string list
        /*if (-------) {
            errorPrototypeMismatch(node.getLine(), node.getFuncId(), -------- );
        }*/
    }

    void visit(ast::Statements& node) override {
        for (auto& statement : node.getStatements()) {
            statement->accept(*this);
        }
    }

    void visit(ast::Break& node) override {
        /* need to implement inLoopScope() in symbolTable */
        // then we can use this VVV
        /* if (!symbolTable.inLoopScope()) {
            errorUnexpectedBreak(node.getLine());
        }*/ 
    }

    void visit(ast::Continue& node) override {
        /* need to implement inLoopScope() in symbolTable */
        // then we can use this VVV
        /* if (!symbolTable.inLoopScope()) {
            errorUnexpectedBreak(node.getLine());
        }*/ 
    }

    void visit(ast::Return& node) override {
        node.getExpr()->accept(*this);

        // Check if return type matches the function's return type
        // need to implement getCurrentFunction() in symbolTable
        /*Symbol* func = symbolTable.getCurrentFunction();
        if (func && func->getDataType() != node.getExpr()->getType()) {
            errorMismatch(node.getLine());
        }*/
    }

    void visit(ast::If& node) override {
        node.getCondition()->accept(*this);
        node.getThen()->accept(*this);
        if (node.getElse()) {
            node.getElse()->accept(*this);
        }

        // if (node.getCondition()->getType() != BuiltInType::BOOL) {
        //     errorMismatch(node.getLine());
        // }
    }

    void visit(ast::While& node) override {
        node.getCondition()->accept(*this);
        node.getBody()->accept(*this);

        // if (node.getCondition()->getType() != BuiltInType::BOOL) {
        //     errorMismatch(node.getLine());
        // }
    }

    void visit(ast::VarDecl& node) override {
        if (symbolTable.getSymbol(node.getVarId())) {
            errorDef(node.getLine(), node.getVarId());
        }

        printf("Current var ID is %s --- Its type is %d -- Var text is %s\n", node.getVarId().c_str(), node.getVarType(), node.getText().c_str());
        
        symbolTable.addVariableSymbol(node.getVarId(), node.getVarType(), node.getLine());
        printer.emitVar(node.getVarId(), node.getVarType(), symbolTable.getSymbol(node.getVarId())->getOffset());
        node.getVarInitExp()->accept(*this);
    }

    void visit(ast::Assign& node) override {
        Symbol* var = symbolTable.getSymbol(node.getAssignId());
        if (!var) {
            errorUndef(node.getLine(), node.getAssignId());
        }
        node.getAssignExp()->accept(*this);
    }

    void visit(ast::Formal& node) override {
        if (symbolTable.getSymbol(node.getFormalId())) {
            errorDef(node.getLine(), node.getFormalId());
        }

        symbolTable.addParameterSymbol(node.getFormalId(), node.getFormalType(), node.getLine());
        printer.emitVar(node.getFormalId(), node.getFormalType(), symbolTable.getSymbol(node.getFormalId())->getOffset());
    }

    void visit(ast::Formals& node) override {
        for (auto& formal : node.getFormals()) {
            formal->accept(*this);
        }
    }

    void visit(ast::FuncDecl& node) override {
        std::vector<BuiltInType> paramsTypes = node.getFuncParams()->getFormalsType();
        std::vector<std::string> paramsIds = node.getFuncParams()->getFormalsIds();

        
        printer.emitFunc(node.getFuncId(), node.getFuncReturnType(), paramsTypes);

        beginScope();
        node.getFuncParams()->accept(*this);
        node.getFuncBody()->accept(*this);
        endScope();
    }

    void visit(ast::Funcs& node) override {
        // The (this) is the ScopePrinter
        this->symbolTable.addFunctionSymbol("print", BuiltInType::VOID, {BuiltInType::STRING}, {"str"}, -1);
        this->symbolTable.addFunctionSymbol("printi", BuiltInType::VOID, {BuiltInType::INT}, {"num"}, -1);

        for (auto& funcDecl : node.getFuncs()) {
            this->symbolTable.addFunctionSymbol(funcDecl->getFuncId(), funcDecl->getFuncReturnType(), funcDecl->getFuncParams()->getFormalsType(), 
                funcDecl->getFuncParams()->getFormalsIds(), funcDecl->getLine());
        }

        for (auto& funcDecl : node.getFuncs()) {
            funcDecl->accept(*this);
        }
    }

    void printResults() {
        std::cout << printer;
    }
};

#endif // SEMANTIC_ANALYZER_HPP
