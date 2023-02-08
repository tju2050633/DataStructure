#include <iostream>
#include "my_stl.h"

const int MAX_LENGTH = 20;

/* 输入一定范围内的整数 */
int GetInt(int low = INT_MIN, int high = INT_MAX)
{
    int number;
    while (true)
    {
        std::cin >> number;
        std::cin.ignore(INT_MAX, '\n');
        if (!std::cin || number < low || number > high)
        {
            std::cout << "输入非法，请重新输入!" << std::endl;
            std::cin.clear();
        }
        else
        {
            break;
        }
    }
    return number;
}

// 树结点
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

// 树
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
    std::cout << "首先建立一个家谱！" << std::endl;
    std::cout << "请输入祖先的姓名：";
    char name[MAX_LENGTH];
    std::cin >> name;
    std::cin.ignore(INT_MAX, '\n');
    root = new TreeNode(name);
    std::cout << "此家谱的祖先是：" << root->name << std::endl
              << std::endl;
}

Tree::~Tree()
{
    root->Delete();
}

TreeNode *Tree::Search(TreeNode *root, const char name[]) const
{
    // 根结点为空，返回空指针
    if (root == nullptr)
    {
        return nullptr;
    }
    // 根结点不为空，判断根结点是否为要查找的结点
    if (root->name == name)
    {
        return root;
    }

    // 根结点不是要查找的结点，遍历根结点的子结点
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
    // 获取姓名
    char name[MAX_LENGTH];
    std::cout << prompt;
    std::cin >> name;
    std::cin.ignore(INT_MAX, '\n');

    // 获取树结点
    TreeNode *person = Search(root, name);

    return person;
}

void Tree::PrintChildren(const TreeNode *root) const
{
    if (root->children.empty())
    {
        std::cout << root->name << "没有儿女" << std::endl
                  << std::endl;
        return;
    }

    std::cout << root->name << "的第一代子孙是：";
    for (int i = 0; i < root->children.size(); i++)
    {
        std::cout << root->children[i]->name << "    ";
    }
    std::cout << std::endl
              << std::endl;
}

void Tree::AddFamily()
{
    // 获取家主树结点
    TreeNode *host = Search("请输入要建立家庭的人的姓名：");
    if (host == nullptr)
    {
        std::cout << "没有找到该人！" << std::endl
                  << std::endl;
        return;
    }

    // 获取儿女数量
    int childrenNumber;
    std::cout << "请输入" << host->name << "的儿女人数：";
    childrenNumber = GetInt(1);

    // 获取儿女姓名
    std::cout << "请依次输入" << host->name << "的儿女的姓名：";
    for (int i = 0; i < childrenNumber; i++)
    {
        char childName[MAX_LENGTH];
        std::cin >> childName;
        TreeNode *child = new TreeNode(childName);
        host->children.push_back(child);
        child->parent = host;
    }
    std::cin.ignore(INT_MAX, '\n');

    // 打印其儿女
    PrintChildren(host);
}

void Tree::AddMember()
{
    // 获取家主树结点
    TreeNode *host = Search("请输入要添加儿子（或女儿）的人姓名：");
    if (host == nullptr)
    {
        std::cout << "没有找到该人！" << std::endl
                  << std::endl;
        return;
    }

    // 获取儿女姓名
    std::cout << "请输入" << host->name << "新添加的儿子（或女儿）的姓名：";
    char child_name[MAX_LENGTH];
    std::cin >> child_name;
    std::cin.ignore(INT_MAX, '\n');

    // 添加儿女
    TreeNode *child = new TreeNode(child_name);
    child->parent = host;
    host->children.push_back(child);

    // 打印其儿女
    PrintChildren(host);
}

void Tree::RemoveFamily()
{
    // 获取家主树结点
    TreeNode *host = Search("请输入要解散家庭的人的姓名：");
    if (host == nullptr)
    {
        std::cout << "没有找到该人！" << std::endl
                  << std::endl;
        return;
    }
    std::cout << "要解散家庭的人是：" << host->name << std::endl;

    // 打印其儿女
    PrintChildren(host);

    // 若是根结点，不删除
    if (host == root)
    {
        std::cout << "该人是家谱的祖先，无法解散家庭！" << std::endl
                  << std::endl;
        return;
    }

    // 删除家庭
    TreeNode *parent = host->parent;
    if (parent != nullptr)
        parent->children.erase(parent->children.find(host));

    host->Delete();
}

void Tree::ModifyName()
{
    // 获取树结点
    TreeNode *person = Search("请输入要修改姓名的人的姓名：");
    if (person == nullptr)
    {
        std::cout << "没有找到该人！" << std::endl
                  << std::endl;
        return;
    }

    // 获取新姓名
    my_std::string ori_name = person->name;
    std::cout << "请输入" << ori_name << "的新姓名：";
    char new_name[MAX_LENGTH];
    std::cin >> new_name;
    std::cin.ignore(INT_MAX, '\n');

    // 修改姓名
    person->name = new_name;

    std::cout << ori_name << "已更名为：" << new_name << std::endl
              << std::endl;
}
