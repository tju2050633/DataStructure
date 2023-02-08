#pragma once
#include "my_stl.h"

/* ����һ����Χ�ڵ����� */
int GetInt(my_std::string prompt, int low = INT_MIN, int high = INT_MAX)
{
    int number;
    while (true)
    {
        std::cout << prompt;
        std::cin >> number;
        if (!std::cin || number < low || number > high)
        {
            std::cout << "����Ƿ�������������!\n";
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

// ѧ����Ϣ
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

// ѧ���б�
class StudentList
{
private:
    my_std::list<Student> _list;
    Student create_student();

public:
    StudentList(int length);

    bool insert(int position);     //�����㵽ָ��λ��
    bool remove(int number);       //ɾ����Ӧ���Ž��
    bool search(int number) const; //���Ҷ�Ӧ���Ž��
    bool modify(int number);       //�޸Ķ�Ӧ���Ž��
    void statistics() const;       //����������
};

StudentList::StudentList(int length)
{
    for (int i = 0; i < length; i++)
    {
        _list.push_back(Student(i + 1, "stu", "��", 20, "������ʦ"));
    }
    std::cout << "��Ϊ���ڲ��ԣ���ʹ��Ĭ�����ݡ�" << std::endl;

    statistics();
}

Student StudentList::create_student()
{
    /* ����ѧ����Ϣ */
    int number;
    my_std::string name;
    my_std::string sex;
    int age;
    my_std::string category;

    std::cout << "�����뿼�����š��������Ա����估�������";

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
    /* λ�÷Ƿ� */
    if (position < 1 || position > _list.size() + 1)
    {
        std::cout << "����λ�÷Ƿ���" << std::endl
                  << std::endl;
        return false;
    }

    /* ����ѧ�� */
    Student s = create_student();

    /* ���ѧ���Ƿ��Ѵ��� */
    for (my_std::list<Student>::iterator it = _list.begin(); it != _list.end(); it++)
    {
        if (it->number == s.number)
        {
            std::cout << "�����Ѵ��ڣ�" << std::endl << std::endl;
            return false;
        }
    }

    /* ������ */
    _list.insert(_list.begin() + (position - 1), s);

    return true;
}

bool StudentList::remove(int number)
{
    /* ���ҽ�� */
    my_std::list<Student>::iterator it = _list.begin();
    for (; it != _list.end(); it++)
    {
        if (it->number == number)
            break;
    }

    /* δ�ҵ� */
    if (it == _list.end())
    {
        std::cout << "���Ų�����" << std::endl
                  << std::endl;
        return false;
    }

    /* ɾ����� */
    _list.erase(it);

    return true;
}

bool StudentList::search(int number) const
{
    /* ���ҽ�� */
    my_std::list<Student>::iterator it = _list.begin();
    for (; it != _list.end(); it++)
    {
        if (it->number == number)
            break;
    }

    /* δ�ҵ� */
    if (it == _list.end())
    {
        std::cout << "���Ų�����" << std::endl
                  << std::endl;
        return false;
    }

    /* ��ӡ�����Ϣ */
    std::cout << "����      "
              << "����      "
              << "�Ա�      "
              << "����      "
              << "�������      " << std::endl;

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
    /* ���ҽ�� */
    my_std::list<Student>::iterator it = _list.begin();
    for (; it != _list.end(); it++)
    {
        if (it->number == number)
            break;
    }

    /* δ�ҵ� */
    if (it == _list.end())
    {
        std::cout << "���Ų�����" << std::endl
                  << std::endl;
        return false;
    }

    /* ������ */
    _list.insert(it, create_student());

    /* ɾ���ɽ�� */
    _list.erase(it);

    return true;
}

void StudentList::statistics() const
{
    for (int i = 0; i < 40; ++i)
        std::cout << "����";
    std::cout << std::endl;
    std::cout << "����     \t��  ����     \t��  �Ա�     \t��  ����     \t��  �������\n";
    for (int i = 0; i < 40; ++i)
        std::cout << "����";
    std::cout << std::endl;
    if (_list.empty())
    {
        std::cout << "���������ݡ�\n";
    }
    else
    {
        for (my_std::list<Student>::iterator it = _list.begin(); it != _list.end(); ++it)
        {
            printf("%-10d\t��  %-10s\t��  %-10s\t��  %-10d\t��  %-10s\n", (*it).number, (*it).name.c_str(),
                   (*it).sex.c_str(), (*it).age,
                   (*it).category.c_str());
        }
    }
    for (int i = 0; i < 40; ++i)
        std::cout << "����";

    std::cout << std::endl
              << std::endl
              << "�б���ѧ��������" << _list.size();

    std::cout << std::endl
              << std::endl;
}