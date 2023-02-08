#include <iostream>
#include "my_stl.h"

const int MAX_LENGTH = 20;

/* ����һ����Χ�ڵ����� */
int GetInt(int low = INT_MIN, int high = INT_MAX)
{
    int number;
    while (true)
    {
        std::cin >> number;
        std::cin.ignore(INT_MAX, '\n');
        if (!std::cin || number < low || number > high)
        {
            std::cout << "����Ƿ�������������!" << std::endl;
            std::cin.clear();
        }
        else
        {
            break;
        }
    }
    return number;
}

// �����
class TreeNode
{
    friend class Tree;

private:
    my_std::string name;
    TreeNode *parent;
    my_std::vector<TreeNode *> children;

public:
    TreeNode(const char name[]);
    void Delete();
};

TreeNode::TreeNode(const char name[])
{
    parent = nullptr;
    this->name = name;
}

void TreeNode::Delete()
{
    for (int i = 0; i < children.size(); i++)
    {
        children[i]->Delete();
        children.erase(i);
    }
    delete this;
}

// ��
class Tree
{
private:
    TreeNode *root;

public:
    Tree();
    ~Tree();

    TreeNode *Search(TreeNode *root, const char name[]) const;
    TreeNode *Search(const char prompt[]) const;
    void PrintChildren(const TreeNode *root) const;

    void AddFamily();
    void AddMember();
    void RemoveFamily();
    void ModifyName();
};

Tree::Tree()
{
    std::cout << "���Ƚ���һ�����ף�" << std::endl;
    std::cout << "���������ȵ�������";
    char name[MAX_LENGTH];
    std::cin >> name;
    std::cin.ignore(INT_MAX, '\n');
    root = new TreeNode(name);
    std::cout << "�˼��׵������ǣ�" << root->name << std::endl
              << std::endl;
}

Tree::~Tree()
{
    root->Delete();
}

TreeNode *Tree::Search(TreeNode *root, const char name[]) const
{
    // �����Ϊ�գ����ؿ�ָ��
    if (root == nullptr)
    {
        return nullptr;
    }
    // ����㲻Ϊ�գ��жϸ�����Ƿ�ΪҪ���ҵĽ��
    if (root->name == name)
    {
        return root;
    }

    // ����㲻��Ҫ���ҵĽ�㣬�����������ӽ��
    TreeNode *node;
    for (int i = 0; i < root->children.size(); i++)
    {
        node = Search(root->children[i], name);
        if (node != nullptr)
        {
            return node;
        }
    }

    return nullptr;
}

TreeNode *Tree::Search(const char prompt[]) const
{
    // ��ȡ����
    char name[MAX_LENGTH];
    std::cout << prompt;
    std::cin >> name;
    std::cin.ignore(INT_MAX, '\n');

    // ��ȡ�����
    TreeNode *person = Search(root, name);

    return person;
}

void Tree::PrintChildren(const TreeNode *root) const
{
    if (root->children.empty())
    {
        std::cout << root->name << "û�ж�Ů" << std::endl
                  << std::endl;
        return;
    }

    std::cout << root->name << "�ĵ�һ�������ǣ�";
    for (int i = 0; i < root->children.size(); i++)
    {
        std::cout << root->children[i]->name << "    ";
    }
    std::cout << std::endl
              << std::endl;
}

void Tree::AddFamily()
{
    // ��ȡ���������
    TreeNode *host = Search("������Ҫ������ͥ���˵�������");
    if (host == nullptr)
    {
        std::cout << "û���ҵ����ˣ�" << std::endl
                  << std::endl;
        return;
    }

    // ��ȡ��Ů����
    int childrenNumber;
    std::cout << "������" << host->name << "�Ķ�Ů������";
    childrenNumber = GetInt(1);

    // ��ȡ��Ů����
    std::cout << "����������" << host->name << "�Ķ�Ů��������";
    for (int i = 0; i < childrenNumber; i++)
    {
        char childName[MAX_LENGTH];
        std::cin >> childName;
        TreeNode *child = new TreeNode(childName);
        host->children.push_back(child);
        child->parent = host;
    }
    std::cin.ignore(INT_MAX, '\n');

    // ��ӡ���Ů
    PrintChildren(host);
}

void Tree::AddMember()
{
    // ��ȡ���������
    TreeNode *host = Search("������Ҫ��Ӷ��ӣ���Ů��������������");
    if (host == nullptr)
    {
        std::cout << "û���ҵ����ˣ�" << std::endl
                  << std::endl;
        return;
    }

    // ��ȡ��Ů����
    std::cout << "������" << host->name << "����ӵĶ��ӣ���Ů������������";
    char child_name[MAX_LENGTH];
    std::cin >> child_name;
    std::cin.ignore(INT_MAX, '\n');

    // ��Ӷ�Ů
    TreeNode *child = new TreeNode(child_name);
    child->parent = host;
    host->children.push_back(child);

    // ��ӡ���Ů
    PrintChildren(host);
}

void Tree::RemoveFamily()
{
    // ��ȡ���������
    TreeNode *host = Search("������Ҫ��ɢ��ͥ���˵�������");
    if (host == nullptr)
    {
        std::cout << "û���ҵ����ˣ�" << std::endl
                  << std::endl;
        return;
    }
    std::cout << "Ҫ��ɢ��ͥ�����ǣ�" << host->name << std::endl;

    // ��ӡ���Ů
    PrintChildren(host);

    // ���Ǹ���㣬��ɾ��
    if (host == root)
    {
        std::cout << "�����Ǽ��׵����ȣ��޷���ɢ��ͥ��" << std::endl
                  << std::endl;
        return;
    }

    // ɾ����ͥ
    TreeNode *parent = host->parent;
    if (parent != nullptr)
        parent->children.erase(parent->children.find(host));

    host->Delete();
}

void Tree::ModifyName()
{
    // ��ȡ�����
    TreeNode *person = Search("������Ҫ�޸��������˵�������");
    if (person == nullptr)
    {
        std::cout << "û���ҵ����ˣ�" << std::endl
                  << std::endl;
        return;
    }

    // ��ȡ������
    my_std::string ori_name = person->name;
    std::cout << "������" << ori_name << "����������";
    char new_name[MAX_LENGTH];
    std::cin >> new_name;
    std::cin.ignore(INT_MAX, '\n');

    // �޸�����
    person->name = new_name;

    std::cout << ori_name << "�Ѹ���Ϊ��" << new_name << std::endl
              << std::endl;
}
