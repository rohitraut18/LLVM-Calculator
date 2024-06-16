#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/ExecutionEngine/GenericValue.h>

#include <iostream>
#include <memory>
#include <map>
#include <cstdio>
#include <cstdlib>


using namespace std;

// Token definitions
enum Token {
    tok_eof = -1,
    tok_number = -2,
    tok_plus = '+',
    tok_minus = '-',
    tok_multiply = '*',
    tok_divide = '/',
    tok_lparen = '(',
    tok_rparen = ')'
};

static string IdentifierStr;
static double NumVal;

// Lexer implementation
int gettok() {
    static int LastChar = ' ';

    // Skip any whitespace.
    while (isspace(LastChar))
        LastChar = getchar();

    // Handle numbers.
    if (isdigit(LastChar)) {
        string NumStr;
        do {
            NumStr += LastChar;
            LastChar = getchar();
        } while (isdigit(LastChar));

        NumVal = strtod(NumStr.c_str(), nullptr);
        return tok_number;
    }

    // Handle operators and parentheses.
    if (LastChar == '+' || LastChar == '-' || LastChar == '*' || LastChar == '/' || LastChar == '(' || LastChar == ')') {
        int ThisChar = LastChar;
        LastChar = getchar();
        return ThisChar;
    }

    // Handle end of file.
    if (LastChar == EOF)
        return tok_eof;

    return -1;  // Unknown character.
}

// AST Node Definitions
class ExprAST {
public:
    virtual ~ExprAST() = default;
    virtual llvm::Value *codegen() = 0;
};

class NumberExprAST : public ExprAST {
    double Val;

public:
    NumberExprAST(double Val) : Val(Val) {}
    llvm::Value *codegen() override;
};

class BinaryExprAST : public ExprAST {
    char Op;
    unique_ptr<ExprAST> LHS, RHS;

public:
    BinaryExprAST(char Op, unique_ptr<ExprAST> LHS, unique_ptr<ExprAST> RHS)
        : Op(Op), LHS(move(LHS)), RHS(move(RHS)) {}
    llvm::Value *codegen() override;
};

// Parser implementation
static int CurTok;

int getNextToken() {
    return CurTok = gettok();
}

unique_ptr<ExprAST> ParseExpression();

unique_ptr<ExprAST> ParseNumberExpr() {
    auto Result = make_unique<NumberExprAST>(NumVal);
    getNextToken();  // consume the number
    return move(Result);
}

unique_ptr<ExprAST> ParseParenExpr() {
    getNextToken();  // eat '('
    auto V = ParseExpression();
    if (!V)
        return nullptr;

    if (CurTok != ')')
        return nullptr;
    getNextToken();  // eat ')'
    return V;
}

unique_ptr<ExprAST> ParsePrimary() {
    switch (CurTok) {
    default:
        return nullptr;
    case tok_number:
        return ParseNumberExpr();
    case tok_lparen:
        return ParseParenExpr();
    }
}

int GetTokPrecedence() {
    if (CurTok == '+' || CurTok == '-')
        return 10;
    if (CurTok == '*' || CurTok == '/')
        return 20;
    return -1;
}

unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec, unique_ptr<ExprAST> LHS) {
    while (true) {
        int TokPrec = GetTokPrecedence();

        if (TokPrec < ExprPrec)
            return LHS;

        int BinOp = CurTok;
        getNextToken();  // eat binop

        auto RHS = ParsePrimary();
        if (!RHS)
            return nullptr;

        int NextPrec = GetTokPrecedence();
        if (TokPrec < NextPrec) {
            RHS = ParseBinOpRHS(TokPrec + 1, move(RHS));
            if (!RHS)
                return nullptr;
        }

        LHS = make_unique<BinaryExprAST>(BinOp, move(LHS), move(RHS));
    }
}

unique_ptr<ExprAST> ParseExpression() {
    auto LHS = ParsePrimary();
    if (!LHS)
        return nullptr;

    return ParseBinOpRHS(0, move(LHS));
}

// LLVM Code Generation
static llvm::LLVMContext TheContext;
static llvm::IRBuilder<> Builder(TheContext);
static unique_ptr<llvm::Module> TheModule;
static map<string, llvm::Value *> NamedValues;

llvm::Value *NumberExprAST::codegen() {
    return llvm::ConstantFP::get(TheContext, llvm::APFloat(Val));
}

llvm::Value *BinaryExprAST::codegen() {
    llvm::Value *L = LHS->codegen();
    llvm::Value *R = RHS->codegen();
    if (!L || !R)
        return nullptr;

    switch (Op) {
    case '+':
        return Builder.CreateFAdd(L, R, "addtmp");
    case '-':
        return Builder.CreateFSub(L, R, "subtmp");
    case '*':
        return Builder.CreateFMul(L, R, "multmp");
    case '/':
        return Builder.CreateFDiv(L, R, "divtmp");
    default:
        return nullptr;
    }
}

// Main Function
int main() {
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();

    TheModule = std::make_unique<llvm::Module>("calculator", TheContext);

    // Prime the first token.
    getNextToken();

    // Parse the expression.
    auto AST = ParseExpression();
    if (!AST) {
        std::cerr << "Error parsing expression!\n";
        return 1;
    }

    // Generate LLVM IR.
    if (llvm::Value *Val = AST->codegen()) {
        Val->print(llvm::errs());
        std::cout << "\n";
    } else {
        std::cerr << "Error generating code!\n";
        return 1;
    }

    // Create a JIT execution engine.
    std::string ErrStr;
    auto ExecutionEngine = llvm::EngineBuilder(std::move(TheModule)).setErrorStr(&ErrStr).create();
    if (!ExecutionEngine) {
        std::cerr << "Could not create ExecutionEngine: " << ErrStr << "\n";
        return 1;
    }

    // Get the function and execute it.
    auto *MainFunction = ExecutionEngine->FindFunctionNamed("main");
    if (!MainFunction) {
        std::cerr << "Could not find function: main\n";
        return 1;
    }

    // Execute the function and print the result.
    std::vector<llvm::GenericValue> Args;
    llvm::GenericValue GV = ExecutionEngine->runFunction(MainFunction, Args);
    std::cout << "Result: " << GV.DoubleVal << "\n";

    return 0;
}
