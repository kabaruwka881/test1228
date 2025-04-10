#include <limits>
#include <cstddef>

template<typename T>
class Node {
public:
    T key;
    Node* next;
    Node* prev;
    Node(const T& key) : key(key), next(nullptr), prev(nullptr) { };
};

template<typename T>
class List {
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using difference_type = std::ptrdiff_t;
    using size_type = std::size_t;

    Node<T>* head;
    Node<T>* tail;

    List() : head(nullptr), tail(nullptr) { };

    List(const List& new_list) : head(nullptr), tail(nullptr) {
        for (const Node<T>* node = new_list.head; node != nullptr; node = node->next) {
            push_back(node->key);
        }
    }

    List(List& new_list) : head(new_list.head), tail(new_list.tail) {
        new_list.head = nullptr;
        new_list.tail = nullptr;
    }

    List& operator=(List& new_list) {
        for (const Node<T>* node = new_list.head; node != nullptr; node = node->next) {
            push_back(node->key);
        }
        return *this;
    }

    List& operator=(List&& other) {
        head = other.head;
        tail = other.tail;
        other.head = nullptr;
        other.tail = nullptr;
        return *this;
    }

    ~List() { clear(); };

    class const_Iterator {
    public:
        const Node<T>* current;
        const_Iterator(const Node<T>* this_node) { current = this_node; }
        const T& operator*() const { return current->key; }
        const T* operator->() const { return &current->key; }
        const_Iterator& operator++() { current = current->next; return *this; }
        const_Iterator operator++(int) { const_Iterator temp = *this; ++(*this); return temp; }
        const_Iterator& operator--() { current = current->prev; return *this; }
        const_Iterator operator--(int) { const_Iterator temp = *this; --(*this); return temp; }
        bool operator==(const const_Iterator& it) const { return current == it.current; }
        bool operator!=(const const_Iterator& it) const { return current != it.current; }
    };
    const_Iterator cbegin() const { return const_Iterator(head); }
    const_Iterator cend() const { return const_Iterator(nullptr); }

    class Iterator {
    public:
        Node<T>* current = nullptr;
        Iterator(Node<T>* this_node) { current = this_node; }
        T& operator*() { return current->key; }
        T* operator->()  { return &current->key; }
        Iterator& operator++() { current = current->next; return *this; }
        Iterator operator++(int) { Iterator temp = *this; ++(*this); return temp; }
        Iterator& operator--() { current = current->prev; return *this; }
        Iterator operator--(int) { Iterator temp = *this; --(*this); return temp; }
        bool operator==(const Iterator& it) { return current == it.current; }
        bool operator!=(const Iterator& it) { return current != it.current; }
        Iterator& operator=(const Iterator& it) { if (this != it.current) { current = it.current; return *this; } }

    };
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }

    class reversible_Iterator {
    public:
        Node<T>* current;
        reversible_Iterator(Node<T>* this_node) { current = this_node; }
        T& operator*() { return current->key; }
        T* operator->()  { return &current->key; }
        reversible_Iterator& operator++() { this->current = this->current->prev; return *this; }
        reversible_Iterator& operator--() { this->current = this->current->next; return *this; }
        reversible_Iterator operator++(int) { reversible_Iterator temp = *this; ++(*this); return temp; }
        reversible_Iterator operator--(int) { reversible_Iterator temp = *this; --(*this); return temp; }
        bool operator==(const reversible_Iterator& it) const { return current == it.current; }
        bool operator!=(const reversible_Iterator& it) const { return current != it.current; }
    };
    reversible_Iterator rbegin() { return reversible_Iterator(tail); }
    reversible_Iterator rend() { return reversible_Iterator(nullptr); }

    class const_reversible_Iterator {
    public:
        Node<T>* current;
        const_reversible_Iterator(Node<T>* this_node) { current = this_node; }
        T& operator*() { return current->key; }
        T* operator->()  { return &current->key; }
        const_reversible_Iterator& operator++() { this->current = this->current->prev; return *this; }
        const_reversible_Iterator& operator--() { this->current = this->current->next; return *this; }
        const_reversible_Iterator operator++(int) { const_reversible_Iterator temp = *this; ++(*this); return temp; }
        const_reversible_Iterator operator--(int) { const_reversible_Iterator temp = *this; --(*this); return temp; }
        bool operator==(const const_reversible_Iterator& it) const { return current == it.current; }
        bool operator!=(const const_reversible_Iterator& it) const { return current != it.current; }
    };
    const_reversible_Iterator crbegin() { return const_reversible_Iterator(tail); }
    const_reversible_Iterator crend() { return const_reversible_Iterator(nullptr); }

    using iterator = Iterator;
    using const_iterator = const_Iterator;

    Node<T>* front() { return head; }

    Node<T>* back() { return tail; }

    void assign(size_t n, const T& value) {
        clear();
        for (size_t i = 0; i < n; ++i) {
            push_back(value);
        }
    }

    void assign_range(Iterator first, Iterator last) {
        clear();
        for (auto it = first; it != last; ++it) {
            push_back(*first);
        }
    }

    void insert(Iterator it, const T& value) {
        if (it == begin()) {
            push_front(value);
        }
        else if (it == end()) {
            push_back(value);
        }
        else {
            auto this_insert = new Node<T>(value);
            Node<T>* prev = it.current->prev;
            prev->next = this_insert;
            this_insert->prev = prev;
            this_insert->next = it.current;
            it.current->prev = this_insert;
        }
    }

    void insert_range(Iterator pos, Iterator first, Iterator last) {
        for (Iterator it = first; it != last; it++) {
            insert(pos, *first);
        }
    }

    void push_back(const T& key) {
        auto newNode = new Node<T>(key);
        if (tail) {
            tail->next = newNode;
            newNode->prev = tail;
        } else {
            head = newNode;
        }
        tail = newNode;
    };

    void push_front(const T& value) {
        auto newNode = new Node<T>(value);
        if (head) {
            head->prev = newNode;
            newNode->next = head;
        } else {
            tail = newNode;
        }
        head = newNode;
    };

    void pop_back() {
        if (tail) {
            Node<T>* temp = tail;
            tail = tail->prev;
            if (tail) {
                tail->next = nullptr;
            } else {
                head = nullptr;
            }
            delete temp;
        }
    };

    void pop_front() {
        if (head) {
            Node<T>* temp = head;
            head = head->next;
            if (head) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
            delete temp;
        }
    };

    void clear() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    };

    bool empty() {
        return head == nullptr;
    }

    void erase(Iterator it) {
        if (it.current == nullptr)
            return;
        if (it.current == head) {
            pop_front();
        } else if (it.current == tail) {
            pop_back();
        } else {
            Node<T>* prev = it.current->prev;
            Node<T>* next = it.current->next;
            Node<T>* deleted = it.current;
            delete deleted;
            prev->next = next;
            next->prev = prev;
        }
    }

    List<T> merge(List& second_list) {
        Iterator it1 = begin();
        Iterator it2 = second_list.begin();
        List<T> new_list;
        while (it1 != end() && it2 != second_list.end()) {
            if (*it1 <= *it2) {
                new_list.push_back(*it1);
                it1++;
            } else {
                new_list.push_back(*it2);
                it2++;
            }
        }
        while (it1 != end()) {
            new_list.push_back(*it1);
            ++it1;
        }
        while (it2 != second_list.end()) {
            new_list.push_back(*it2);
            ++it2;
        }
        return new_list;
    }

    void remove(const T& value) {
        for (auto it = begin(); it != end(); ) {
            if (*it == value) {
                it = erase(it);
            } else {
                ++it;
            }
        }
    }

    void reverse() {
        Node<T>* current = head;
        while (current) {
            swap(current->prev, current->next);
            current = current->prev;
        }
        swap(head, tail);
    }

    void unique() {
        Node<T>* current = head;
        while (current != nullptr && current->next != nullptr) {
            if (current->key == current->next->key) {
                Node<T>* deleted = current->next;
                current->next = deleted->next;
                if (deleted->next) {
                    deleted->next->prev = current;
                } else {
                    tail = current;
                }
                delete deleted;
            } else {
                current = current->next;
            }
        }
    }

    void splice(Iterator pos, List<T>& this_list) {
        if (this_list.empty())
            return;

        if (pos.current == head) {
            this_list.tail->next = head;
            head->prev = this_list.tail;
            head = this_list.head;
        }
        else if (pos.current == tail) {
            tail->next = this_list.head;
            this_list.head->prev = tail;
            tail = this_list.tail;
        }
        else {
            Node<T>* prev = pos.current->prev;
            prev->next = this_list.head;
            this_list.head->prev = prev;
            this_list.tail->next = pos.current;
            pos.current->prev = this_list.tail;
        }
    }

    int size() {
        Node<T>* temp = head;
        int count = 0;
        while (temp) {
            temp = temp->next;
            count++;
        }
        return count;
    }

    void resize(size_t new_size, const T& value) {
        if (new_size < size()) {
            while (size() > new_size) {
                pop_back();
            }
        } else {
            while (size() < new_size) {
                push_back(value);
            }
        }
    }

    int max_size() { return std::numeric_limits<T>::max(); }
};