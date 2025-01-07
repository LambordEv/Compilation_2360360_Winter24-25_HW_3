#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include "Scope.hpp"
#include "nodes.hpp"
using namespace ast;
#include <memory>
#include <unordered_map>
#include <string>
#include <stack>

class SymbolTable {
private:
    Scope* globalScope; // Global scope for functions and global variables
    std::stack<Scope*> scopeStack; // Stack to manage nested scopes

public:
    SymbolTable() {
        globalScope = new Scope(nullptr);
        scopeStack.push(globalScope);

        globalScope->addFunctionSymbol("print", BuiltInType::VOID, {BuiltInType::STRING}, -1);
        globalScope->addFunctionSymbol("printi", BuiltInType::VOID, {BuiltInType::INT}, -1);
    }

    ~SymbolTable() {
        while (!scopeStack.empty()) {
            delete scopeStack.top();
            scopeStack.pop();
        }
    }

    void addVariableSymbol(const std::string& name, BuiltInType dataType, int lineno) {
        getCurrentScope()->addVariableSymbol(name, dataType, lineno);
    }

    void addParameterSymbol(const std::string& name, BuiltInType dataType, int lineno) {
        getCurrentScope()->addParameterSymbol(name, dataType, lineno);
    }

    void addFunctionSymbol(const std::string& name, BuiltInType returnType,
                           const std::vector<BuiltInType>& paramTypes,
                           const std::vector<std::string>& paramNames, int lineno) {
        globalScope->addFunctionSymbol(name, returnType, paramTypes, paramNames, lineno);
        beginScope();
        for (size_t i = 0; i < paramNames.size(); ++i) {
            getCurrentScope()->addParameterSymbol(paramNames[i], paramTypes[i], lineno);
        }
    }

    Symbol* getSymbol(const std::string &name) {
        return getCurrentScope()->getSymbol(name);
    }

    void beginScope() {
        Scope* newScope = new Scope(scopeStack.top());
        scopeStack.push(newScope);
    }

    void endScope() {
        if (scopeStack.size() > 1) { 
            Scope* currentScope = scopeStack.top();
            scopeStack.pop();
            delete currentScope;
        } else {
            throw std::runtime_error("Cannot end the last scope");
        }
    }

    Scope* getCurrentScope() {
        return scopeStack.top();
    }
};

#endif // SYMBOL_TABLE_HPP
