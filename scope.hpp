#ifndef SCOPE_HPP
#define SCOPE_HPP

#include "Symbol.hpp"
#include "output.hpp"
#include <unordered_map>
#include <memory>
#include <stdexcept>

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

    void addVariableSymbol(const std::string& name, Symbol::DataType datatype, int lineno) {
        if (symbolTable.count(name) > 0) {
            errorDef(lineno, name);
        }
        symbolTable[name] = Symbol(name, Symbol::SymbolType::VARIABLE, datatype, nextOffset++);
    }

    void addParameterSymbol(const std::string& name, Symbol::DataType datatype, int lineno) {
        if (symbolTable.count(name) > 0) {
            errorDef(lineno, name);
        }
        symbolTable[name] = Symbol(name, Symbol::SymbolType::VARIABLE, datatype, nextParamOffset--);
    }

    void addFunctionSymbol(const std::string& name, Symbol::DataType returnType,
        const std::vector<Symbol::DataType>& paramTypes,
        const std::vector<std::string>& paramNames, int lineno) {
        if (symbolTable.count(name) > 0) {
            errorDef(lineno, name);
        }
        symbolTable[name] = Symbol(name, Symbol::SymbolType::FUNCTION, returnType, paramTypes, paramNames);
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
