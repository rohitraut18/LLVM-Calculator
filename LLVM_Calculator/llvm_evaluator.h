#ifndef LLVM_EVALUATOR_H
#define LLVM_EVALUATOR_H

#include <string>

class LLVM_Evaluator {
public:
    LLVM_Evaluator();
    double evaluateExpression(const std::string &expression);
};

#endif // LLVM_EVALUATOR_H
