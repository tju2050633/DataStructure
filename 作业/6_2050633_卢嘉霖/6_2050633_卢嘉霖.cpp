#include "Tree.h"

void Welcome()
{
    std::cout << "**            ���׹���ϵͳ                   **" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "**         ��ѡ��Ҫִ�еĲ�����              **" << std::endl;
    std::cout << "**         A --- ���Ƽ���                    **" << std::endl;
    std::cout << "**         B --- ��Ӽ�ͥ��Ա                **" << std::endl;
    std::cout << "**         C --- ��ɢ�ֲ���ͥ                **" << std::endl;
    std::cout << "**         D --- ���ļ�ͥ��Ա����            **" << std::endl;
    std::cout << "**         E --- �˳�����                    **" << std::endl;
    std::cout << "===============================================" << std::endl;
}

char GetChar()
{
    char ch;
    std::cin >> ch;
    std::cin.ignore(INT_MAX, '\n');

    //Сдת��д
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
        std::cout << "��ѡ��Ҫִ�еĲ�����";
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
            std::cout << "�����������������" << std::endl;
            break;
        }
    }

    return 0;
}