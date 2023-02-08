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
        // ��������ַ��Ϸ���
        for (int j = 0; legalChars[j] != '\0'; j++)
        {
            if (exp[i] == legalChars[j] || isDigit(exp[i]))
            {
                break;
            }
            else if (legalChars[j + 1] == '\0')
            {
                std::cout << "�Ƿ��ַ�" << exp[i] << std::endl;
                return;
            }
        }
        Expression.append(exp[i]);
    }

    int j = 0;
    while (j < Expression.length())
    {
        char c = Expression[j];
        if (isDigit(c) || c == '.') //����ֱ�����
        {
            std::cout << c;
            if (j == Expression.length() - 1 && !soloNumber) //���һλ�����Ҳ��ǽ���һ�����֣���ո�
                std::cout << ' ';
        }
        else //������
        {
            soloNumber = false;
            if (j != 0 && isDigit(Expression[j - 1])) //�����ֵ���һλ�����֣�������ո�
            {
                std::cout << ' ';
            }

            if (c == '(') //��������ջ
            {
                Operator.push('(');
            }
            else if (c == ')') //�����ţ���ջ��Ԫ�����ֱ������������
            {
                while (!topEquals('('))
                {
                    std::cout << pop() << ' ';
                }
                pop();
            }
            else if (c == '+' || c == '-') //�Ӽ��ţ���ջ��Ԫ�����ֱ�����������Ż�ջ��
            {
                if (j == 0 || lastChar == '(')
                {
                    if (c == '-') //���Ų���Ҫ���
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
            else if (c == '*' || c == '/') //�˳��ţ���ջ��Ԫ�����ֱ�����������Ż�ջ�ջ������Ӽ���
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

    //���ʣ�����
    while (!Operator.empty())
    {
        std::cout << pop();
        if (!Operator.empty()) //���һ�����Ų���Ҫ�ո�
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
        std::cerr << "���ʽ�Ƿ�" << std::endl;
    }
    char c = Operator.top();
    Operator.pop();
    return c;
}