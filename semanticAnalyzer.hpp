#ifndef SEMANTIC_ANALYZER_HPP
#define SEMANTIC_ANALYZER_HPP

#include "visitor.hpp"
#include "symbolTable.hpp"
#include "output.hpp"
#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>

using namespace std;

SemanticNodeType builtInToNodeType(const BuiltInType& type) {
    switch (type) {
        case BuiltInType::TYPE_ERROR: return NODE_Undecided;
        case BuiltInType::VOID:       return NODE_Undecided;
        case BuiltInType::BOOL:       return NODE_Bool;
        case BuiltInType::BYTE:       return NODE_NumB;
        case BuiltInType::INT:        return NODE_Num;
        case BuiltInType::STRING:     return NODE_String;
        default:                      return NODE_Undecided;
    }
}

string builtInTypeToString(const BuiltInType& type) {
    switch (type) {
        case BuiltInType::TYPE_ERROR: return "TYPE_ERROR";
        case BuiltInType::VOID:       return "VOID";
        case BuiltInType::BOOL:       return "BOOL";
        case BuiltInType::BYTE:       return "BYTE";
        case BuiltInType::INT:        return "INT";
        case BuiltInType::STRING:     return "STRING";
        default:                      return "UNKNOWN";
    }
}

vector<string> convertVectorToStrings(const vector<BuiltInType>& vec) {
    vector<string> result;
    for (auto& type : vec) {
        result.push_back(builtInTypeToString(type));
    }
    return result;
}



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
    void beginScope(string scopeName = "", bool isLoopScope = false) {
        symbolTable.beginScope(isLoopScope, scopeName);
        printer.beginScope();
    }

    // End the current scope
    void endScope() {
        symbolTable.endScope();
        printer.endScope();
    }

    // Implementations of visit methods
    void visit(ast::Num& node) override { 
        // Not Needed ?
    }

    void visit(ast::NumB& node) override {
        if (node.getValueInt() > 255) {
            errorByteTooLarge(node.getLine(), node.getValueInt());
        }
    }

    void visit(ast::String& node) override {
        // Not Needed ?
    }

    void visit(ast::Bool& node) override {
        // Not Needed ?
    }

    void visit(ast::ID& node) override {
        Symbol* var = symbolTable.getSymbol(node.getValueStr(), node.getLine());
        if (!var) {
            errorUndef(node.getLine(), node.getValueStr());
        }
    }

    void visit(ast::BinOp& node) override {
        node.getLeft()->accept(*this);
        node.getRight()->accept(*this);

        BuiltInType leftBuiltInType = BuiltInType::TYPE_ERROR;
        BuiltInType rightBuiltInType = BuiltInType::TYPE_ERROR;

        if (node.getLeft()->getType() == NODE_ID) {
            Symbol* left = symbolTable.getSymbol(node.getLeft()->getValueStr(), node.getLeft()->getLine());
            leftBuiltInType = left->getDataType();
        }
        else if (node.getLeft()->getType() == NODE_Num) {
            leftBuiltInType = BuiltInType::INT;
        }
        else if (node.getLeft()->getType() == NODE_NumB) {
            leftBuiltInType = BuiltInType::BYTE;
        }

        if (node.getRight()->getType() == NODE_ID) {
            Symbol* right = symbolTable.getSymbol(node.getRight()->getValueStr(), node.getRight()->getLine());
            rightBuiltInType = right->getDataType();
        }
        else if (node.getRight()->getType() == NODE_Num) {
            rightBuiltInType = BuiltInType::INT;
        }
        else if (node.getRight()->getType() == NODE_NumB) {
            rightBuiltInType = BuiltInType::BYTE;
        }

        if (TYPE_ERROR == leftBuiltInType || TYPE_ERROR == rightBuiltInType) {
            node.resultType = TYPE_ERROR;
            // printf("Node error, node type is not apropriate - %d --- %d\n", leftBuiltInType, rightBuiltInType);
            errorMismatch(node.getLine());
        } else if(BYTE == leftBuiltInType && BYTE == rightBuiltInType){
            node.resultType = BYTE;
            node.setType(NODE_NumB);
        } else {
            node.resultType = INT;
            node.setType(NODE_Num);
        }

        if (node.getType() != NODE_Num && node.getType() != NODE_NumB) {
            // printf("Node error, node type is not apropriate - %d\n", node.getType());
            // errorMismatch(node.getLine());
        }
    }

    void visit(ast::RelOp& node) override {
        node.getLeft()->accept(*this);
        node.getRight()->accept(*this);

        BuiltInType leftBuiltInType = BuiltInType::TYPE_ERROR;
        BuiltInType rightBuiltInType = BuiltInType::TYPE_ERROR;

        if (node.getLeft()->getType() == NODE_ID) {
            Symbol* left = symbolTable.getSymbol(node.getLeft()->getValueStr(), node.getLeft()->getLine());
            leftBuiltInType = left->getDataType();
        }
        else if (node.getLeft()->getType() == NODE_Num) {
            leftBuiltInType = BuiltInType::INT;
        }
        else if (node.getLeft()->getType() == NODE_NumB) {
            leftBuiltInType = BuiltInType::BYTE;
        }

        if (node.getRight()->getType() == NODE_ID) {
            Symbol* right = symbolTable.getSymbol(node.getRight()->getValueStr(), node.getRight()->getLine());
            rightBuiltInType = right->getDataType();
        }
        else if (node.getRight()->getType() == NODE_Num) {
            rightBuiltInType = BuiltInType::INT;
        }
        else if (node.getRight()->getType() == NODE_NumB) {
            rightBuiltInType = BuiltInType::BYTE;
        }

        if (node.getLeft()->getType() == NODE_Bool || node.getRight()->getType() == NODE_Bool
            || leftBuiltInType == TYPE_ERROR || leftBuiltInType == TYPE_ERROR){
            // printf("Node error, node type is not apropriate - %d\n", node.getType());
            errorMismatch(node.getLine());
        } else {
            node.setType(NODE_Bool);
        }

        if (node.getType() != NODE_Bool) {
            // printf("Node error, node type is not apropriate - %d\n", node.getType());
            // errorMismatch(node.getLine());
        }
    }

    void visit(ast::Not& node) override {
        node.getExpr()->accept(*this);
        
        if (node.getType() == NODE_Bool){
            node.setType(NODE_Bool);
        } else {
            errorMismatch(node.getLine());
        }
    }

    void visit(ast::And& node) override {
        node.getLeft()->accept(*this);
        node.getRight()->accept(*this);

        if (node.getLeft()->getType() == NODE_Bool && node.getRight()->getType() == NODE_Bool) {
            node.setType(NODE_Bool);
        } else {
            errorMismatch(node.getLine());
        }
    }

    void visit(ast::Or& node) override {
        node.getLeft()->accept(*this);
        node.getRight()->accept(*this);

        if (node.getLeft()->getType() == NODE_Bool && node.getRight()->getType() == NODE_Bool) {
            node.setType(NODE_Bool);
        } else {
            errorMismatch(node.getLine());
        }
    }

    void visit(ast::Type& node) override {
        // Not Needed ?
    }

    void visit(ast::Cast& node) override {
        node.getExpr()->accept(*this);

        Symbol* expSymbol = nullptr;
        BuiltInType originalType = TYPE_ERROR;
        BuiltInType targetType = TYPE_ERROR;
        //cout << "exp type is: " << node.getExpr()->getType() << endl;
        if (node.getExpr()->getType() == NODE_ID || node.getExpr()->getType() == NODE_Num ||
            node.getExpr()->getType() == NODE_NumB) {
            expSymbol = symbolTable.getSymbol(node.getExpr()->getValueStr(), node.getExpr()->getLine());
            if(!expSymbol) {
                cout << "In Visit Cast symbol returned as nullptr, WTF?!" << endl;
            }
            originalType = expSymbol->getDataType();
        }

        if (node.getTargetType() == INT
            && (originalType == INT || originalType == BYTE)) {
            targetType = INT;
            node.getExpr()->setType(NODE_Num);
            node.setType(NODE_Num);
        } else if (node.getTargetType() == BYTE
            && (originalType == BYTE || originalType == INT)) {
            targetType = BYTE;
            node.getExpr()->setType(NODE_NumB);
            node.setType(NODE_NumB);
        } else {
            //cout << "In Visit Cast, targetType is not apropriate - " << node.getTargetType() << endl;
            //cout << "In Visit Cast, originalType is not apropriate - " << originalType << endl;
            errorMismatch(node.getExpr()->getLine());
        }

        //Update the type of the symbol in the symbolTable
        if (nullptr != expSymbol) {
            expSymbol->setDataType(targetType);
        }
    }

    void visit(ast::ExpList& node) override {
        for (auto& expr : node.getExpressions()) {
            expr->accept(*this);
        }
    }

    void visit(ast::Call& node) override {
        // printf("Get Symbol in %s\n", "Visit Call");
        if (symbolTable.getFuncSymbol(node.getFuncId(), node.getLine()) == nullptr) {
            errorUndefFunc(node.getLine(), node.getFuncId());
        }

        Symbol* func = symbolTable.getSymbol(node.getFuncId(), node.getLine());
        if (!func) {
            errorUndefFunc(node.getLine(), node.getFuncId());
        }

        if (func->getSymbolType() != FUNCTION) {
            errorDefAsVar(node.getLine(), node.getFuncId());
        }

        node.getArgsExp()->accept(*this);

        vector<BuiltInType> paramsTypesInSymbolTable = func->getParameterTypes();
        vector<shared_ptr<Exp>> paramsInFunc = node.getArgs();

        vector<BuiltInType> types;
        for(auto& exp : paramsInFunc) {
            if (exp->getType() == NODE_ID) {
                Symbol* expSymbol = symbolTable.getSymbol(exp->getValueStr(), exp->getLine());
                if (expSymbol == nullptr) {
                    errorUndef(exp->getLine(), exp->getValueStr());
                }
                types.push_back(expSymbol->getDataType());
            } else if (exp->getType() == NODE_Num) {
                // cout << "Num type is not supported in function calls" << endl;
                types.push_back(BuiltInType::INT);
            } else if (exp->getType() == NODE_NumB) {
                types.push_back(BuiltInType::BYTE);
            } else if (exp->getType() == NODE_Bool) {
                types.push_back(BuiltInType::BOOL);
            } else if (exp->getType() == NODE_String) {
                // cout << "String type is not supported in function calls" << endl;
                types.push_back(BuiltInType::STRING);
            } else {
                types.push_back(BuiltInType::TYPE_ERROR);
            }
        }

        // in error which vector should be passed as argument????????????????????
        vector<string> typesStr = convertVectorToStrings(types);
        vector<string> paramsTypesInSymbolTableStr = convertVectorToStrings(paramsTypesInSymbolTable);
        if (paramsTypesInSymbolTable.size() != types.size()) {
            errorPrototypeMismatch(node.getLine(), node.getFuncId(), paramsTypesInSymbolTableStr);
        }
        for (size_t i = 0; i < paramsTypesInSymbolTable.size(); i++) {
            if (paramsTypesInSymbolTable[i] != types[i]) {
                errorPrototypeMismatch(node.getLine(), node.getFuncId(), paramsTypesInSymbolTableStr);
            }
        }

        node.setType(builtInToNodeType(func->getDataType())); 

    }

    void visit(ast::Statements& node) override {
        for (auto& statement : node.getStatements()) {
            statement->accept(*this);
        }
    }

    void visit(ast::Break& node) override {
        if (!(symbolTable.getCurrentScope()->isInLoopScope())) {
            errorUnexpectedBreak(node.getLine());
        }
    }

    void visit(ast::Continue& node) override {
        if (!(symbolTable.getCurrentScope()->isInLoopScope())) {
            errorUnexpectedContinue(node.getLine());
        }
    }

    void visit(ast::Return& node) override {
        node.getExpr()->accept(*this);

        string funcName = symbolTable.getCurrentScope()->getScopeName();
        Symbol* func = symbolTable.getSymbol(funcName, node.getLine());
        if(func == nullptr) {
            errorUndefFunc(node.getLine(), funcName);
        }
        BuiltInType funcRetType = func->getDataType();
        
        BuiltInType expType = BuiltInType::TYPE_ERROR;
        if(node.getExpr() == nullptr) {
            expType = BuiltInType::VOID;
        } 
        else {
            if (node.getExpr()->getType() == NODE_ID) {
                Symbol* expSymbol = symbolTable.getSymbol(node.getExpr()->getValueStr(), node.getExpr()->getLine());
                if (expSymbol == nullptr) {
                    errorUndef(node.getLine(), node.getExpr()->getValueStr());
                }
                expType = expSymbol->getDataType();
            } else if (node.getExpr()->getType() == NODE_Num) {
                expType = BuiltInType::INT;
            } else if (node.getExpr()->getType() == NODE_NumB) {
                expType = BuiltInType::BYTE;
            }
        }

        if (funcRetType != expType) {
            errorMismatch(node.getLine());
        }
    }

    void visit(ast::If& node) override {
        beginScope();
        beginScope();
        // cout<< "before line number is " << node.getLine() << endl;
        node.getCondition()->accept(*this);
        // cout << "In Visit If Condition Exists " << node.getCondition()->getType() << endl;
        // cout<< "after line number is " << node.getLine() << endl;
        if (node.getCondition()->getType() != NODE_Bool) {
            errorMismatch(node.getLine());
        }
        node.getThen()->accept(*this);
        endScope();
        endScope();
        if (node.getElse()) {
            beginScope();
            node.getElse()->accept(*this);
            endScope();
        }
    }

    void visit(ast::While& node) override {
        // Condition scope (?)
        beginScope("", true);
        node.getCondition()->accept(*this);
        // Body scope (?)
        if (node.getBody()->getType() != NODE_Undecided) {
            beginScope("", true);
            node.getBody()->accept(*this);
            endScope();
        }
        
        // cout << "In Visit While Condition Exists " << node.getCondition()->getType() << endl;
        // cout << "In Visit While Body Exists " << node.getBody()->getType() << endl;
        endScope();
    }

    void visit(ast::VarDecl& node) override {
        if (node.getVarInitExp()) {
            node.getVarInitExp()->accept(*this);
            if (node.getVarInitExp()->getType() == NODE_ID) {
                Symbol* expSymbol = symbolTable.getSymbol(node.getVarInitExp()->getValueStr(), node.getVarInitExp()->getLine());
                if (expSymbol == nullptr) {
                    errorUndef(node.getVarInitExp()->getLine(), node.getVarInitExp()->getValueStr());
                }
            }
        }

        if (symbolTable.getSymbol(node.getValueStr(), node.getLine())) {
            errorDef(node.getLine(), node.getValueStr());
        }

        symbolTable.addVariableSymbol(node.getValueStr(), node.getVarType(), node.getLine());
        Symbol* symbol = symbolTable.getSymbol(node.getValueStr(), node.getLine());
        if (symbol == nullptr) {
            cout << "In Visit VarDecl symbol returned as nullptr, WTF?!" << endl;
        }
        printer.emitVar(node.getValueStr(), symbol->getDataType(), symbol->getOffset());


        node.getVarId()->accept(*this);
        if(node.getVarType() == BuiltInType::BYTE && node.getVarInitExp()->getType() == NODE_Num) {
            errorMismatch(node.getLine());
        }
        if (node.getVarInitExp()){
            if (!(node.getVarType() == BuiltInType::INT && node.getVarInitExp()->getType() == NODE_NumB)) {
                if ((node.getVarType() == BOOL && node.getVarInitExp()->getType() != NODE_Bool) ||
                    (node.getVarType() == STRING && node.getVarInitExp()->getType() != NODE_String) ||
                    (node.getVarType() == INT && node.getVarInitExp()->getType() != NODE_Num) ||
                    (node.getVarType() == BYTE && node.getVarInitExp()->getType() != NODE_NumB)) {
                    errorMismatch(node.getLine());
                }
            }
        }
    }

    void visit(ast::Assign& node) override {
        // printf("Get Symbol in %s\n", "Visit Assign");
        Symbol* var = symbolTable.getSymbol(node.getValueStr(), node.getLine());
        if (!var) {
            errorUndef(node.getLine(), node.getValueStr());
        }
        node.getAssignExp()->accept(*this);

        BuiltInType varType = var->getDataType();
        BuiltInType expType = BuiltInType::TYPE_ERROR;
        if (node.getAssignExp()->getType() == NODE_ID) {
            Symbol* expSymbol = symbolTable.getSymbol(node.getAssignExp()->getValueStr(), node.getAssignExp()->getLine());
            if (expSymbol == nullptr) {
                errorUndef(node.getAssignExp()->getLine(), node.getAssignExp()->getValueStr());
            }
            expType = expSymbol->getDataType();
        } else if (node.getAssignExp()->getType() == NODE_Num) {
            expType = BuiltInType::INT;
        } else if (node.getAssignExp()->getType() == NODE_NumB) {
            expType = BuiltInType::BYTE;
        } else if (node.getAssignExp()->getType() == NODE_Bool) {
            expType = BuiltInType::BOOL;
        } else if (node.getAssignExp()->getType() == NODE_String) {
            expType = BuiltInType::STRING;
        }
        
        if (varType != expType && !(varType == BuiltInType::INT && expType == BuiltInType::BYTE)) {
            errorMismatch(node.getLine());
        }
    }

    void visit(ast::Formal& node) override {
        // printf("Get Symbol in %s\n", "Visit Formal 1");
        if (symbolTable.getSymbol(node.getFormalId(), node.getLine())) {
            errorDef(node.getLine(), node.getFormalId());
        }

        symbolTable.addParameterSymbol(node.getFormalId(), node.getFormalType(), node.getLine());
        // printf("Get Symbol in %s\n", "Visit Formal 3");
        Symbol* symbol = symbolTable.getSymbol(node.getFormalId(), node.getLine());
        printer.emitVar(node.getFormalId(), node.getFormalType(), symbol->getOffset());
    }

    void visit(ast::Formals& node) override {
        for (auto& formal : node.getFormals()) {
            formal->accept(*this);
        }
    }

    void visit(ast::FuncDecl& node) override {
        vector<BuiltInType> paramsTypes = node.getFuncParams()->getFormalsType();
        vector<string> paramsIds = node.getFuncParams()->getFormalsIds();

        
        printer.emitFunc(node.getFuncId(), node.getFuncReturnType(), paramsTypes);

        beginScope(node.getFuncId(), false);
        node.getFuncParams()->accept(*this);
        node.getFuncBody()->accept(*this);
        endScope();
    }

    void visit(ast::Funcs& node) override {
        // The (this) is the ScopePrinter
        this->symbolTable.addFunctionSymbol("print", BuiltInType::VOID, {BuiltInType::STRING}, {"str"}, -1);
        this->symbolTable.addFunctionSymbol("printi", BuiltInType::VOID, {BuiltInType::INT}, {"num"}, -1);
        printer.emitFunc("print", BuiltInType::VOID, {BuiltInType::STRING});
        printer.emitFunc("printi", BuiltInType::VOID, {BuiltInType::INT});

        for (auto& funcDecl : node.getFuncs()) {
            this->symbolTable.addFunctionSymbol(funcDecl->getFuncId(), funcDecl->getFuncReturnType(), funcDecl->getFuncParams()->getFormalsType(), 
                funcDecl->getFuncParams()->getFormalsIds(), funcDecl->getLine());
        }

        if(symbolTable.getFuncSymbol("main", -1) == nullptr) {
            errorMainMissing();
        }

        for (auto& funcDecl : node.getFuncs()) {
            funcDecl->accept(*this);
        }
    }

    void printResults() {
        cout << printer;
    }
};

#endif // SEMANTIC_ANALYZER_HPP
