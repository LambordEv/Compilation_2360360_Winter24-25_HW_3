#ifndef SCOPE_HPP
#define SCOPE_HPP

#include "symbol.hpp"
#include "output.hpp"
#include <unordered_map>
#include <memory>
#include <stdexcept>
using namespace ast;
using namespace output;

class Scope {
private:
    Scope* parent;
    std::unordered_map<std::string, Symbol> symbolTable;
    int nextOffset;
    int nextParamOffset;

public:
    Scope(Scope* parent)
        : parent(parent),
          nextOffset(0),
          nextParamOffset(-1) {}

    void addVariableSymbol(const std::string& name, BuiltInType datatype, int lineno) {
        if (symbolTable.count(name) > 0) {
            errorDef(lineno, name);
        }
        symbolTable[name] = Symbol(name, SymbolType::VARIABLE, datatype, nextOffset++);
    }

    void addParameterSymbol(const std::string& name, BuiltInType datatype, int lineno) {
        if (symbolTable.count(name) > 0) {
            errorDef(lineno, name);
        }
        symbolTable[name] = Symbol(name, SymbolType::VARIABLE, datatype, nextParamOffset--);
    }

    void addFunctionSymbol(const std::string& name, BuiltInType returnType,
        const std::vector<BuiltInType>& paramTypes,
        const std::vector<std::string>& paramNames, int lineno) {
        if (symbolTable.count(name) > 0) {
            errorDef(lineno, name);
        }
        symbolTable[name] = Symbol(name, SymbolType::FUNCTION, returnType, paramTypes, paramNames);
    }

    Symbol* getSymbol(const std::string& name) {
        auto it = symbolTable.find(name);
        if (it != symbolTable.end()) {
            return &it->second;
        }
        return parent ? parent->getSymbol(name) : nullptr;
    }

    int getNextOffset() const {
        return nextOffset;
    }

    int getNextParamOffset() const {
        return nextParamOffset;
    }
};

#endif // SCOPE_HPP
