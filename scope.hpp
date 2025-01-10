#ifndef SCOPE_HPP
#define SCOPE_HPP

#include "symbol.hpp"
#include "output.hpp"
#include <unordered_map>
#include <memory>
#include <stdexcept>
using namespace ast;
using namespace output;

/*const char* symbolTypeToString(SymbolType type) {
    switch (type) {
        case SymbolType::VARIABLE: return "VARIABLE";
        case SymbolType::FUNCTION: return "FUNCTION";
        default: return "UNKNOWN";
    }
}

const char* builtInTypeToString(BuiltInType type) {
    switch (type) {
        case BuiltInType::INT: return "INT";
        case BuiltInType::BYTE: return "BYTE";
        case BuiltInType::BOOL: return "BOOL";
        case BuiltInType::TYPE_ERROR: return "TYPE_ERROR";
        default: return "UNKNOWN";
    }
}

void printSymbolTable(const std::unordered_map<std::string, Symbol>& symbolTable) {
    for (const auto& [key, value] : symbolTable) {
        printf("Key: %s\n", key.c_str());
        printf("  Name: %s\n", value.getName().c_str());
        printf("  Symbol Type: %s\n", symbolTypeToString(value.getSymbolType()));
        printf("  Data Type: %s\n", builtInTypeToString(value.getDataType()));
        printf("  Offset: %d\n", value.getOffset());

        if (value.getSymbolType() == SymbolType::FUNCTION) {
            printf("  Parameter Types: ");
            for (BuiltInType type : value.getParameterTypes()) {
                printf("%s ", builtInTypeToString(type));
            }
            printf("\n  Parameter Names: ");
            for (const std::string& name : value.getParameterNames()) {
                printf("%s ", name.c_str());
            }
            printf("\n");
        }
    }
}*/


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
        //printSymbolTable(symbolTable);
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

    const std::unordered_map<std::string, Symbol>& getSymbolTable() const {
        return symbolTable;
    }
};


#endif // SCOPE_HPP
