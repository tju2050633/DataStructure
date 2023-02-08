#pragma once
#include <iostream>

/* =============�����������������ռ�my_std���ֹ��std���stl��ͻ============= */

namespace my_std
{
    /**
     * |---------------------------------------------------------|
     * |               ģ��һ������������ʵ�ֵ�list�ࡹ               |
     * |---------------------------------------------------------|
     */

     /* list_node���� */

    template <typename T>
    struct list_node
    {
        T _data;             // ������
        list_node<T>* _prev; // ǰ��ָ��
        list_node<T>* _next; // ���ָ��

        // ���캯��
        list_node() : _prev(nullptr), _next(nullptr) {};
        list_node(const T& data, list_node<T>* next = nullptr, list_node<T>* prev = nullptr)
            : _data(data), _prev(prev), _next(next) {};
    };

    /* list���� */

    template <typename T>
    class list
    {
    private:
        list_node<T>* _head; // ͷָ��
        list_node<T>* _tail; // βָ��
        int _size;           // ��С

    public:
        // ���캯������������
        list();
        list(const list<T>& other);
        ~list();

        // ��ֵ���������
        list<T>& operator=(const list<T>& other);

        // ��ȡ��Ϣ����
        inline bool empty() const; // �ж��Ƿ�Ϊ��
        inline int size() const;   // ��ȡ��С

        // ������
        class iterator
        {
            friend class list<T>;

        private:
            list_node<T>* _ptr;

        public:
            // ���캯��
            iterator(list_node<T>* ptr = nullptr) : _ptr(ptr) {};

            // getter
            inline list_node<T>* get_ptr() const { return _ptr; };

            // ���������

            T& operator*() const;  // ������
            T* operator->() const; // ��Ա����

            iterator& operator++();                        // ǰ��++
            iterator operator++(int);                      // ����++
            iterator& operator--();                        // ǰ��--
            iterator operator--(int);                      // ����--
            iterator operator+=(int);                      // +=
            iterator operator-=(int);                      // -=
            iterator operator+(int) const;                 // ����+
            iterator operator-(int) const;                 // ����-
            friend iterator operator+(int n, iterator& it) // ǰ��+
            {
                return it + n; // ���ú���+
            }

            bool operator==(const iterator& other) const; // һϵ�бȽ������
            bool operator!=(const iterator& other) const;
            bool operator<(const iterator& other) const;
            bool operator<=(const iterator& other) const;
            bool operator>(const iterator& other) const;
            bool operator>=(const iterator& other) const;
        };

        // ��ȡ������
        inline iterator begin(); // ��ȡͷ������
        inline const iterator begin() const;
        inline iterator end(); // ��ȡβ������
        inline const iterator end() const;
        iterator find(const T& data) const; // ͨ�����ݻ�ȡ������

        // ����Ԫ��
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;

        // ����Ԫ��
        void push_front(const T& data);           // ��ͷ������Ԫ��
        void push_back(const T& data);            // ��β������Ԫ��
        void insert(iterator pos, const T& data); // ��ָ��λ�ò���Ԫ��

        // ɾ��Ԫ��
        void pop_front();         // ɾ��ͷ��Ԫ��
        void pop_back();          // ɾ��β��Ԫ��
        void erase(iterator pos); // ɾ��ָ��λ��Ԫ��
        void clear();             // �������
    };

    /**
     * |---------------------------------------------------------|
     * |              ģ���������������ʵ�ֵ�vector�ࡹ              |
     * |---------------------------------------------------------|
     */

#define VECTOR_SIZE 10 // Ĭ������

     /* vector���� */

    template <typename T>
    class vector
    {
    private:
        T* _data;      // ������
        int _size;     // ��С
        int _capacity; // ����

        void _expand();                    // ����
        int calc_capacity(int size) const; // ��������
        void _quick_sort(int, int);        // ��������

    public:
        // ���캯������������
        vector();                       // Ĭ�Ϲ��캯��
        vector(const vector<T>& other); // �������캯��
        vector(T* data, int size);      // ͨ�����鹹��
        vector(int n);                  // ���캯����ָ����ʼ��С
        vector(int n, const T& data);   // ���캯����ָ����С�ͳ�ʼֵ
        ~vector();                      // ��������

        // ���������
        vector<T>& operator=(const vector<T>& other); // ��ֵ
        inline T& operator[](int index);              // �±����
        inline const T& operator[](int index) const;  // �±����

        // ��ȡ��Ϣ����
        inline bool empty() const;   // �ж��Ƿ�Ϊ��
        inline int size() const;     // ��ȡ��С
        inline int capacity() const; // ��ȡ����

        // ����size
        void resize(int n);

        // ������
        class iterator
        {
            friend class vector<T>;

        private:
            T* _ptr;
            T* _begin; // ָ��vector��ͷ��
            int _size; // vector�Ĵ�С

        public:
            // ���캯��
            iterator(T* begin, int size, T* ptr = nullptr)
                : _ptr(ptr), _begin(begin), _size(size) {};

            // getter
            inline T* get_ptr() const { return _ptr; };

            // ���������

            T& operator*() const;  // ������
            T* operator->() const; // ��Ա����

            iterator& operator++();                              // ǰ��++
            iterator operator++(int);                            // ����++
            iterator& operator--();                              // ǰ��--
            iterator operator--(int);                            // ����--
            iterator operator+=(int);                            // +=
            iterator operator-=(int);                            // -=
            iterator operator+(int) const;                       // ����+
            iterator operator-(int) const;                       // ����-
            friend iterator operator+(int n, const iterator& it) // ǰ��+
            {
                return it + n; // ���ú���+
            }

            bool operator==(const iterator& other) const; // һϵ�бȽ������
            bool operator!=(const iterator& other) const;
            bool operator<(const iterator& other) const;
            bool operator<=(const iterator& other) const;
            bool operator>(const iterator& other) const;
            bool operator>=(const iterator& other) const;
        };

        // ��ȡ������
        inline iterator begin(); // ��ȡͷ������
        inline const iterator begin() const;
        inline iterator end(); // ��ȡβ������
        inline const iterator end() const;
        iterator find(const T& data) const; // ͨ�����ݻ�ȡ������

        // ����Ԫ��
        T get(int index) const;             // ��ȡָ��λ��Ԫ��
        void set(int index, const T& data); // ����ָ��λ��Ԫ��
        void fill(const T& data);           // �������

        // ����Ԫ��
        void push_front(const T& data);                  // ��ͷ������Ԫ��
        void push_back(const T& data);                   // ��β������Ԫ��
        void insert(const iterator& pos, const T& data); // ��ָ��λ�ò���Ԫ��
        void insert(int index, const T& data);           // ��ָ��λ�ò���Ԫ��

        // ɾ��Ԫ��
        void pop_front();                                        // ɾ��ͷ��Ԫ��
        void pop_back();                                         // ɾ��β��Ԫ��
        void erase(const iterator& pos);                         // ɾ��ָ��λ��Ԫ��
        void erase(int index);                                   // ɾ��ָ��λ��Ԫ��
        void erase(const iterator& first, const iterator& last); // ɾ��[first, last)����Ԫ��
        void erase(int first, int last);                         // ɾ��[first, last)����Ԫ��
        void clear();                                            // �������

        // ����
        void sort();
    };

    /**
     * |---------------------------------------------------------|
     * |           ģ������������C����ַ���ʵ�ֵ�string�ࡹ           |
     * |---------------------------------------------------------|
     */

     /* string���� */

    class string
    {
    private:
        vector<char> _data; // �ַ�������

    public:
        // ���캯��
        string();                          // Ĭ�Ϲ��캯��
        string(const char* str);           // ͨ��C����ַ�������
        string(const string& other);       // �������캯��
        string(const vector<char>& other); // ͨ��vector����

        // ��������
        ~string() {}

        // ���������
        string& operator=(const string& other);                               // ��ֵ
        string& operator=(const char* str);                                   // ��ֵ
        string& operator=(const vector<char>& other);                         // ��ֵ
        char& operator[](int index);                                          // �±����
        const char& operator[](int index) const;                              // �±����
        friend std::ostream& operator<<(std::ostream& os, const string& str); // �����
        friend std::istream& operator>>(std::istream& is, string& str);       // ������
        string operator+(const string& other) const;                          // ����
        string& operator+=(const string& other);                              // ����
        bool operator==(const string& other) const;                           // �Ƚ�
        bool operator!=(const string& other) const;                           // �Ƚ�
        bool operator<(const string& other) const;                            // �Ƚ�
        bool operator<=(const string& other) const;                           // �Ƚ�
        bool operator>(const string& other) const;                            // �Ƚ�
        bool operator>=(const string& other) const;                           // �Ƚ�

        // ��ȡ��Ϣ����
        inline bool empty() const;   // �ж��Ƿ�Ϊ��
        inline int length() const;   // ��ȡ����
        inline int size() const;     // ��ȡ����
        inline int capacity() const; // ��ȡ����

        // ����Ԫ��
        void append(const string& other);            // ׷���ַ���
        void append(const char* str);                // ׷���ַ���
        void append(const char& c);                  // ׷���ַ�
        void insert(int index, const string& other); // ��ָ��λ�ò����ַ���
        void insert(int index, const char* str);     // ��ָ��λ�ò����ַ���
        void insert(int index, const char& c);       // ��ָ��λ�ò����ַ�

        // ɾ��Ԫ��
        void erase(int index);           // ɾ��ָ��λ��Ԫ��
        void erase(int first, int last); // ɾ��[first, last)����Ԫ��
        void clear();                    // �������

        // �滻Ԫ��
        void replace(int index, const char& c);                 // �滻ָ��λ��Ԫ��
        void replace(int first, int last, const char& c);       // �滻[first, last)����Ԫ��
        void replace(int first, int last, const char* str);     // �滻[first, last)����Ԫ��
        void replace(int first, int last, const string& other); // �滻[first, last)����Ԫ��

        // ����Ԫ��
        int find(const char& c) const;            // �����ַ�
        int find(const char* str) const;          // �����ַ���
        int find(const string& other) const;      // �����ַ���
        string substr(int first, int last) const; // ��ȡ[first, last)�����Ӵ�
        const char* c_str() const;                // ��ȡC����ַ���
    };

    /**
     * |---------------------------------------------------------|
     * |              ģ���ģ�������listʵ�ֵ�queue�ࡹ              |
     * |---------------------------------------------------------|
     */

     /* queue���� */

    template <typename T>
    class queue
    {
    private:
        list<T> _data; // ����

    public:
        // ���캯������������
        queue() {}  // Ĭ�Ϲ��캯��
        ~queue() {} // Ĭ����������

        // ��ȡ��Ϣ����
        inline bool empty() const; // �ж��Ƿ�Ϊ��
        inline int size() const;   // ��ȡ����

        // ����Ԫ��
        void push(const T& value); // ���

        // ɾ��Ԫ��
        void pop(); // ����

        // ����Ԫ��
        T& front(); // ��ȡ����Ԫ��
        const T& front() const;
        T& back(); // ��ȡ��βԪ��
        const T& back() const;
    };

    /**
     * |---------------------------------------------------------|
     * |              ģ���壺������listʵ�ֵ�stack�ࡹ              |
     * |---------------------------------------------------------|
     */

     /* stack���� */

    template <typename T>
    class stack
    {
    private:
        list<T> _data; // ����

    public:
        // ���캯������������
        stack() {}  // Ĭ�Ϲ��캯��
        ~stack() {} // Ĭ����������

        // ��ȡ��Ϣ����
        inline bool empty() const; // �ж��Ƿ�Ϊ��
        inline int size() const;   // ��ȡ����

        // ����Ԫ��
        void push(const T& value); // ��ջ

        // ɾ��Ԫ��
        void pop(); // ��ջ

        // ����Ԫ��
        T& top(); // ��ȡջ��Ԫ��
        const T& top() const;
    };

    /**
     * |---------------------------------------------------------|
     * |                    ģ��������pair�ࡹ                      |
     * |---------------------------------------------------------|
     */

     /* pair���� */
    template <typename T1, typename T2>
    struct pair
    {
        T1 first;  // ��һ��Ԫ��
        T2 second; // �ڶ���Ԫ��

        // ���캯������������
        pair() {}                                                                 // Ĭ�Ϲ��캯��
        pair(const T1& first, const T2& second) : first(first), second(second) {} // ���캯��
        pair(const pair& other) : first(other.first), second(other.second) {}     // �������캯��
        template <class T3, class T4>
        pair(const T3& first, const T4& second) : first(first), second(second) {} // ���캯��(֧����ʽת��)
        ~pair() {}                                                                // Ĭ����������

        // ���������
        pair& operator=(const pair& other);              // ���ظ�ֵ�����
        inline bool operator==(const pair& other) const; // ���ص��������
        inline bool operator!=(const pair& other) const; // ���ز����������
    };

};

/* =============����ʵ�ַ���namespace�⣬�������my_std::==================== */

/**
 * |---------------------------------------------------------|
 * |               ģ��һ������������ʵ�ֵ�list�ࡹ               |
 * |---------------------------------------------------------|
 */

namespace my_std
{
    /* list_nodeʵ�� */

    // ������ʵ�ֹ��캯������������ʵ��

    /* listʵ�� */

    // ���캯������������
    template <typename T>
    my_std::list<T>::list()
    {
        // ��ʼ��ͷβ���
        _head = new list_node<T>();
        _tail = new list_node<T>();
        _head->_next = _tail;
        _tail->_prev = _head;
        _size = 0;
    }

    template <typename T>
    my_std::list<T>::list(const list<T>& other)
    {
        // ����Ĭ�Ϲ��캯��(��ԭʼ�ڴ渲�ǣ�֧��C++11���±�����)
        new (this) list();

        // ��������
        for (my_std::list<T>::iterator it = other.begin(); it != other.end(); ++it)
        {
            push_back(*it);
        }
    }

    template <typename T>
    my_std::list<T>::~list()
    {
        clear();      // ������ݽ��
        delete _head; // ɾ��ͷ���
        delete _tail; // ɾ��β���
    }

    // ��ֵ���������
    template <typename T>
    my_std::list<T>& my_std::list<T>::operator=(const my_std::list<T>& other)
    {
        // ��ֹ���Ҹ�ֵ
        if (this == &other)
            return *this;

        // ������ݽ��
        clear();

        // ��������
        for (my_std::list<T>::iterator it = other.begin(); it != other.end(); ++it)
        {
            push_back(*it);
        }

        return *this;
    }

    // ��ȡ��Ϣ����
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

    // ��������ʵ��
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

    // ��ȡ������
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

    // ����Ԫ��
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

    // ����Ԫ��
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
            std::cerr << "my_std::list::insert �������󡾵�����Խ�硿" << std::endl;
            return;
        }
        list_node<T>* node = new list_node<T>(data);
        node->_next = pos._ptr;
        node->_prev = pos._ptr->_prev;
        pos._ptr->_prev->_next = node;
        pos._ptr->_prev = node;
        ++_size;
    }

    // ɾ��Ԫ��
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
            std::cerr << "my_std::list::erase �������󡾵�����Խ�硿" << std::endl;
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
 * |              ģ���������������ʵ�ֵ�vector�ࡹ              |
 * |---------------------------------------------------------|
 */

namespace my_std
{
    /* vectorʵ�� */

    // private����
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

    // ���캯������������
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

    // ���������
    template <typename T>
    my_std::vector<T>& my_std::vector<T>::operator=(const vector& other)
    {
        // ��ֹ�Ը�ֵ
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
            std::cerr << "my_std::vector::operator[] ���������±�Խ�硿" << std::endl;
            return _data[0];
        }
        return _data[index];
    }

    template <typename T>
    const T& my_std::vector<T>::operator[](int index) const
    {
        if (index < 0 || index >= _size)
        {
            std::cerr << "my_std::vector::operator[] ���������±�Խ�硿" << std::endl;
            return _data[0];
        }
        return _data[index];
    }

    // ��ȡ��Ϣ����
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

    // ����size
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

    // ������
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

    // ��ȡ������
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

    // ����Ԫ��
    template <typename T>
    T my_std::vector<T>::get(int index) const
    {
        if (index < 0 || index >= _size)
        {
            std::cerr << "my_std::vector::get ���������±�Խ�硿" << std::endl;
            return T();
        }
        return _data[index];
    }

    template <typename T>
    void my_std::vector<T>::set(int index, const T& data)
    {
        if (index < 0 || index >= _size)
        {
            std::cerr << "my_std::vector::set ���������±�Խ�硿" << std::endl;
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

    // ����Ԫ��
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
            std::cerr << "my_std::vector::insert ���������±�Խ�硿" << std::endl;
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
            std::cerr << "my_std::vector::insert ���������±�Խ�硿" << std::endl;
            return;
        }

        if (_size == _capacity)
            _expand();

        for (int i = _size; i > index; --i)
            _data[i] = _data[i - 1];

        _data[index] = data;
        ++_size;
    }

    // ɾ��Ԫ��
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
            std::cerr << "my_std::vector::erase ���������±�Խ�硿" << std::endl;
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
            std::cerr << "my_std::vector::erase ���������±�Խ�硿" << std::endl;
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
            std::cerr << "my_std::vector::erase ���������±�Խ�硿" << std::endl;
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
            std::cerr << "my_std::vector::erase ���������±�Խ�硿" << std::endl;
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

    // ����
    template <typename T>
    void my_std::vector<T>::sort()
    {
        // ��������
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
 * |           ģ������������C����ַ���ʵ�ֵ�string�ࡹ           |
 * |---------------------------------------------------------|
 */

namespace my_std
{
    /* stringʵ�� */

    // ���캯��
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

    // ���������
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

    // ��ȡ��Ϣ����
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

    // ����Ԫ��
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
            std::cerr << "my_std::string::insert ���������±�Խ�硿" << std::endl;
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
            std::cerr << "my_std::string::insert ���������±�Խ�硿" << std::endl;
            return;
        }
        _data.insert(index, c);
    }

    // ɾ��Ԫ��
    void my_std::string::erase(int index)
    {
        if (index < 0 || index >= size())
        {
            std::cerr << "my_std::string::erase ���������±�Խ�硿" << std::endl;
            return;
        }
        _data.erase(index);
    }

    void my_std::string::erase(int first, int last)
    {
        if (first < 0 || first >= size() || last < 0 || last >= size() || first > last)
        {
            std::cerr << "my_std::string::erase ���������±�Խ�硿" << std::endl;
            return;
        }
        _data.erase(first, last);
    }

    void my_std::string::clear()
    {
        _data.clear();
        _data.push_back('\0');
    }

    // �滻Ԫ��
    void my_std::string::replace(int index, const char& c)
    {
        if (index < 0 || index >= size())
        {
            std::cerr << "my_std::string::replace ���������±�Խ�硿" << std::endl;
            return;
        }
        _data[index] = c;
    }

    void my_std::string::replace(int first, int last, const char& c)
    {
        if (first < 0 || first >= size() || last < 0 || last > size() || first > last)
        {
            std::cerr << "my_std::string::replace ���������±�Խ�硿" << std::endl;
            return;
        }
        for (int i = first; i < last; ++i)
            _data[i] = c;
    }

    void my_std::string::replace(int first, int last, const char* str)
    {
        if (first < 0 || first >= size() || last < 0 || last > size() || first > last)
        {
            std::cerr << "my_std::string::replace ���������±�Խ�硿" << std::endl;
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

    // ����Ԫ��
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
            std::cerr << "my_std::string::substr ���������±�Խ�硿" << std::endl;
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
 * |              ģ���ģ�������listʵ�ֵ�queue�ࡹ              |
 * |---------------------------------------------------------|
 */

namespace my_std
{
    /* queueʵ�� */

    // ��ȡ��Ϣ����
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

    // ����Ԫ��
    template <typename T>
    void queue<T>::push(const T& value)
    {
        _data.push_back(value);
    }

    // ɾ��Ԫ��
    template <typename T>
    void queue<T>::pop()
    {
        if (empty())
        {
            std::cerr << "my_std::queue::pop �������󡾶���Ϊ�ա�" << std::endl;
            return;
        }
        _data.pop_front();
    }

    // ����Ԫ��
    template <typename T>
    T& queue<T>::front()
    {
        if (empty())
        {
            std::cerr << "my_std::queue::front �������󡾶���Ϊ�ա�" << std::endl;
            return _data.front();
        }
        return _data.front();
    }

    template <typename T>
    const T& queue<T>::front() const
    {
        if (empty())
        {
            std::cerr << "my_std::queue::front �������󡾶���Ϊ�ա�" << std::endl;
            return _data.front();
        }
        return _data.front();
    }

    template <typename T>
    T& queue<T>::back()
    {
        if (empty())
        {
            std::cerr << "my_std::queue::back �������󡾶���Ϊ�ա�" << std::endl;
            return _data.back();
        }
        return _data.back();
    }

    template <typename T>
    const T& queue<T>::back() const
    {
        if (empty())
        {
            std::cerr << "my_std::queue::back �������󡾶���Ϊ�ա�" << std::endl;
            return _data.back();
        }
        return _data.back();
    }
};

/**
 * |---------------------------------------------------------|
 * |              ģ���壺������listʵ�ֵ�stack�ࡹ              |
 * |---------------------------------------------------------|
 */

namespace my_std
{
    /* stackʵ�� */

    // ��ȡ��Ϣ����
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

    // ����Ԫ��
    template <typename T>
    void stack<T>::push(const T& value)
    {
        _data.push_back(value);
    }

    // ɾ��Ԫ��
    template <typename T>
    void stack<T>::pop()
    {
        if (empty())
        {
            std::cerr << "my_std::stack::pop ��������ջΪ�ա�" << std::endl;
            return;
        }
        _data.pop_back();
    }

    // ����Ԫ��
    template <typename T>
    T& stack<T>::top()
    {
        if (empty())
        {
            std::cerr << "my_std::stack::top ��������ջΪ�ա�" << std::endl;
            return _data.back();
        }
        return _data.back();
    }

    template <typename T>
    const T& stack<T>::top() const
    {
        if (empty())
        {
            std::cerr << "my_std::stack::top ��������ջΪ�ա�" << std::endl;
            return _data.back();
        }
        return _data.back();
    }
};

/**
 * |---------------------------------------------------------|
 * |                    ģ��������pair�ࡹ                      |
 * |---------------------------------------------------------|
 */

namespace my_std
{
    /* pairʵ�� */

    // ���������(��Ա����)
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

    // ���������(�ǳ�Ա����)
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
