#pragma once
#include "my_stl.h"

/* 输入一定范围内的整数 */
int GetInt(my_std::string prompt, int low = INT_MIN, int high = INT_MAX)
{
    int number;
    while (true)
    {
        std::cout << prompt;
        std::cin >> number;
        if (!std::cin || number < low || number > high)
        {
            std::cout << "输入非法，请重新输入!\n";
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
        else
        {
            break;
        }
    }
    return number;
}

// 学生信息
struct Student
{
    int number;
    my_std::string name;
    my_std::string sex;
    int age;
    my_std::string category;
    Student()
    {
        number = 0;
        name = "";
        sex = "";
        age = 0;
        category = "";
    }
    Student(int n, my_std::string na, my_std::string s, int a, my_std::string c)
    {
        number = n;
        name = na;
        sex = s;
        age = a;
        category = c;
    }
};

// 学生列表
class StudentList
{
private:
    my_std::list<Student> _list;
    Student create_student();

public:
    StudentList(int length);

    bool insert(int position);     //插入结点到指定位置
    bool remove(int number);       //删除对应考号结点
    bool search(int number) const; //查找对应考号结点
    bool modify(int number);       //修改对应考号结点
    void statistics() const;       //输出完整表格
};

StudentList::StudentList(int length)
{
    for (int i = 0; i < length; i++)
    {
        _list.push_back(Student(i + 1, "stu", "男", 20, "软件设计师"));
    }
    std::cout << "【为便于测试，已使用默认数据】" << std::endl;

    statistics();
}

Student StudentList::create_student()
{
    /* 输入学生信息 */
    int number;
    my_std::string name;
    my_std::string sex;
    int age;
    my_std::string category;

    std::cout << "请输入考生考号、姓名、性别、年龄及报考类别：";

    number = GetInt("", 1);
    std::cin >> name;
    std::cin >> sex;
    age = GetInt("", 0);
    std::cin >> category;

    Student s = Student(number, name, sex, age, category);

    return s;
}

bool StudentList::insert(int position)
{
    /* 位置非法 */
    if (position < 1 || position > _list.size() + 1)
    {
        std::cout << "插入位置非法！" << std::endl
                  << std::endl;
        return false;
    }

    /* 创建学生 */
    Student s = create_student();

    /* 检查学号是否已存在 */
    for (my_std::list<Student>::iterator it = _list.begin(); it != _list.end(); it++)
    {
        if (it->number == s.number)
        {
            std::cout << "考号已存在！" << std::endl << std::endl;
            return false;
        }
    }

    /* 插入结点 */
    _list.insert(_list.begin() + (position - 1), s);

    return true;
}

bool StudentList::remove(int number)
{
    /* 查找结点 */
    my_std::list<Student>::iterator it = _list.begin();
    for (; it != _list.end(); it++)
    {
        if (it->number == number)
            break;
    }

    /* 未找到 */
    if (it == _list.end())
    {
        std::cout << "考号不存在" << std::endl
                  << std::endl;
        return false;
    }

    /* 删除结点 */
    _list.erase(it);

    return true;
}

bool StudentList::search(int number) const
{
    /* 查找结点 */
    my_std::list<Student>::iterator it = _list.begin();
    for (; it != _list.end(); it++)
    {
        if (it->number == number)
            break;
    }

    /* 未找到 */
    if (it == _list.end())
    {
        std::cout << "考号不存在" << std::endl
                  << std::endl;
        return false;
    }

    /* 打印结点信息 */
    std::cout << "考号      "
              << "姓名      "
              << "性别      "
              << "年龄      "
              << "报考类别      " << std::endl;

    std::cout << it->number << "         "
              << it->name << "       "
              << it->sex << "        "
              << it->age << "        "
              << it->category << std::endl
              << std::endl;

    return true;
}

bool StudentList::modify(int number)
{
    /* 查找结点 */
    my_std::list<Student>::iterator it = _list.begin();
    for (; it != _list.end(); it++)
    {
        if (it->number == number)
            break;
    }

    /* 未找到 */
    if (it == _list.end())
    {
        std::cout << "考号不存在" << std::endl
                  << std::endl;
        return false;
    }

    /* 插入结点 */
    _list.insert(it, create_student());

    /* 删除旧结点 */
    _list.erase(it);

    return true;
}

void StudentList::statistics() const
{
    for (int i = 0; i < 40; ++i)
        std::cout << "──";
    std::cout << std::endl;
    std::cout << "考号     \t│  姓名     \t│  性别     \t│  年龄     \t│  报考类别\n";
    for (int i = 0; i < 40; ++i)
        std::cout << "──";
    std::cout << std::endl;
    if (_list.empty())
    {
        std::cout << "【暂无数据】\n";
    }
    else
    {
        for (my_std::list<Student>::iterator it = _list.begin(); it != _list.end(); ++it)
        {
            printf("%-10d\t│  %-10s\t│  %-10s\t│  %-10d\t│  %-10s\n", (*it).number, (*it).name.c_str(),
                   (*it).sex.c_str(), (*it).age,
                   (*it).category.c_str());
        }
    }
    for (int i = 0; i < 40; ++i)
        std::cout << "──";

    std::cout << std::endl
              << std::endl
              << "列表中学生人数：" << _list.size();

    std::cout << std::endl
              << std::endl;
}