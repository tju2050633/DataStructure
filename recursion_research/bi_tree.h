#pragma once
#include "my_stl.h"

class BiTree
{
    struct Node;

public:
    BiTree();
    ~BiTree();

    void createBiTree(int NodeNum);
    void deleteBiTree(Node *root);

    void rec_PostOrder_impl(Node *root); // 递归后序遍历二叉树实现
    void rec_PostOrder();                // 递归后序遍历二叉树
    void unrec_PostOrder();              // 非递归后序遍历二叉树

private:
    struct Node
    {
        int data;
        Node *lchild;
        Node *rchild;
        Node()
        {
            data = 0;
            lchild = rchild = nullptr;
        }
    };
    Node *root;
};

BiTree::BiTree()
{
    root = new Node();
    root->data = 1;
}

void BiTree::deleteBiTree(Node *root)
{
    if (root == nullptr)
        return;
    deleteBiTree(root->lchild);
    deleteBiTree(root->rchild);
    delete root;
}

BiTree::~BiTree()
{
    deleteBiTree(root);
}

void BiTree::createBiTree(int NodeNum)
{
    my_std::queue<Node *> q;
    q.push(root);
    int i = 2;
    while (i <= NodeNum)
    {
        Node *node = q.front();
        q.pop();
        node->lchild = new Node();
        node->lchild->data = i++;
        q.push(node->lchild);
        if (i <= NodeNum)
        {
            node->rchild = new Node();
            node->rchild->data = i++;
            q.push(node->rchild);
        }
    }
}

void BiTree::rec_PostOrder_impl(Node *root)
{
    if (root)
    {
        rec_PostOrder_impl(root->lchild);
        rec_PostOrder_impl(root->rchild);
        // cout << root->data << endl;
    }
}

void BiTree::rec_PostOrder()
{
    rec_PostOrder_impl(root);
}

void BiTree::unrec_PostOrder()
{
    Node *p = root, *q = nullptr;
    my_std::stack<Node *> s;
    while (p || !s.empty())
    {
        if (p)
        {
            s.push(p);
            p = p->lchild;
        }
        else
        {
            p = s.top();
            if (p->rchild && p->rchild != q)
            {
                p = p->rchild;
                s.push(p);
                p = p->lchild;
            }
            else
            {
                p = s.top();
                s.pop();
                // cout << p->data << endl;
                q = p;
                p = nullptr;
            }
        }
    }
}