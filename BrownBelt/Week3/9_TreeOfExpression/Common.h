//
// Created by cobak on 24.01.2022.
//

#ifndef TASK_9_COMMON_H
#define TASK_9_COMMON_H

#include <memory>
#include <string>
using std::move;

// Базовый класс арифметического выражения
class Expression {
public:
    virtual ~Expression() = default;

    // Вычисляет значение выражения
    virtual int Evaluate() const = 0;

    // Форматирует выражение как строку
    // Каждый узел берётся в скобки, независимо от приоритета
    virtual std::string ToString() const = 0;
};

using ExpressionPtr = std::unique_ptr<Expression>;

#endif //TASK_9_COMMON_H
