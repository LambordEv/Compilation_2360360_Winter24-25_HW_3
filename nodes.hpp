#ifndef NODES_HPP
#define NODES_HPP

#include <memory>
#include <string>
#include <vector>
#include "visitor.hpp"

namespace ast {

    enum SemanticNodeType {
        NODE_Undecided = -1,
        NODE_Exp,
        NODE_Statement,
        NODE_Num,
        NODE_NumB,
        NODE_String,
        NODE_Bool,
        NODE_ID,
        NODE_BinOP,
        NODE_RelOP,
        NODE_Not,
        NODE_And,
        NODE_Or,
        NODE_Type,
        NODE_Cast,
        NODE_ExpList,
        NODE_Call,
        NODE_Statements,
        NODE_Break,
        NODE_Continue,
        NODE_Return,
        NODE_If,
        NODE_While,
        NODE_VarDecl,
        NODE_Assign,
        NODE_Formal,
        NODE_Formals,
        NODE_FuncDecl,
        NODE_Funcs
    };

    /* Arithmetic operations */
    enum BinOpType {
        BIN_ERROR = -1,
        ADD, // Addition
        SUB, // Subtraction
        MUL, // Multiplication
        DIV  // Division
    };

    /* Relational operations */
    enum RelOpType {
        REL_ERROR = -1,
        EQ, // Equal
        NE, // Not equal
        LT, // Less than
        GT, // Greater than
        LE, // Less than or equal
        GE  // Greater than or equal
    };

    /* Built-in types */
    enum BuiltInType {
        TYPE_ERROR = -1,
        VOID,
        BOOL,
        BYTE,
        INT,
        STRING
    };

    /* Base class for all AST nodes */
    class Node {
    protected:
        SemanticNodeType nodeType = NODE_Undecided;
    public:
        // Line number in the source code
        int line;
        std::string text;

        // Use this constructor only while parsing in bison or flex
        Node();
        int getLine() const { return line; }
        std::string getText() const { return text; }
        SemanticNodeType getType() const { return nodeType; }
        virtual void setType(SemanticNodeType newType) { this->nodeType = newType; }
        // Accept method for visitor pattern
        virtual void accept(Visitor &visitor) = 0;
    };

    /* Base class for all expressions */
    class Exp : virtual public Node {
    public:
        Exp() = default;
    };

    /* Base class for all statements */
    class Statement : virtual public Node { 

    };

    /* Number literal */
    class Num : public Exp {
    public:
        // Value of the number
        int value;

        // Constructor that receives a C-style string that represents the number
        explicit Num(std::string str);
        int getValue() const { return value; }
        void accept(Visitor &visitor) override {
            visitor.visit(*this);
        }
    };

    /* Byte literal */
    class NumB : public Exp {
    public:
        // Value of the number
        int value;

        // Constructor that receives a C-style (including b character) string that represents the number
        explicit NumB(std::string str);
        int getValue() const { return value; }
        void accept(Visitor &visitor) override {
            visitor.visit(*this);
        }
    };

    /* String literal */
    class String : public Exp {
    public:
        // Value of the string
        std::string value;

        // Constructor that receives a C-style string that represents the string *including quotes*
        explicit String(std::string str);
        std::string getValue() const { return value; }
        void accept(Visitor &visitor) override {
            visitor.visit(*this);
        }
    };

    /* Boolean literal */
    class Bool : public Exp {
    public:
        // Value of the boolean
        bool value;

        // Constructor that receives the boolean value
        explicit Bool(bool value);
        bool getValue() const { return value; }
        void accept(Visitor &visitor) override {
            visitor.visit(*this);
        }
    };

    /* Identifier */
    class ID : public Exp {
    public:
        // Name of the identifier
        std::string value;

        // Constructor that receives a C-style string that represents the identifier
        explicit ID(std::string str);
        std::string getValue() const { return value; }
        void accept(Visitor &visitor) override {
            visitor.visit(*this);
        }
    };

    /* Binary arithmetic operation */
    class BinOp : public Exp {
    public:
        // Left operand
        std::shared_ptr<Exp> left;
        // Right operand
        std::shared_ptr<Exp> right;
        // Operation
        BinOpType op;
        BuiltInType resultType = TYPE_ERROR;

        // Constructor that receives the left and right operands and the operation
        BinOp(BinOpType op, std::shared_ptr<Exp> left = nullptr, std::shared_ptr<Exp> right = nullptr);
        std::shared_ptr<Exp> getLeft() const { return left; }
        std::shared_ptr<Exp> getRight() const { return right; }
        BinOpType getOp() const { return op; }
        void accept(Visitor &visitor) override {
            visitor.visit(*this);
        }
    };

    /* Binary relational operation */
    class RelOp : public Exp {
    public:
        // Left operand
        std::shared_ptr<Exp> left;
        // Right operand
        std::shared_ptr<Exp> right;
        // Operation
        RelOpType op;
        BuiltInType resultType = TYPE_ERROR;

        // Constructor that receives the left and right operands and the operation
        RelOp(RelOpType op, std::shared_ptr<Exp> left = nullptr, std::shared_ptr<Exp> right = nullptr);
        std::shared_ptr<Exp> getLeft() const { return left; }
        std::shared_ptr<Exp> getRight() const { return right; }
        RelOpType getOp() const { return op; }
        void accept(Visitor &visitor) override {
            visitor.visit(*this);
        }
    };

    /* Unary logical NOT operation */
    class Not : public Exp {
    public:
        // Operand
        std::shared_ptr<Exp> exp;
        BuiltInType resultType = TYPE_ERROR;

        // Constructor that receives the operand
        explicit Not(std::shared_ptr<Exp> exp);
        std::shared_ptr<Exp> getExpr() const { return exp; }
        void accept(Visitor &visitor) override {
            visitor.visit(*this);
        }
    };

    /* Binary logical AND operation */
    class And : public Exp {
    public:
        // Left operand
        std::shared_ptr<Exp> left;
        // Right operand
        std::shared_ptr<Exp> right;
        BuiltInType resultType = TYPE_ERROR;

        // Constructor that receives the left and right operands
        And(std::shared_ptr<Exp> left, std::shared_ptr<Exp> right);
        std::shared_ptr<Exp> getLeft() const { return left; }
        std::shared_ptr<Exp> getRight() const { return right; }
        void accept(Visitor &visitor) override {
            visitor.visit(*this);
        }
    };

    /* Binary logical OR operation */
    class Or : public Exp {
    public:
        // Left operand
        std::shared_ptr<Exp> left;
        // Right operand
        std::shared_ptr<Exp> right;
        BuiltInType resultType = TYPE_ERROR;

        // Constructor that receives the left and right operands
        Or(std::shared_ptr<Exp> left, std::shared_ptr<Exp> right);
        std::shared_ptr<Exp> getLeft() const { return left; }
        std::shared_ptr<Exp> getRight() const { return right; }
        void accept(Visitor &visitor) override {
            visitor.visit(*this);
        }
    };

    /* Type symbol */
    class Type : public Node {
    public:
        // Type
        BuiltInType type;

        // Constructor that receives the type
        explicit Type(BuiltInType type);
        BuiltInType getTypeOfType() const { return type; }
        void accept(Visitor &visitor) override {
            visitor.visit(*this);
        }
    };

    /* Type cast */
    class Cast : public Exp {
    public:
        // Expression to be cast
        std::shared_ptr<Exp> exp;
        // Target type
        std::shared_ptr<Type> target_type;

        // Constructor that receives the expression and the target type
        Cast(std::shared_ptr<Exp> exp, std::shared_ptr<Type> type);
        std::shared_ptr<Exp> getExpr() const { return exp; }
        BuiltInType getTargetType() const { return target_type->getTypeOfType(); }
        void accept(Visitor &visitor) override {
            visitor.visit(*this);
        }
    };

    /* List of expressions */
    class ExpList : public Node {
    public:
        // List of expressions
        std::vector<std::shared_ptr<Exp>> exps;

        // Constructor that receives no expressions
        ExpList() = default;

        // Constructor that receives the first expression
        explicit ExpList(std::shared_ptr<Exp> exp);

        // Method to add an expression at the beginning of the list
        void push_front(const std::shared_ptr<Exp> &exp);

        // Method to add an expression at the end of the list
        void push_back(const std::shared_ptr<Exp> &exp);

        std::vector<std::shared_ptr<Exp>> getExpressions() const { return exps; }

        // std::vector<BuiltInType> getExpListType() const {
            // std::vector<BuiltInType> types;
            // for(auto& exp : exps) {
            //     types.push_back(exp->getType());
            // }
            // return types;
        // }

        void accept(Visitor &visitor) override {
            visitor.visit(*this);
        }
    };

    /* Function call */
    class Call : public Exp, public Statement {
    public:
        // Function identifier
        std::shared_ptr<ID> func_id;
        // List of arguments as expressions
        std::shared_ptr<ExpList> args;

        // Constructor that receives the function identifier and the list of arguments
        Call(std::shared_ptr<ID> func_id, std::shared_ptr<ExpList> args);

        // Constructor that receives only the function identifier (for parameterless functions)
        explicit Call(std::shared_ptr<ID> func_id);

        std::string getFuncId() const { return func_id->getValue(); }

        std::shared_ptr<ExpList> getArgs() const { return args; }

        void accept(Visitor &visitor) override {
            visitor.visit(*this);
        }
    };

    /* List of statements */
    class Statements : public Statement {
    public:
        // List of statements
        std::vector<std::shared_ptr<Statement>> statements;

        // Constructor that receives no statements
        Statements() = default;

        // Constructor that receives the first statement
        explicit Statements(std::shared_ptr<Statement> statement);

        // Method to add a statement at the beginning of the list
        void push_front(const std::shared_ptr<Statement> &statement);

        // Method to add a statement at the end of the list
        void push_back(const std::shared_ptr<Statement> &statement);


        std::vector<std::shared_ptr<Statement>> getStatements() const { return statements; }

        void accept(Visitor &visitor) override {
            visitor.visit(*this);
        }
    };

    /* Break statement */
    class Break : public Statement {
        void accept(Visitor &visitor) override {
            visitor.visit(*this);
        }
    };

    /* Continue statement */
    class Continue : public Statement {
        void accept(Visitor &visitor) override {
            visitor.visit(*this);
        }
    };

    /* Return statement */
    class Return : public Statement {
    public:
        // Expression to be returned. If the return is expressionless, this field is nullptr
        std::shared_ptr<Exp> exp;

        // Constructor that receives the expression to be returned
        explicit Return(std::shared_ptr<Exp> exp = nullptr);

        std::shared_ptr<Exp> getExpr() const { return exp; }
        void accept(Visitor &visitor) override {
            visitor.visit(*this);
        }
    };

    /* If statement */
    class If : public Statement {
    public:
        // Condition expression
        std::shared_ptr<Exp> condition;
        // Statement to be executed if the condition is true
        std::shared_ptr<Statement> then;
        // Statement to be executed if the condition is false. For an if statement without else, this field is nullptr
        std::shared_ptr<Statement> otherwise;

        // Constructor that receives the condition, the statement to be executed if the condition is true, and the statement to be executed if the condition is false
        If(std::shared_ptr<Exp> condition, std::shared_ptr<Statement> then,
           std::shared_ptr<Statement> otherwise = nullptr);

        std::shared_ptr<Exp> getCondition() const { return condition; }
        std::shared_ptr<Statement> getThen() const { return then; }
        std::shared_ptr<Statement> getElse() const { return otherwise; }

        void accept(Visitor &visitor) override {
            visitor.visit(*this);
        }
    };

    /* While statement */
    class While : public Statement {
    public:
        // Condition expression
        std::shared_ptr<Exp> condition;
        // Statement to be executed while the condition is true
        std::shared_ptr<Statement> body;

        // Constructor that receives the condition and the statement to be executed while the condition is true
        While(std::shared_ptr<Exp> condition, std::shared_ptr<Statement> body);

        std::shared_ptr<Exp> getCondition() const { return condition; }
        std::shared_ptr<Statement> getBody() const { return body; }

        void accept(Visitor &visitor) override {
            visitor.visit(*this);
        }
    };

    /* Variable declaration */
    class VarDecl : public Statement {
    public:
        // Identifier of the variable
        std::shared_ptr<ID> id;
        // Type of the variable
        std::shared_ptr<Type> type;
        // Initial value of the variable. If the variable is not initialized, this field is nullptr
        std::shared_ptr<Exp> init_exp;

        // Constructor that receives the identifier, the type, and the initial value expression
        VarDecl(std::shared_ptr<ID> id, std::shared_ptr<Type> type, std::shared_ptr<Exp> init_exp = nullptr);

        std::string getVarId() const { return id->getValue(); }
        BuiltInType getVarType() const { return type->getTypeOfType(); }
        std::shared_ptr<Exp> getVarInitExp() const { return init_exp; }

        void accept(Visitor &visitor) override {
            visitor.visit(*this);
        }
    };

    /* Assignment statement */
    class Assign : public Statement {
    public:
        // Identifier of the variable
        std::shared_ptr<ID> id;
        // Expression to be assigned
        std::shared_ptr<Exp> exp;

        // Constructor that receives the identifier and the expression to be assigned
        Assign(std::shared_ptr<ID> id, std::shared_ptr<Exp> exp);

        std::string getAssignId() const { return id->getValue(); }
        std::shared_ptr<Exp> getAssignExp() const { return exp; }

        void accept(Visitor &visitor) override {
            visitor.visit(*this);
        }
    };

    /* Formal parameter */
    class Formal : public Node {
    public:
        // Identifier of the parameter
        std::shared_ptr<ID> id;
        // Type of the parameter
        std::shared_ptr<Type> type;

        // Constructor that receives the identifier and the type
        Formal(std::shared_ptr<ID> id, std::shared_ptr<Type> type);

        std::string getFormalId() const { return id->getValue(); }
        BuiltInType getFormalType() const { 
            return type->getTypeOfType(); }

        void accept(Visitor &visitor) override {
            visitor.visit(*this);
        }
    };

    /* List of formal parameters */
    class Formals : public Node {
    public:
        // List of formal parameters
        std::vector<std::shared_ptr<Formal>> formals;

        // Constructor that receives no parameters
        Formals() = default;

        // Constructor that receives the first formal parameter
        explicit Formals(std::shared_ptr<Formal> formal);

        // Method to add a formal parameter at the beginning of the list
        void push_front(const std::shared_ptr<Formal> &formal);

        // Method to add a formal parameter at the end of the list
        void push_back(const std::shared_ptr<Formal> &formal);

        std::vector<std::shared_ptr<Formal>> getFormals() const { return formals; }

        // Method to get a vector of formal parameter IDs
        std::vector<std::string> getFormalsIds() const {
            std::vector<std::string> ids;
            for (const auto &formal : formals) {
                ids.push_back(formal->getFormalId());
            }
            return ids;
        }

        // Method to get a vector of formal parameter types
        std::vector<BuiltInType> getFormalsType() const {
            std::vector<BuiltInType> types;
            for (const auto &formal : formals) {
                types.push_back(formal->getFormalType());
            }
            return types;
        }

        void accept(Visitor &visitor) override {
            visitor.visit(*this);
        }
    };

    /* Function declaration */
    class FuncDecl : public Node {
    public:
        // Identifier of the function
        std::shared_ptr<ID> id;
        // Return type of the function
        std::shared_ptr<Type> return_type;
        // List of formal parameters
        std::shared_ptr<Formals> formals;
        // Body of the function
        std::shared_ptr<Statements> body;

        // Constructor that receives the identifier, the return type, the list of formal parameters, and the body
        FuncDecl(std::shared_ptr<ID> id, std::shared_ptr<Type> return_type, std::shared_ptr<Formals> formals,
                 std::shared_ptr<Statements> body);

        std::string getFuncId() const { return id->getValue(); }
        BuiltInType getFuncReturnType() const { return return_type->getTypeOfType(); }
        std::shared_ptr<Formals> getFuncParams() const { return formals; }
        std::shared_ptr<Statements> getFuncBody() const { return body; }

        void accept(Visitor &visitor) override {
            visitor.visit(*this);
        }
    };

    /* List of function declarations */
    class Funcs : public Node {
    public:
        // List of function declarations
        std::vector<std::shared_ptr<FuncDecl>> funcs;

        // Constructor that receives no function declarations
        Funcs() = default;

        // Constructor that receives the first function declaration
        explicit Funcs(std::shared_ptr<FuncDecl> func);

        // Method to add a function declaration at the beginning of the list
        void push_front(const std::shared_ptr<FuncDecl> &func);

        // Method to add a function declaration at the end of the list
        void push_back(const std::shared_ptr<FuncDecl> &func);

        std::vector<std::shared_ptr<FuncDecl>> getFuncs() const { return funcs; }

        void accept(Visitor &visitor) override {
            visitor.visit(*this);
            // This is the root of the program, here is the global scope
            // Add to Visitor.SymbolTable.GlobalScope the function name and its return type


            // Continue with the visit - visit the function parameters and the function body, which are the inner scopes
            
        }
    };
}

#define YYSTYPE std::shared_ptr<ast::Node>

#endif //NODES_HPP
