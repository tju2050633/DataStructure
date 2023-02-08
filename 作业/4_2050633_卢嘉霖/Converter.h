#pragma once
#include <iostream>
#include "my_stl.h"

const int N = 50;

class Converter
{
private:
    my_std::stack<char> Operator;
    my_std::string Expression;
    bool soloNumber;
    char lastChar;

public:
    Converter();
    void run();
    bool isDigit(char c);
    bool topEquals(char c) const;
    char pop();
};

Converter::Converter()
{
    soloNumber = true;
    lastChar = ' ';
}

void Converter::run()
{
    char exp[N];
    std::cin.get(exp, N);

    char legalChars[] = "+-*/(). ";

    for (int i = 0; exp[i] != '\0'; i++)
    {
        // 检查输入字符合法性
        for (int j = 0; legalChars[j] != '\0'; j++)
        {
            if (exp[i] == legalChars[j] || isDigit(exp[i]))
            {
                break;
            }
            else if (legalChars[j + 1] == '\0')
            {
                std::cout << "非法字符" << exp[i] << std::endl;
                return;
            }
        }
        Expression.append(exp[i]);
    }

    int j = 0;
    while (j < Expression.length())
    {
        char c = Expression[j];
        if (isDigit(c) || c == '.') //数字直接输出
        {
            std::cout << c;
            if (j == Expression.length() - 1 && !soloNumber) //最后一位数字且不是仅有一个数字，需空格
                std::cout << ' ';
        }
        else //非数字
        {
            soloNumber = false;
            if (j != 0 && isDigit(Expression[j - 1])) //非数字的上一位是数字，需输出空格
            {
                std::cout << ' ';
            }

            if (c == '(') //左括号入栈
            {
                Operator.push('(');
            }
            else if (c == ')') //右括号，将栈顶元素输出直到遇到左括号
            {
                while (!topEquals('('))
                {
                    std::cout << pop() << ' ';
                }
                pop();
            }
            else if (c == '+' || c == '-') //加减号，将栈顶元素输出直到遇到左括号或栈空
            {
                if (j == 0 || lastChar == '(')
                {
                    if (c == '-') //负号才需要输出
                        std::cout << c;
                }
                else
                {
                    while (!Operator.empty() && !topEquals('('))
                    {
                        std::cout << pop() << ' ';
                    }
                    Operator.push(c);
                }
            }
            else if (c == '*' || c == '/') //乘除号，将栈顶元素输出直到遇到左括号或栈空或遇到加减号
            {
                while (!Operator.empty() && !topEquals('(') && !topEquals('+') && !topEquals('-'))
                {
                    std::cout << pop() << ' ';
                }
                Operator.push(c);
            }
        }

        if (c != ' ')
            lastChar = c;
        j++;
    }

    //输出剩余符号
    while (!Operator.empty())
    {
        std::cout << pop();
        if (!Operator.empty()) //最后一个符号不需要空格
        {
            std::cout << ' ';
        }
    }
}

bool Converter::isDigit(char c)
{
    return c >= '0' && c <= '9';
}

bool Converter::topEquals(char c) const
{
    if (Operator.empty())
    {
        return false;
    }
    return Operator.top() == c;
}

char Converter::pop()
{
    if (Operator.empty())
    {
        std::cerr << "表达式非法" << std::endl;
    }
    char c = Operator.top();
    Operator.pop();
    return c;
}