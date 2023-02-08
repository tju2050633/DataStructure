#include "Net.h"

void Welcome()
{
    std::cout << "**            ????????????               **" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "**         A --- ????????????                **" << std::endl;
    std::cout << "**         B --- ??????????                **" << std::endl;
    std::cout << "**         C --- ??????§³??????              **" << std::endl;
    std::cout << "**         D --- ?????§³??????              **" << std::endl;
    std::cout << "**         E --- ???????                    **" << std::endl;
    std::cout << "===============================================" << std::endl;
}

char GetChar()
{
    char ch;
    std::cin >> ch;
    std::cin.ignore(INT_MAX, '\n');

    //§³§Õ???§Õ
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
    ElectricityNet net;
    while (true)
    {
        std::cout << "??????????";
        option = GetChar();
        switch (option)
        {
        case 'A':
            net.CreateNodes();
            break;
        case 'B':
            net.CreateEdges();
            break;
        case 'C':
            net.CreateMST();
            break;
        case 'D':
            net.PrintMST();
            break;
        case 'E':
            return 0;
        default:
            std::cout << "?????????????????" << std::endl;
            break;
        }
    }

    return 0;
}