#include <iostream>
#include <iterator>
#include <cstddef>

template<typename T> class Node {

private:

    T NodeData;
    Node<T>* NextNode;

public:

    Node(T val) : NodeData(val), NextNode(nullptr) {}

    void ChangePtr(Node<T>* ptrNextNode) {
        NextNode = ptrNextNode;
    }

    Node<T>* GetNextNode() {
        return NextNode;
    }

    T& GetData() {
        return NodeData;
    }

};


template <typename T> class List {
private:

    Node<T>* head;
    int size;

public:
    List() : head(nullptr), size(0) {}

    ~List() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* nextNode = current->GetNextNode();
            delete current;
            current = nextNode;
        }
    }

    void add(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node<T>* current = head;
            while (current->GetNextNode() != nullptr) {
                current = current->GetNextNode();
            }
            current->ChangePtr(newNode);
        }
        size++;
    }

    int GetSize() {
        return size;
    }


    struct Iterator {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        Iterator(Node<T>* ptr = nullptr) : m_ptr(ptr) {}

        reference operator*() {
            return m_ptr->GetData();
        }

        pointer operator->() const {
            return &(**this);
        }

        Iterator& operator++() {
            if (m_ptr)
                m_ptr = m_ptr->GetNextNode();
            return *this;
        }

        bool operator==(const Iterator& other) const {
            return m_ptr == other.m_ptr;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

    private:
        Node<T>* m_ptr;
    };

    Iterator begin() const {
        return Iterator(head);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

    void display() const {
        for (auto It = begin(); It != end(); ++It) {
            std::cout << *It << " ";

        }

    }

};



int main()
{

    List<char> CharList;
    CharList.add('a');
    CharList.add('a');
    CharList.add('a');
    CharList.display();
    std::cout << CharList.GetSize();
}