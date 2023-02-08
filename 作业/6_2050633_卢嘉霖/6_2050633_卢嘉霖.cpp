#include "Tree.h"

void Welcome()
{
    std::cout << "**            家谱管理系统                   **" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "**         请选择要执行的操作：              **" << std::endl;
    std::cout << "**         A --- 完善家谱                    **" << std::endl;
    std::cout << "**         B --- 添加家庭成员                **" << std::endl;
    std::cout << "**         C --- 解散局部家庭                **" << std::endl;
    std::cout << "**         D --- 更改家庭成员姓名            **" << std::endl;
    std::cout << "**         E --- 退出程序                    **" << std::endl;
    std::cout << "===============================================" << std::endl;
}

char GetChar()
{
    char ch;
    std::cin >> ch;
    std::cin.ignore(INT_MAX, '\n');

    //小写转大写
    if (ch >= 'a' && ch <= 'z')
    {
        ch -= 32;
    }

    return ch;
}

int main()
{
    Welcome();

    char option;
    Tree tree;
    while (true)
    {
        std::cout << "请选择要执行的操作：";
        option = GetChar();
        switch (option)
        {
        case 'A':
            tree.AddFamily();
            break;
        case 'B':
            tree.AddMember();
            break;
        case 'C':
            tree.RemoveFamily();
            break;
        case 'D':
            tree.ModifyName();
            break;
        case 'E':
            return 0;
        default:
            std::cout << "输入错误，请重新输入" << std::endl;
            break;
        }
    }

    return 0;
}