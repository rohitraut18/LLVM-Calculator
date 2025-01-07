// llvm_evaluator.cpp
#include "llvm_evaluator.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/ExecutionEngine/GenericValue.h"

#include <iostream>

LLVM_Evaluator::LLVM_Evaluator() {
    // Initialize LLVM components
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();
}

double LLVM_Evaluator::evaluateExpression(const std::string &expression) {
    llvm::LLVMContext context;
    llvm::IRBuilder<> builder(context);
    llvm::Module *module = new llvm::Module("expr_module", context);

    // For simplicity, hardcoded 42.0 value as a placeholder for evaluation logic
    llvm::FunctionType *funcType = llvm::FunctionType::get(builder.getDoubleTy(), false);
    llvm::Function *func = llvm::Function::Create(funcType, llvm::GlobalValue::ExternalLinkage, "evaluate_expr", module);

    llvm::BasicBlock *entry = llvm::BasicBlock::Create(context, "entry", func);
    builder.SetInsertPoint(entry);

    llvm::Value *result = llvm::ConstantFP::get(context, llvm::APFloat(42.0)); // Placeholder result
    builder.CreateRet(result);

    std::string errStr;
    llvm::ExecutionEngine *engine = llvm::EngineBuilder(std::unique_ptr<llvm::Module>(module))
                                        .setErrorStr(&errStr)
                                        .create();
    if (!engine) {
        std::cerr << "Error creating execution engine: " << errStr << std::endl;
        return -1.0;
    }

    std::vector<llvm::GenericValue> args;
    llvm::GenericValue gv = engine->runFunction(func, args);

    return gv.DoubleVal;
}
