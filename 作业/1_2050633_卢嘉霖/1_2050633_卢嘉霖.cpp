#include <iostream>
#include "Student.h"

int main()
{
    /* ���뿼������ */
    int stu_num = GetInt("�����뽨��������Ϣϵͳ��\n�����뿼��������", 0);

    /* ���뿼����Ϣ */
    StudentList stu_list(stu_num);

    /* ��������в��� */
    std::cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������\n";

    bool flag = true;
    int option;
    int position;
    int number;
    while (flag)
    {
        option = GetInt("��ѡ����Ҫ���еĲ�����", 0, 5);
        switch (option)
        {
        case 0:
            flag = false;
            break;
        case 1:
            position = GetInt("��������Ҫ����Ŀ�����λ�ã�");

            if (stu_list.insert(position))
            {
                stu_list.statistics();
            }
            break;
        case 2:
            number = GetInt("������Ҫɾ���Ŀ����Ŀ��ţ�");

            if (stu_list.remove(number))
            {
                stu_list.statistics();
            }
            break;
        case 3:
            number = GetInt("������Ҫ���ҵĿ����Ŀ��ţ�");

            stu_list.search(number);
            break;
        case 4:
            number = GetInt("������Ҫ�޸ĵĿ����Ŀ��ţ�");

            if (stu_list.modify(number))
            {
                stu_list.statistics();
            }
            break;
        case 5:
            std::cout << "����Ϊ������Ϣ��\n";
            stu_list.statistics();
            break;
        default:
            break;
        }
    }

    std::cout << "������ϣ���лʹ�ã�\n";

    return 0;
}