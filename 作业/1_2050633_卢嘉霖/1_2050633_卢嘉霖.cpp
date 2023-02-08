#include <iostream>
#include "Student.h"

int main()
{
    /* 输入考生人数 */
    int stu_num = GetInt("首先请建立考生信息系统！\n请输入考生人数：", 0);

    /* 输入考生信息 */
    StudentList stu_list(stu_num);

    /* 对链表进行操作 */
    std::cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）\n";

    bool flag = true;
    int option;
    int position;
    int number;
    while (flag)
    {
        option = GetInt("请选择您要进行的操作：", 0, 5);
        switch (option)
        {
        case 0:
            flag = false;
            break;
        case 1:
            position = GetInt("请输入你要插入的考生的位置：");

            if (stu_list.insert(position))
            {
                stu_list.statistics();
            }
            break;
        case 2:
            number = GetInt("请输入要删除的考生的考号：");

            if (stu_list.remove(number))
            {
                stu_list.statistics();
            }
            break;
        case 3:
            number = GetInt("请输入要查找的考生的考号：");

            stu_list.search(number);
            break;
        case 4:
            number = GetInt("请输入要修改的考生的考号：");

            if (stu_list.modify(number))
            {
                stu_list.statistics();
            }
            break;
        case 5:
            std::cout << "以下为完整信息表：\n";
            stu_list.statistics();
            break;
        default:
            break;
        }
    }

    std::cout << "操作完毕，感谢使用！\n";

    return 0;
}