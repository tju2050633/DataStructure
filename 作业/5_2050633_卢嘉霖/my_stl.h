#pragma once
#include <iostream>

/* =============所有声明放在命名空间my_std里，防止与std里的stl冲突============= */

namespace my_std
{
    /**
     * |---------------------------------------------------------|
     * |               模块一：「基于链表实现的list类」               |
     * |---------------------------------------------------------|
     */

     /* list_node声明 */

    template <typename T>
    struct list_node
    {
        T _data;             // 数据域
        list_node<T>* _prev; // 前驱指针
        list_node<T>* _next; // 后继指针

        // 构造函数
        list_node() : _prev(nullptr), _next(nullptr) {};
        list_node(const T& data, list_node<T>* next = nullptr, list_node<T>* prev = nullptr)
            : _data(data), _prev(prev), _next(next) {};
    };

    /* list声明 */

    template <typename T>
    class list
    {
    private:
        list_node<T>* _head; // 头指针
        list_node<T>* _tail; // 尾指针
        int _size;           // 大小

    public:
        // 构造函数，析构函数
        list();
        list(const list<T>& other);
        ~list();

        // 赋值运算符重载
        list<T>& operator=(const list<T>& other);

        // 获取信息方法
        inline bool empty() const; // 判断是否为空
        inline int size() const;   // 获取大小

        // 迭代器
        class iterator
        {
            friend class list<T>;

        private:
            list_node<T>* _ptr;

        public:
            // 构造函数
            iterator(list_node<T>* ptr = nullptr) : _ptr(ptr) {};

            // getter
            inline list_node<T>* get_ptr() const { return _ptr; };

            // 运算符重载

            T& operator*() const;  // 解引用
            T* operator->() const; // 成员访问

            iterator& operator++();                        // 前置++
            iterator operator++(int);                      // 后置++
            iterator& operator--();                        // 前置--
            iterator operator--(int);                      // 后置--
            iterator operator+=(int);                      // +=
            iterator operator-=(int);                      // -=
            iterator operator+(int) const;                 // 后置+
            iterator operator-(int) const;                 // 后置-
            friend iterator operator+(int n, iterator& it) // 前置+
            {
                return it + n; // 调用后置+
            }

            bool operator==(const iterator& other) const; // 一系列比较运算符
            bool operator!=(const iterator& other) const;
            bool operator<(const iterator& other) const;
            bool operator<=(const iterator& other) const;
            bool operator>(const iterator& other) const;
            bool operator>=(const iterator& other) const;
        };

        // 获取迭代器
        inline iterator begin(); // 获取头迭代器
        inline const iterator begin() const;
        inline iterator end(); // 获取尾迭代器
        inline const iterator end() const;
        iterator find(const T& data) const; // 通过数据获取迭代器

        // 访问元素
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;

        // 增加元素
        void push_front(const T& data);           // 在头部插入元素
        void push_back(const T& data);            // 在尾部插入元素
        void insert(iterator pos, const T& data); // 在指定位置插入元素

        // 删除元素
        void pop_front();         // 删除头部元素
        void pop_back();          // 删除尾部元素
        void erase(iterator pos); // 删除指定位置元素
        void clear();             // 清空容器
    };

    /**
     * |---------------------------------------------------------|
     * |              模块二：「基于数组实现的vector类」              |
     * |---------------------------------------------------------|
     */

#define VECTOR_SIZE 10 // 默认容量

     /* vector声明 */

    template <typename T>
    class vector
    {
    private:
        T* _data;      // 数据域
        int _size;     // 大小
        int _capacity; // 容量

        void _expand();                    // 扩容
        int calc_capacity(int size) const; // 计算容量
        void _quick_sort(int, int);        // 快速排序

    public:
        // 构造函数，析构函数
        vector();                       // 默认构造函数
        vector(const vector<T>& other); // 拷贝构造函数
        vector(T* data, int size);      // 通过数组构造
        vector(int n);                  // 构造函数，指定初始大小
        vector(int n, const T& data);   // 构造函数，指定大小和初始值
        ~vector();                      // 析构函数

        // 运算符重载
        vector<T>& operator=(const vector<T>& other); // 赋值
        inline T& operator[](int index);              // 下标访问
        inline const T& operator[](int index) const;  // 下标访问

        // 获取信息方法
        inline bool empty() const;   // 判断是否为空
        inline int size() const;     // 获取大小
        inline int capacity() const; // 获取容量

        // 设置size
        void resize(int n);

        // 迭代器
        class iterator
        {
            friend class vector<T>;

        private:
            T* _ptr;
            T* _begin; // 指向vector的头部
            int _size; // vector的大小

        public:
            // 构造函数
            iterator(T* begin, int size, T* ptr = nullptr)
                : _ptr(ptr), _begin(begin), _size(size) {};

            // getter
            inline T* get_ptr() const { return _ptr; };

            // 运算符重载

            T& operator*() const;  // 解引用
            T* operator->() const; // 成员访问

            iterator& operator++();                              // 前置++
            iterator operator++(int);                            // 后置++
            iterator& operator--();                              // 前置--
            iterator operator--(int);                            // 后置--
            iterator operator+=(int);                            // +=
            iterator operator-=(int);                            // -=
            iterator operator+(int) const;                       // 后置+
            iterator operator-(int) const;                       // 后置-
            friend iterator operator+(int n, const iterator& it) // 前置+
            {
                return it + n; // 调用后置+
            }

            bool operator==(const iterator& other) const; // 一系列比较运算符
            bool operator!=(const iterator& other) const;
            bool operator<(const iterator& other) const;
            bool operator<=(const iterator& other) const;
            bool operator>(const iterator& other) const;
            bool operator>=(const iterator& other) const;
        };

        // 获取迭代器
        inline iterator begin(); // 获取头迭代器
        inline const iterator begin() const;
        inline iterator end(); // 获取尾迭代器
        inline const iterator end() const;
        iterator find(const T& data) const; // 通过数据获取迭代器

        // 访问元素
        T get(int index) const;             // 获取指定位置元素
        void set(int index, const T& data); // 设置指定位置元素
        void fill(const T& data);           // 填充容器

        // 增加元素
        void push_front(const T& data);                  // 在头部插入元素
        void push_back(const T& data);                   // 在尾部插入元素
        void insert(const iterator& pos, const T& data); // 在指定位置插入元素
        void insert(int index, const T& data);           // 在指定位置插入元素

        // 删除元素
        void pop_front();                                        // 删除头部元素
        void pop_back();                                         // 删除尾部元素
        void erase(const iterator& pos);                         // 删除指定位置元素
        void erase(int index);                                   // 删除指定位置元素
        void erase(const iterator& first, const iterator& last); // 删除[first, last)区间元素
        void erase(int first, int last);                         // 删除[first, last)区间元素
        void clear();                                            // 清空容器

        // 排序
        void sort();
    };

    /**
     * |---------------------------------------------------------|
     * |           模块三：「基于C风格字符串实现的string类」           |
     * |---------------------------------------------------------|
     */

     /* string声明 */

    class string
    {
    private:
        vector<char> _data; // 字符串数据

    public:
        // 构造函数
        string();                          // 默认构造函数
        string(const char* str);           // 通过C风格字符串构造
        string(const string& other);       // 拷贝构造函数
        string(const vector<char>& other); // 通过vector构造

        // 析构函数
        ~string() {}

        // 运算符重载
        string& operator=(const string& other);                               // 赋值
        string& operator=(const char* str);                                   // 赋值
        string& operator=(const vector<char>& other);                         // 赋值
        char& operator[](int index);                                          // 下标访问
        const char& operator[](int index) const;                              // 下标访问
        friend std::ostream& operator<<(std::ostream& os, const string& str); // 输出流
        friend std::istream& operator>>(std::istream& is, string& str);       // 输入流
        string operator+(const string& other) const;                          // 连接
        string& operator+=(const string& other);                              // 连接
        bool operator==(const string& other) const;                           // 比较
        bool operator!=(const string& other) const;                           // 比较
        bool operator<(const string& other) const;                            // 比较
        bool operator<=(const string& other) const;                           // 比较
        bool operator>(const string& other) const;                            // 比较
        bool operator>=(const string& other) const;                           // 比较

        // 获取信息方法
        inline bool empty() const;   // 判断是否为空
        inline int length() const;   // 获取长度
        inline int size() const;     // 获取长度
        inline int capacity() const; // 获取容量

        // 增加元素
        void append(const string& other);            // 追加字符串
        void append(const char* str);                // 追加字符串
        void append(const char& c);                  // 追加字符
        void insert(int index, const string& other); // 在指定位置插入字符串
        void insert(int index, const char* str);     // 在指定位置插入字符串
        void insert(int index, const char& c);       // 在指定位置插入字符

        // 删除元素
        void erase(int index);           // 删除指定位置元素
        void erase(int first, int last); // 删除[first, last)区间元素
        void clear();                    // 清空容器

        // 替换元素
        void replace(int index, const char& c);                 // 替换指定位置元素
        void replace(int first, int last, const char& c);       // 替换[first, last)区间元素
        void replace(int first, int last, const char* str);     // 替换[first, last)区间元素
        void replace(int first, int last, const string& other); // 替换[first, last)区间元素

        // 查找元素
        int find(const char& c) const;            // 查找字符
        int find(const char* str) const;          // 查找字符串
        int find(const string& other) const;      // 查找字符串
        string substr(int first, int last) const; // 获取[first, last)区间子串
        const char* c_str() const;                // 获取C风格字符串
    };

    /**
     * |---------------------------------------------------------|
     * |              模块四：「基于list实现的queue类」              |
     * |---------------------------------------------------------|
     */

     /* queue声明 */

    template <typename T>
    class queue
    {
    private:
        list<T> _data; // 数据

    public:
        // 构造函数，析构函数
        queue() {}  // 默认构造函数
        ~queue() {} // 默认析构函数

        // 获取信息方法
        inline bool empty() const; // 判断是否为空
        inline int size() const;   // 获取长度

        // 增加元素
        void push(const T& value); // 入队

        // 删除元素
        void pop(); // 出队

        // 访问元素
        T& front(); // 获取队首元素
        const T& front() const;
        T& back(); // 获取队尾元素
        const T& back() const;
    };

    /**
     * |---------------------------------------------------------|
     * |              模块五：「基于list实现的stack类」              |
     * |---------------------------------------------------------|
     */

     /* stack声明 */

    template <typename T>
    class stack
    {
    private:
        list<T> _data; // 数据

    public:
        // 构造函数，析构函数
        stack() {}  // 默认构造函数
        ~stack() {} // 默认析构函数

        // 获取信息方法
        inline bool empty() const; // 判断是否为空
        inline int size() const;   // 获取长度

        // 增加元素
        void push(const T& value); // 入栈

        // 删除元素
        void pop(); // 出栈

        // 访问元素
        T& top(); // 获取栈顶元素
        const T& top() const;
    };

    /**
     * |---------------------------------------------------------|
     * |                    模块六：「pair类」                      |
     * |---------------------------------------------------------|
     */

     /* pair声明 */
    template <typename T1, typename T2>
    struct pair
    {
        T1 first;  // 第一个元素
        T2 second; // 第二个元素

        // 构造函数，析构函数
        pair() {}                                                                 // 默认构造函数
        pair(const T1& first, const T2& second) : first(first), second(second) {} // 构造函数
        pair(const pair& other) : first(other.first), second(other.second) {}     // 拷贝构造函数
        template <class T3, class T4>
        pair(const T3& first, const T4& second) : first(first), second(second) {} // 构造函数(支持隐式转换)
        ~pair() {}                                                                // 默认析构函数

        // 重载运算符
        pair& operator=(const pair& other);              // 重载赋值运算符
        inline bool operator==(const pair& other) const; // 重载等于运算符
        inline bool operator!=(const pair& other) const; // 重载不等于运算符
    };

};

/* =============所有实现放在namespace外，故需加上my_std::==================== */

/**
 * |---------------------------------------------------------|
 * |               模块一：「基于链表实现的list类」               |
 * |---------------------------------------------------------|
 */

namespace my_std
{
    /* list_node实现 */

    // 声明已实现构造函数，无需另外实现

    /* list实现 */

    // 构造函数，析构函数
    template <typename T>
    my_std::list<T>::list()
    {
        // 初始化头尾结点
        _head = new list_node<T>();
        _tail = new list_node<T>();
        _head->_next = _tail;
        _tail->_prev = _head;
        _size = 0;
    }

    template <typename T>
    my_std::list<T>::list(const list<T>& other)
    {
        // 调用默认构造函数(在原始内存覆盖，支持C++11以下编译器)
        new (this) list();

        // 复制数据
        for (my_std::list<T>::iterator it = other.begin(); it != other.end(); ++it)
        {
            push_back(*it);
        }
    }

    template <typename T>
    my_std::list<T>::~list()
    {
        clear();      // 清空数据结点
        delete _head; // 删除头结点
        delete _tail; // 删除尾结点
    }

    // 赋值运算符重载
    template <typename T>
    my_std::list<T>& my_std::list<T>::operator=(const my_std::list<T>& other)
    {
        // 防止自我赋值
        if (this == &other)
            return *this;

        // 清空数据结点
        clear();

        // 复制数据
        for (my_std::list<T>::iterator it = other.begin(); it != other.end(); ++it)
        {
            push_back(*it);
        }

        return *this;
    }

    // 获取信息方法
    template <typename T>
    inline bool my_std::list<T>::empty() const
    {
        return _size == 0;
    }

    template <typename T>
    inline int my_std::list<T>::size() const
    {
        return _size;
    }

    // 迭代器类实现
    template <typename T>
    T& my_std::list<T>::iterator::operator*() const
    {
        return _ptr->_data;
    }

    template <typename T>
    T* my_std::list<T>::iterator::operator->() const
    {
        return &_ptr->_data;
    }

    template <typename T>
    typename my_std::list<T>::iterator& my_std::list<T>::iterator::operator++()
    {
        _ptr = _ptr->_next;
        return *this;
    }

    template <typename T>
    typename my_std::list<T>::iterator my_std::list<T>::iterator::operator++(int)
    {
        iterator temp = *this;
        _ptr = _ptr->_next;
        return temp;
    }

    template <typename T>
    typename my_std::list<T>::iterator& my_std::list<T>::iterator::operator--()
    {
        _ptr = _ptr->_prev;
        return *this;
    }

    template <typename T>
    typename my_std::list<T>::iterator my_std::list<T>::iterator::operator--(int)
    {
        iterator temp = *this;
        _ptr = _ptr->_prev;
        return temp;
    }

    template <typename T>
    typename my_std::list<T>::iterator my_std::list<T>::iterator::operator+=(int n)
    {
        for (int i = 0; i < n; ++i)
        {
            ++(*this);
        }
        return *this;
    }

    template <typename T>
    typename my_std::list<T>::iterator my_std::list<T>::iterator::operator-=(int n)
    {
        for (int i = 0; i < n; ++i)
        {
            --(*this);
        }
        return *this;
    }

    template <typename T>
    typename my_std::list<T>::iterator my_std::list<T>::iterator::operator+(int n) const
    {
        iterator it = *this;
        for (int i = 0; i < n; ++i)
        {
            ++it;
        }
        return it;
    }

    template <typename T>
    typename my_std::list<T>::iterator my_std::list<T>::iterator::operator-(int n) const
    {
        iterator it = *this;
        for (int i = 0; i < n; ++i)
        {
            --it;
        }
        return it;
    }

    template <typename T>
    bool my_std::list<T>::iterator::operator==(const iterator& other) const
    {
        return _ptr == other.get_ptr();
    }

    template <typename T>
    bool my_std::list<T>::iterator::operator!=(const iterator& other) const
    {
        return _ptr != other.get_ptr();
    }

    template <typename T>
    bool my_std::list<T>::iterator::operator<(const iterator& other) const
    {
        iterator it = *this;
        while (it._ptr != nullptr)
        {
            ++it;
            if (it == other)
                return true;
        }
        return false;
    }

    template <typename T>
    bool my_std::list<T>::iterator::operator<=(const iterator& other) const
    {
        return *this == other || *this < other;
    }

    template <typename T>
    bool my_std::list<T>::iterator::operator>(const iterator& other) const
    {
        return !(*this <= other);
    }

    template <typename T>
    bool my_std::list<T>::iterator::operator>=(const iterator& other) const
    {
        return !(*this < other);
    }

    // 获取迭代器
    template <typename T>
    inline typename my_std::list<T>::iterator my_std::list<T>::begin()
    {
        return iterator(_head->_next);
    }

    template <typename T>
    inline const typename my_std::list<T>::iterator my_std::list<T>::begin() const
    {
        return iterator(_head->_next);
    }

    template <typename T>
    inline typename my_std::list<T>::iterator my_std::list<T>::end()
    {
        return iterator(_tail);
    }

    template <typename T>
    inline const typename my_std::list<T>::iterator my_std::list<T>::end() const
    {
        return iterator(_tail);
    }

    template <typename T>
    typename my_std::list<T>::iterator my_std::list<T>::find(const T& data) const
    {
        iterator it = begin();
        while (it != end())
        {
            if (*it == data)
                return it;
            ++it;
        }
        return end();
    }

    // 访问元素
    template <typename T>
    T& my_std::list<T>::front()
    {
        return _head->_next->_data;
    }

    template <typename T>
    const T& my_std::list<T>::front() const
    {
        return _head->_next->_data;
    }

    template <typename T>
    T& my_std::list<T>::back()
    {
        return _tail->_prev->_data;
    }

    template <typename T>
    const T& my_std::list<T>::back() const
    {
        return _tail->_prev->_data;
    }

    // 增加元素
    template <typename T>
    void my_std::list<T>::push_front(const T& data)
    {
        insert(begin(), data);
    }

    template <typename T>
    void my_std::list<T>::push_back(const T& data)
    {
        insert(end(), data);
    }

    template <typename T>
    void my_std::list<T>::insert(iterator pos, const T& data)
    {
        if (pos < begin() || pos > end())
        {
            std::cerr << "my_std::list::insert 发生错误【迭代器越界】" << std::endl;
            return;
        }
        list_node<T>* node = new list_node<T>(data);
        node->_next = pos._ptr;
        node->_prev = pos._ptr->_prev;
        pos._ptr->_prev->_next = node;
        pos._ptr->_prev = node;
        ++_size;
    }

    // 删除元素
    template <typename T>
    void my_std::list<T>::pop_front()
    {
        erase(begin());
    }

    template <typename T>
    void my_std::list<T>::pop_back()
    {
        erase(--end());
    }

    template <typename T>
    void my_std::list<T>::erase(iterator pos)
    {
        if (pos < begin() || pos >= end())
        {
            std::cerr << "my_std::list::erase 发生错误【迭代器越界】" << std::endl;
            return;
        }
        list_node<T>* node = pos.get_ptr();
        node->_prev->_next = node->_next;
        node->_next->_prev = node->_prev;
        delete node;
        --_size;
    }

    template <typename T>
    void my_std::list<T>::clear()
    {
        while (!empty())
            pop_front();
    }
};

/**
 * |---------------------------------------------------------|
 * |              模块二：「基于数组实现的vector类」              |
 * |---------------------------------------------------------|
 */

namespace my_std
{
    /* vector实现 */

    // private方法
    template <typename T>
    void my_std::vector<T>::_expand()
    {
        _capacity += VECTOR_SIZE;

        T* old_data = this->_data;
        this->_data = new T[_capacity];

        for (int i = 0; i < _size; ++i)
            this->_data[i] = old_data[i];

        delete[] old_data;
    }

    template <typename T>
    int my_std::vector<T>::calc_capacity(int size) const
    {
        return (size / VECTOR_SIZE + 1) * VECTOR_SIZE;
    }

    // 构造函数，析构函数
    template <typename T>
    my_std::vector<T>::vector()
    {
        _data = new T[1];
        _capacity = 1;
        _size = 0;
    }

    template <typename T>
    my_std::vector<T>::vector(const vector& other)
    {
        _data = new T[other.capacity()];
        _capacity = other.capacity();
        _size = other.size();

        for (int i = 0; i < _size; ++i)
            _data[i] = other[i];
    }

    template <typename T>
    my_std::vector<T>::vector(T* data, int size)
    {
        _capacity = calc_capacity(size);
        _data = new T[_capacity];
        _size = size;

        for (int i = 0; i < _size; ++i)
            _data[i] = data[i];
    }

    template <typename T>
    my_std::vector<T>::vector(int n)
    {
        _capacity = calc_capacity(n);
        _data = new T[_capacity];
        _size = n;
    }

    template <typename T>
    my_std::vector<T>::vector(int n, const T& data)
    {
        new (this) vector(n);

        for (int i = 0; i < _size; ++i)
            _data[i] = data;
    }

    template <typename T>
    my_std::vector<T>::~vector()
    {
        delete[] _data;
    }

    // 运算符重载
    template <typename T>
    my_std::vector<T>& my_std::vector<T>::operator=(const vector& other)
    {
        // 防止自赋值
        if (this == &other)
            return *this;

        delete[] _data;
        _data = new T[other.capacity()];
        _capacity = other.capacity();
        _size = other.size();

        for (int i = 0; i < _size; ++i)
            _data[i] = other[i];

        return *this;
    }

    template <typename T>
    T& my_std::vector<T>::operator[](int index)
    {
        if (index < 0 || index >= _size)
        {
            std::cerr << "my_std::vector::operator[] 发生错误【下标越界】" << std::endl;
            return _data[0];
        }
        return _data[index];
    }

    template <typename T>
    const T& my_std::vector<T>::operator[](int index) const
    {
        if (index < 0 || index >= _size)
        {
            std::cerr << "my_std::vector::operator[] 发生错误【下标越界】" << std::endl;
            return _data[0];
        }
        return _data[index];
    }

    // 获取信息方法
    template <typename T>
    bool my_std::vector<T>::empty() const
    {
        return _size == 0;
    }

    template <typename T>
    int my_std::vector<T>::size() const
    {
        return _size;
    }

    template <typename T>
    int my_std::vector<T>::capacity() const
    {
        return _capacity;
    }

    // 设置size
    template <typename T>
    void my_std::vector<T>::resize(int size)
    {
        if (size >= _capacity)
        {
            _capacity = calc_capacity(size);
            T* old_data = _data;
            _data = new T[_capacity];

            for (int i = 0; i < _size; ++i)
                _data[i] = old_data[i];

            delete[] old_data;
        }
        _size = size;
    }

    // 迭代器
    template <typename T>
    T& my_std::vector<T>::iterator::operator*() const
    {
        return *_ptr;
    }

    template <typename T>
    T* my_std::vector<T>::iterator::operator->() const
    {
        return _ptr;
    }

    template <typename T>
    typename my_std::vector<T>::iterator& my_std::vector<T>::iterator::operator++()
    {
        ++_ptr;
        return *this;
    }

    template <typename T>
    typename my_std::vector<T>::iterator my_std::vector<T>::iterator::operator++(int)
    {
        iterator tmp = *this;
        ++_ptr;
        return tmp;
    }

    template <typename T>
    typename my_std::vector<T>::iterator& my_std::vector<T>::iterator::operator--()
    {
        --_ptr;
        return *this;
    }

    template <typename T>
    typename my_std::vector<T>::iterator my_std::vector<T>::iterator::operator--(int)
    {
        iterator tmp = *this;
        --_ptr;
        return tmp;
    }

    template <typename T>
    typename my_std::vector<T>::iterator my_std::vector<T>::iterator::operator+=(int n)
    {
        _ptr += n;
        return *this;
    }

    template <typename T>
    typename my_std::vector<T>::iterator my_std::vector<T>::iterator::operator-=(int n)
    {
        _ptr -= n;
        return *this;
    }

    template <typename T>
    typename my_std::vector<T>::iterator my_std::vector<T>::iterator::operator+(int n) const
    {
        return iterator(_begin, _size, _ptr + n);
    }

    template <typename T>
    typename my_std::vector<T>::iterator my_std::vector<T>::iterator::operator-(int n) const
    {
        return iterator(_begin, _size, _ptr - n);
    }

    template <typename T>
    bool my_std::vector<T>::iterator::operator==(const iterator& other) const
    {
        return _ptr == other.get_ptr();
    }

    template <typename T>
    bool my_std::vector<T>::iterator::operator!=(const iterator& other) const
    {
        return _ptr != other.get_ptr();
    }

    template <typename T>
    bool my_std::vector<T>::iterator::operator<(const iterator& other) const
    {
        return _ptr < other.get_ptr();
    }

    template <typename T>
    bool my_std::vector<T>::iterator::operator<=(const iterator& other) const
    {
        return _ptr <= other.get_ptr();
    }

    template <typename T>
    bool my_std::vector<T>::iterator::operator>(const iterator& other) const
    {
        return _ptr > other.get_ptr();
    }

    template <typename T>
    bool my_std::vector<T>::iterator::operator>=(const iterator& other) const
    {
        return _ptr >= other.get_ptr();
    }

    // 获取迭代器
    template <typename T>
    typename my_std::vector<T>::iterator my_std::vector<T>::begin()
    {
        return iterator(_data, _size, _data);
    }

    template <typename T>
    const typename my_std::vector<T>::iterator my_std::vector<T>::begin() const
    {
        return iterator(_data, _size, _data);
    }

    template <typename T>
    typename my_std::vector<T>::iterator my_std::vector<T>::end()
    {
        return iterator(_data, _size, _data + _size);
    }

    template <typename T>
    const typename my_std::vector<T>::iterator my_std::vector<T>::end() const
    {
        return iterator(_data, _size, _data + _size);
    }

    template <typename T>
    typename my_std::vector<T>::iterator my_std::vector<T>::find(const T& data) const
    {
        for (iterator it = begin(); it != end(); ++it)
        {
            if (*it == data)
                return it;
        }
        return end();
    }

    // 访问元素
    template <typename T>
    T my_std::vector<T>::get(int index) const
    {
        if (index < 0 || index >= _size)
        {
            std::cerr << "my_std::vector::get 发生错误【下标越界】" << std::endl;
            return T();
        }
        return _data[index];
    }

    template <typename T>
    void my_std::vector<T>::set(int index, const T& data)
    {
        if (index < 0 || index >= _size)
        {
            std::cerr << "my_std::vector::set 发生错误【下标越界】" << std::endl;
            return;
        }
        _data[index] = data;
    }

    template <typename T>
    void my_std::vector<T>::fill(const T& data)
    {
        for (int i = 0; i < _size; ++i)
            _data[i] = data;
    }

    // 增加元素
    template <typename T>
    void my_std::vector<T>::push_front(const T& data)
    {
        insert(0, data);
    }

    template <typename T>
    void my_std::vector<T>::push_back(const T& data)
    {
        insert(_size, data);
    }

    template <typename T>
    void my_std::vector<T>::insert(const iterator& pos, const T& data)
    {
        if (pos < begin() || pos > end())
        {
            std::cerr << "my_std::vector::insert 发生错误【下标越界】" << std::endl;
            return;
        }

        if (_size == _capacity)
            _expand();

        for (iterator it = end(); it != pos; --it)
            *it = *(it - 1);

        *pos = data;
        ++_size;
    }

    template <typename T>
    void my_std::vector<T>::insert(int index, const T& data)
    {
        if (index < 0 || index > _size)
        {
            std::cerr << "my_std::vector::insert 发生错误【下标越界】" << std::endl;
            return;
        }

        if (_size == _capacity)
            _expand();

        for (int i = _size; i > index; --i)
            _data[i] = _data[i - 1];

        _data[index] = data;
        ++_size;
    }

    // 删除元素
    template <typename T>
    void my_std::vector<T>::pop_front()
    {
        erase(0);
    }

    template <typename T>
    void my_std::vector<T>::pop_back()
    {
        erase(_size - 1);
    }

    template <typename T>
    void my_std::vector<T>::erase(const iterator& pos)
    {
        if (pos < begin() || pos >= end())
        {
            std::cerr << "my_std::vector::erase 发生错误【下标越界】" << std::endl;
            return;
        }

        for (iterator it = pos; it != end() - 1; ++it)
            *it = *(it + 1);

        --_size;
    }

    template <typename T>
    void my_std::vector<T>::erase(int index)
    {
        if (index < 0 || index >= _size)
        {
            std::cerr << "my_std::vector::erase 发生错误【下标越界】" << std::endl;
            return;
        }

        for (int i = index; i < _size - 1; ++i)
            _data[i] = _data[i + 1];

        --_size;
    }

    template <typename T>
    void my_std::vector<T>::erase(const iterator& first, const iterator& last)
    {
        if (first < begin() || first >= end() || last < begin() || last > end() || first > last)
        {
            std::cerr << "my_std::vector::erase 发生错误【下标越界】" << std::endl;
            return;
        }

        for (iterator it = first; it != last; ++it)
            erase(first);
    }

    template <typename T>
    void my_std::vector<T>::erase(int first, int last)
    {
        if (first < 0 || first >= _size || last < 0 || last > _size || first > last)
        {
            std::cerr << "my_std::vector::erase 发生错误【下标越界】" << std::endl;
            return;
        }

        for (int i = first; i < last; ++i)
            erase(first);
    }

    template <typename T>
    void my_std::vector<T>::clear()
    {
        _size = 0;
    }

    // 排序
    template <typename T>
    void my_std::vector<T>::sort()
    {
        // 快速排序
        _quick_sort(0, _size - 1);
    }

    template <typename T>
    void my_std::vector<T>::_quick_sort(int left, int right)
    {
        if (left >= right)
            return;

        int i = left, j = right;
        T pivot = _data[left];

        while (i < j)
        {
            while (i < j && _data[j] >= pivot)
                --j;
            _data[i] = _data[j];

            while (i < j && _data[i] <= pivot)
                ++i;
            _data[j] = _data[i];
        }

        _data[i] = pivot;

        _quick_sort(left, i - 1);
        _quick_sort(i + 1, right);
    }
};

/**
 * |---------------------------------------------------------|
 * |           模块三：「基于C风格字符串实现的string类」           |
 * |---------------------------------------------------------|
 */

namespace my_std
{
    /* string实现 */

    // 构造函数
    my_std::string::string()
    {
        _data.push_back('\0');
    }

    my_std::string::string(const char* str)
    {
        (*this) = str;
    }

    my_std::string::string(const string& str)
    {
        (*this) = str;
    }

    my_std::string::string(const vector<char>& str)
    {
        (*this) = str;
    }

    // 运算符重载
    my_std::string& my_std::string::operator=(const string& str)
    {
        _data.clear();
        for (int i = 0; i < str.size(); ++i)
            _data.push_back(str[i]);
        _data.push_back('\0');
        return *this;
    }

    my_std::string& my_std::string::operator=(const char* str)
    {
        _data.clear();
        for (int i = 0; str[i] != '\0'; ++i)
            _data.push_back(str[i]);
        _data.push_back('\0');
        return *this;
    }

    my_std::string& my_std::string::operator=(const vector<char>& str)
    {
        _data.clear();
        for (int i = 0; i < str.size(); ++i)
            _data.push_back(str[i]);
        _data.push_back('\0');
        return *this;
    }

    char& my_std::string::operator[](int index)
    {
        return _data[index];
    }

    const char& my_std::string::operator[](int index) const
    {
        return _data[index];
    }

    std::ostream& operator<<(std::ostream& os, const string& str)
    {
        for (int i = 0; i < str.size() && str[i] != '\0'; ++i)
            os << str[i];
        return os;
    }

    std::istream& operator>>(std::istream& is, string& str)
    {
        str.clear();
        char ch;
        while (is.get(ch))
        {
            if (str.size() == 0 && (ch == ' ' || ch == '\n'))
                continue;
            if (str.size() != 0 && (ch == ' ' || ch == '\n'))
                break;
            str.append(ch);
        }

        return is;
    }

    my_std::string my_std::string::operator+(const string& other) const
    {
        string temp = *this;
        temp.append(other);
        return temp;
    }

    my_std::string& my_std::string::operator+=(const string& other)
    {
        (*this).append(other);
        return (*this);
    }

    bool my_std::string::operator==(const string& other) const
    {
        if (size() != other.size())
            return false;
        for (int i = 0; i < size(); ++i)
            if ((*this)[i] != other[i])
                return false;
        return true;
    }

    bool my_std::string::operator!=(const string& other) const
    {
        return !((*this) == other);
    }

    bool my_std::string::operator<(const string& other) const
    {
        int len = size() < other.size() ? size() : other.size();
        for (int i = 0; i < len; ++i)
        {
            if ((*this)[i] < other[i])
                return true;
            else if ((*this)[i] > other[i])
                return false;
        }
        return size() < other.size();
    }

    bool my_std::string::operator>(const string& other) const
    {
        return other < (*this);
    }

    bool my_std::string::operator<=(const string& other) const
    {
        return !((*this) > other);
    }

    bool my_std::string::operator>=(const string& other) const
    {
        return !((*this) < other);
    }

    // 获取信息方法
    bool my_std::string::empty() const
    {
        return size() == 0;
    }

    int my_std::string::length() const
    {
        return size();
    }

    int my_std::string::size() const
    {
        return _data.size() - 1;
    }

    int my_std::string::capacity() const
    {
        return _data.capacity();
    }

    // 增加元素
    void my_std::string::append(const string& str)
    {
        for (int i = 0; i < str.size(); ++i)
            _data.insert(_data.size() - 1, str[i]);
    }

    void my_std::string::append(const char* str)
    {
        append(string(str));
    }

    void my_std::string::append(const char& c)
    {
        _data.insert(_data.size() - 1, c);
    }

    void my_std::string::insert(int index, const string& str)
    {
        if (index < 0 || index > size())
        {
            std::cerr << "my_std::string::insert 发生错误【下标越界】" << std::endl;
            return;
        }

        vector<char> temp;
        for (int i = 0; i < index; ++i)
            temp.push_back(_data[i]);
        for (int i = 0; i < str.size(); ++i)
            temp.push_back(str[i]);
        for (int i = index; i < size(); ++i)
            temp.push_back(_data[i]);
        temp.push_back('\0');
        _data = temp;
    }

    void my_std::string::insert(int index, const char* str)
    {
        insert(index, string(str));
    }

    void my_std::string::insert(int index, const char& c)
    {
        if (index < 0 || index > size())
        {
            std::cerr << "my_std::string::insert 发生错误【下标越界】" << std::endl;
            return;
        }
        _data.insert(index, c);
    }

    // 删除元素
    void my_std::string::erase(int index)
    {
        if (index < 0 || index >= size())
        {
            std::cerr << "my_std::string::erase 发生错误【下标越界】" << std::endl;
            return;
        }
        _data.erase(index);
    }

    void my_std::string::erase(int first, int last)
    {
        if (first < 0 || first >= size() || last < 0 || last >= size() || first > last)
        {
            std::cerr << "my_std::string::erase 发生错误【下标越界】" << std::endl;
            return;
        }
        _data.erase(first, last);
    }

    void my_std::string::clear()
    {
        _data.clear();
        _data.push_back('\0');
    }

    // 替换元素
    void my_std::string::replace(int index, const char& c)
    {
        if (index < 0 || index >= size())
        {
            std::cerr << "my_std::string::replace 发生错误【下标越界】" << std::endl;
            return;
        }
        _data[index] = c;
    }

    void my_std::string::replace(int first, int last, const char& c)
    {
        if (first < 0 || first >= size() || last < 0 || last > size() || first > last)
        {
            std::cerr << "my_std::string::replace 发生错误【下标越界】" << std::endl;
            return;
        }
        for (int i = first; i < last; ++i)
            _data[i] = c;
    }

    void my_std::string::replace(int first, int last, const char* str)
    {
        if (first < 0 || first >= size() || last < 0 || last > size() || first > last)
        {
            std::cerr << "my_std::string::replace 发生错误【下标越界】" << std::endl;
            return;
        }
        string temp = substr(0, first);
        temp += str;
        temp += substr(last, size());
        (*this) = temp;
    }

    void my_std::string::replace(int first, int last, const my_std::string& other)
    {
        replace(first, last, other.c_str());
    }

    // 查找元素
    int my_std::string::find(const char& c) const
    {
        for (int i = 0; i < size(); ++i)
            if (_data[i] == c)
                return i;
        return -1;
    }

    int my_std::string::find(const char* str) const
    {
        return find(string(str));
    }

    int my_std::string::find(const my_std::string& other) const
    {
        for (int i = 0; i < size(); ++i)
        {
            if (_data[i] == other[0])
            {
                bool flag = true;
                for (int j = 1; j < other.size(); ++j)
                {
                    if (_data[i + j] != other[j])
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag)
                    return i;
            }
        }
        return -1;
    }

    my_std::string my_std::string::substr(int first, int last) const
    {
        if (first < 0 || first >= size() || last < 0 || last > size() || first > last)
        {
            std::cerr << "my_std::string::substr 发生错误【下标越界】" << std::endl;
            return "";
        }
        string temp;
        for (int i = first; i < last; ++i)
            temp.append(_data[i]);
        return temp;
    }

    const char* my_std::string::c_str() const
    {
        char* temp = new char[size() + 1];
        for (int i = 0; i < size(); ++i)
            temp[i] = _data[i];
        temp[size()] = '\0';

        return temp;
    }
};

/**
 * |---------------------------------------------------------|
 * |              模块四：「基于list实现的queue类」              |
 * |---------------------------------------------------------|
 */

namespace my_std
{
    /* queue实现 */

    // 获取信息方法
    template <typename T>
    bool queue<T>::empty() const
    {
        return _data.empty();
    }

    template <typename T>
    int queue<T>::size() const
    {
        return _data.size();
    }

    // 增加元素
    template <typename T>
    void queue<T>::push(const T& value)
    {
        _data.push_back(value);
    }

    // 删除元素
    template <typename T>
    void queue<T>::pop()
    {
        if (empty())
        {
            std::cerr << "my_std::queue::pop 发生错误【队列为空】" << std::endl;
            return;
        }
        _data.pop_front();
    }

    // 访问元素
    template <typename T>
    T& queue<T>::front()
    {
        if (empty())
        {
            std::cerr << "my_std::queue::front 发生错误【队列为空】" << std::endl;
            return _data.front();
        }
        return _data.front();
    }

    template <typename T>
    const T& queue<T>::front() const
    {
        if (empty())
        {
            std::cerr << "my_std::queue::front 发生错误【队列为空】" << std::endl;
            return _data.front();
        }
        return _data.front();
    }

    template <typename T>
    T& queue<T>::back()
    {
        if (empty())
        {
            std::cerr << "my_std::queue::back 发生错误【队列为空】" << std::endl;
            return _data.back();
        }
        return _data.back();
    }

    template <typename T>
    const T& queue<T>::back() const
    {
        if (empty())
        {
            std::cerr << "my_std::queue::back 发生错误【队列为空】" << std::endl;
            return _data.back();
        }
        return _data.back();
    }
};

/**
 * |---------------------------------------------------------|
 * |              模块五：「基于list实现的stack类」              |
 * |---------------------------------------------------------|
 */

namespace my_std
{
    /* stack实现 */

    // 获取信息方法
    template <typename T>
    bool stack<T>::empty() const
    {
        return _data.empty();
    }

    template <typename T>
    int stack<T>::size() const
    {
        return _data.size();
    }

    // 增加元素
    template <typename T>
    void stack<T>::push(const T& value)
    {
        _data.push_back(value);
    }

    // 删除元素
    template <typename T>
    void stack<T>::pop()
    {
        if (empty())
        {
            std::cerr << "my_std::stack::pop 发生错误【栈为空】" << std::endl;
            return;
        }
        _data.pop_back();
    }

    // 访问元素
    template <typename T>
    T& stack<T>::top()
    {
        if (empty())
        {
            std::cerr << "my_std::stack::top 发生错误【栈为空】" << std::endl;
            return _data.back();
        }
        return _data.back();
    }

    template <typename T>
    const T& stack<T>::top() const
    {
        if (empty())
        {
            std::cerr << "my_std::stack::top 发生错误【栈为空】" << std::endl;
            return _data.back();
        }
        return _data.back();
    }
};

/**
 * |---------------------------------------------------------|
 * |                    模块六：「pair类」                      |
 * |---------------------------------------------------------|
 */

namespace my_std
{
    /* pair实现 */

    // 重载运算符(成员函数)
    template <typename T1, typename T2>
    pair<T1, T2>& pair<T1, T2>::operator=(const pair<T1, T2>& other)
    {
        first = other.first;
        second = other.second;
        return *this;
    }

    template <typename T1, typename T2>
    bool pair<T1, T2>::operator==(const pair<T1, T2>& other) const
    {
        return first == other.first && second == other.second;
    }

    template <typename T1, typename T2>
    bool pair<T1, T2>::operator!=(const pair<T1, T2>& other) const
    {
        return !(*this == other);
    }

    // 重载运算符(非成员函数)
    template <class T1, class T2>
    bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second);
    }

    template <class T1, class T2>
    bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return lhs.first > rhs.first || (lhs.first == rhs.first && lhs.second > rhs.second);
    }

    template <class T1, class T2>
    bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return !(lhs > rhs);
    }

    template <class T1, class T2>
    bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return !(lhs < rhs);
    }

    template <class T1, class T2>
    pair<T1, T2> operator+(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return pair<T1, T2>(lhs.first + rhs.first, lhs.second + rhs.second);
    }

    template <class T1, class T2>
    pair<T1, T2> operator-(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return pair<T1, T2>(lhs.first - rhs.first, lhs.second - rhs.second);
    }
};
