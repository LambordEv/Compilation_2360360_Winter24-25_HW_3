#include "output.hpp"
#include <iostream>

namespace output {
    static const std::string child_prefix = "├──";
    static const std::string last_child_prefix = "└──";
    static const std::string child_indent = "│   ";
    static const std::string last_child_indent = "    ";
    
    /* Helper functions */

    static std::string toString(ast::BuiltInType type) {
        switch (type) {
            case ast::BuiltInType::INT:
                return "int";
            case ast::BuiltInType::BOOL:
                return "bool";
            case ast::BuiltInType::BYTE:
                return "byte";
            case ast::BuiltInType::VOID:
                return "void";
            case ast::BuiltInType::STRING:
                return "string";
            default:
                return "unknown";
        }
    }

    /* Error handling functions */

    void errorLex(int lineno) {
        std::cout << "line " << lineno << ": lexical error\n";
        exit(0);
    }

    void errorSyn(int lineno) {
        std::cout << "line " << lineno << ": syntax error\n";
        exit(0);
    }

    void errorUndef(int lineno, const std::string &id) {
        std::cout << "line " << lineno << ":" << " variable " << id << " is not defined" << std::endl;
        exit(0);
    }

    void errorDefAsFunc(int lineno, const std::string &id) {
        std::cout << "line " << lineno << ":" << " symbol " << id << " is a function" << std::endl;
        exit(0);
    }

    void errorDefAsVar(int lineno, const std::string &id) {
        std::cout << "line " << lineno << ":" << " symbol " << id << " is a variable" << std::endl;
        exit(0);
    }

    void errorDef(int lineno, const std::string &id) {
        std::cout << "line " << lineno << ":" << " symbol " << id << " is already defined" << std::endl;
        exit(0);
    }

    void errorUndefFunc(int lineno, const std::string &id) {
        std::cout << "line " << lineno << ":" << " function " << id << " is not defined" << std::endl;
        exit(0);
    }

    void errorMismatch(int lineno) {
        std::cout << "line " << lineno << ":" << " type mismatch" << std::endl;
        exit(0);
    }

    void errorPrototypeMismatch(int lineno, const std::string &id, std::vector<std::string> &paramTypes) {
        std::cout << "line " << lineno << ": prototype mismatch, function " << id << " expects parameters (";

        for (int i = 0; i < paramTypes.size(); ++i) {
            std::cout << paramTypes[i];
            if (i != paramTypes.size() - 1)
                std::cout << ",";
        }

        std::cout << ")" << std::endl;
        exit(0);
    }

    void errorUnexpectedBreak(int lineno) {
        std::cout << "line " << lineno << ":" << " unexpected break statement" << std::endl;
        exit(0);
    }

    void errorUnexpectedContinue(int lineno) {
        std::cout << "line " << lineno << ":" << " unexpected continue statement" << std::endl;
        exit(0);
    }

    void errorMainMissing() {
        std::cout << "Program has no 'void main()' function" << std::endl;
        exit(0);
    }

    void errorByteTooLarge(int lineno, const int value) {
        std::cout << "line " << lineno << ": byte value " << value << " out of range" << std::endl;
        exit(0);
    }


    /* PrintVisitor class */

    PrintVisitor::PrintVisitor() : indents({last_child_indent}), prefixes({last_child_prefix}) {}

    void PrintVisitor::print_indented(const std::string &str) {
        for (auto it = indents.begin(); it != indents.end() - 1; ++it) {
            std::cout << *it;
        }
        std::cout << prefixes.back() << str << std::endl;
    }

    void PrintVisitor::enter_child() {
        indents.emplace_back(child_indent);
        prefixes.emplace_back(child_prefix);
    }

    void PrintVisitor::enter_last_child() {
        indents.emplace_back(last_child_indent);
        prefixes.emplace_back(last_child_prefix);
    }

    void PrintVisitor::leave_child() {
        indents.pop_back();
        prefixes.pop_back();
    }

    void PrintVisitor::visit(ast::Num &node) {
        print_indented("Num: " + std::to_string(node.value));
    }

    void PrintVisitor::visit(ast::NumB &node) {
        print_indented("NumB: " + std::to_string(node.value));
    }

    void PrintVisitor::visit(ast::String &node) {
        print_indented("String: " + node.value);
    }

    void PrintVisitor::visit(ast::Bool &node) {
        print_indented("Bool: " + std::string((node.value ? "true" : "false")));
    }

    void PrintVisitor::visit(ast::ID &node) {
        print_indented("ID: " + node.value);
    }

    void PrintVisitor::visit(ast::BinOp &node) {
        std::string op;

        switch (node.op) {
            case ast::BinOpType::ADD:
                op = "+";
                break;
            case ast::BinOpType::SUB:
                op = "-";
                break;
            case ast::BinOpType::MUL:
                op = "*";
                break;
            case ast::BinOpType::DIV:
                op = "/";
                break;
        }

        print_indented("BinOp: " + op);

        enter_child();
        node.left->accept(*this);
        leave_child();

        enter_last_child();
        node.right->accept(*this);
        leave_child();
    }

    void PrintVisitor::visit(ast::RelOp &node) {
        std::string op;

        switch (node.op) {
            case ast::RelOpType::EQ:
                op = "==";
                break;
            case ast::RelOpType::NE:
                op = "!=";
                break;
            case ast::RelOpType::LT:
                op = "<";
                break;
            case ast::RelOpType::LE:
                op = "<=";
                break;
            case ast::RelOpType::GT:
                op = ">";
                break;
            case ast::RelOpType::GE:
                op = ">=";
                break;
        }

        print_indented("RelOp: " + op);

        enter_child();
        node.left->accept(*this);
        leave_child();


        enter_last_child();
        node.right->accept(*this);
        leave_child();
    }

    void PrintVisitor::visit(ast::Type &node) {
        print_indented("Type: " + toString(node.type));
    }

    void PrintVisitor::visit(ast::Cast &node) {
        print_indented("Cast");

        enter_child();
        node.exp->accept(*this);
        leave_child();

        enter_last_child();
        node.target_type->accept(*this);
        leave_child();
    }

    void PrintVisitor::visit(ast::Not &node) {
        print_indented("Not");

        enter_last_child();
        node.exp->accept(*this);
        leave_child();
    }

    void PrintVisitor::visit(ast::And &node) {
        print_indented("And");

        enter_child();
        node.left->accept(*this);
        leave_child();

        enter_last_child();
        node.right->accept(*this);
        leave_child();
    }

    void PrintVisitor::visit(ast::Or &node) {
        print_indented("Or");

        enter_child();
        node.left->accept(*this);
        leave_child();

        enter_last_child();
        node.right->accept(*this);
        leave_child();
    }

    void PrintVisitor::visit(ast::ExpList &node) {
        print_indented("ExpList");

        for (auto it = node.exps.rbegin(); it != node.exps.rend(); ++it) {
            if (it != node.exps.rend() - 1) {
                enter_child();
            } else {
                enter_last_child();
            }
            (*it)->accept(*this);
            leave_child();
        }
    }

    void PrintVisitor::visit(ast::Call &node) {
        print_indented("Call");

        enter_child();
        node.func_id->accept(*this);
        leave_child();

        enter_last_child();
        node.args->accept(*this);
        leave_child();
    }

    void PrintVisitor::visit(ast::Statements &node) {
        print_indented("Statements");

        for (auto it = node.statements.begin(); it != node.statements.end(); ++it) {
            if (it != node.statements.end() - 1) {
                enter_child();
            } else {
                enter_last_child();
            }
            (*it)->accept(*this);
            leave_child();
        }
    }

    void PrintVisitor::visit(ast::Break &node) {
        print_indented("Break");
    }

    void PrintVisitor::visit(ast::Continue &node) {
        print_indented("Continue");
    }

    void PrintVisitor::visit(ast::Return &node) {
        print_indented("Return");

        if (node.exp) {
            enter_last_child();
            node.exp->accept(*this);
            leave_child();
        }
    }

    void PrintVisitor::visit(ast::If &node) {
        print_indented("If");

        enter_child();
        node.condition->accept(*this);
        leave_child();

        if (node.otherwise) {
            enter_child();
        } else {
            enter_last_child();
        }
        node.then->accept(*this);
        leave_child();

        if (node.otherwise) {
            enter_last_child();
            node.otherwise->accept(*this);
            leave_child();
        }
    }

    void PrintVisitor::visit(ast::While &node) {
        print_indented("While");

        enter_child();
        node.condition->accept(*this);
        leave_child();

        enter_last_child();
        node.body->accept(*this);
        leave_child();
    }

    void PrintVisitor::visit(ast::VarDecl &node) {
        print_indented("VarDecl");

        enter_child();
        node.id->accept(*this);
        leave_child();

        if (node.init_exp) {
            enter_child();
        } else {
            enter_last_child();
        }
        node.type->accept(*this);
        leave_child();

        if (node.init_exp) {
            enter_last_child();
            node.init_exp->accept(*this);
            leave_child();
        }
    }

    void PrintVisitor::visit(ast::Assign &node) {
        print_indented("Assign");

        enter_child();
        node.id->accept(*this);
        leave_child();

        enter_last_child();
        node.exp->accept(*this);
        leave_child();
    }

    void PrintVisitor::visit(ast::Formal &node) {
        print_indented("Formal");

        enter_child();
        node.id->accept(*this);
        leave_child();

        enter_last_child();
        node.type->accept(*this);
        leave_child();
    }

    void PrintVisitor::visit(ast::Formals &node) {
        print_indented("Formals");

        for (auto it = node.formals.rbegin(); it != node.formals.rend(); ++it) {
            if (it != node.formals.rend() - 1) {
                enter_child();
            } else {
                enter_last_child();
            }
            (*it)->accept(*this);
            leave_child();
        }
    }

    void PrintVisitor::visit(ast::FuncDecl &node) {
        print_indented("FuncDecl");

        enter_child();
        node.id->accept(*this);
        leave_child();

        enter_child();
        node.return_type->accept(*this);
        leave_child();

        enter_child();
        node.formals->accept(*this);
        leave_child();

        enter_last_child();
        node.body->accept(*this);
        leave_child();
    }

    void PrintVisitor::visit(ast::Funcs &node) {
        print_indented("Funcs");

        for (auto it = node.funcs.begin(); it != node.funcs.end(); ++it) {
            if (it != node.funcs.end() - 1) {
                enter_child();
            } else {
                enter_last_child();
            }
            (*it)->accept(*this);
            leave_child();
        }
    }


    /* ScopePrinter class */

    ScopePrinter::ScopePrinter() : indentLevel(0) {}

    std::string ScopePrinter::indent() const {
        std::string result;
        for (int i = 0; i < indentLevel; ++i) {
            result += "  ";
        }
        return result;
    }

    void ScopePrinter::beginScope() {
        indentLevel++;
        buffer << indent() << "---begin scope---" << std::endl;
    }

    void ScopePrinter::endScope() {
        buffer << indent() << "---end scope---" << std::endl;
        indentLevel--;
    }

    void ScopePrinter::emitVar(const std::string &id, const ast::BuiltInType &type, int offset) {
        buffer << indent() << id << " " << toString(type) << " " << offset << std::endl;
    }

    void ScopePrinter::emitFunc(const std::string &id, const ast::BuiltInType &returnType,
                                const std::vector<ast::BuiltInType> &paramTypes) {
        globalsBuffer << id << " " << "(";

        for (int i = 0; i < paramTypes.size(); ++i) {
            globalsBuffer << toString(paramTypes[i]);
            if (i != paramTypes.size() - 1)
                globalsBuffer << ",";
        }

        globalsBuffer << ")" << " -> " << toString(returnType) << std::endl;
    }

    std::ostream &operator<<(std::ostream &os, const ScopePrinter &printer) {
        os << "---begin global scope---" << std::endl;
        os << printer.globalsBuffer.str();
        os << printer.buffer.str();
        os << "---end global scope---" << std::endl;
        return os;
    }
}
