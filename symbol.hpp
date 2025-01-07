#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>
#include <vector>
#include "nodes.hpp"
using namespace ast;

class Symbol {
public:
    enum class SymbolType {
        VARIABLE,
        FUNCTION
    };

    " from ast namespace:
    /* Built-in types */
    enum BuiltInType {
        TYPE_ERROR = -1,
        VOID,
        BOOL,
        BYTE,
        INT,
        STRING
    };"

private:
    std::string name;                   // Name of the symbol
    SymbolType symbolType;              // VARIABLE or FUNCTION
    BuiltInType dataType;                  // Data type (e.g., INT, BYTE, BOOL, etc.)
    int offset;                         // Memory offset (for variables or parameters)
    std::vector<BuiltInType> parameterTypes; // Function parameter types
    std::vector<std::string> parameterNames; // Function parameter names

public:
    // Constructor for variables
    Symbol(const std::string& name, SymbolType symbolType, BuiltInType dataType, int offset)
        : name(name), symbolType(symbolType), dataType(dataType), offset(offset) {}

    // Constructor for functions
    Symbol(const std::string& name, SymbolType symbolType, BuiltInType dataType,
           const std::vector<BuiltInType>& paramTypes, const std::vector<std::string>& paramNames)
        : name(name), symbolType(symbolType), dataType(dataType),
          offset(0), isDefined(isDefined), parameterTypes(paramTypes), parameterNames(paramNames) {}

    // Getters
    const std::string& getName() const { return name; }
    SymbolType getSymbolType() const { return symbolType; }
    BuiltInType getDataType() const { return dataType; }
    int getOffset() const { return offset; }
    const std::vector<BuiltInType>& getParameterTypes() const { return parameterTypes; }
    const std::vector<std::string>& getParameterNames() const { return parameterNames; }

};

#endif // SYMBOL_HPP
