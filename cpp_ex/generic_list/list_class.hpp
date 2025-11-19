#include "node_class.hpp"
#include <iostream>
#include <iterator>
#include <cstddef>

template <typename T> class List {
private:

    Node<T>* head;
    INT size;

public:

    List() : head(NULL), size(0) {}

    INT GetSize() { return size; }

    class Iterator {
    private:

        Node<T>* m_ptr;

    public:

        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        Iterator(Node<T>* ptr = NULL) : m_ptr(ptr) {}

        pointer operator->() const {
            return m_ptr;
        }

        reference operator*() {
            return m_ptr->GetData();
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
            return !(m_ptr == other.m_ptr);
        }
        Node<T>* GetItPtr() {
            return m_ptr;
        }

    };

    Iterator begin() const {
        return Iterator(head);
    }

    Iterator end() const {
        return Iterator(NULL);
    }

    Node<T>* GetLastNode() const {

        Node<T>* last;

        last = NULL;

        for (Iterator It = begin(); It != end(); ++It) {
            last = It.GetItPtr();
        }
        return last;
    }

    VOID DeleteLast() {

        Node<T>* last;

        last = nullptr;

        for (Iterator It = begin(); It.GetItPtr()->GetNextNode() != NULL; ++It) {
            last = It.GetItPtr();
        }
        last->ChangePtr(NULL);
        size--;
    }

    VOID add(T val) {

        Node<T>* newNode;

        newNode = new Node<T>(val);

        if (head == NULL) {
            head = newNode;
        }
        else {
            GetLastNode()->ChangePtr(newNode);
        }
        size++;
    }

    VOID addExisting(Node<T>* existingNode) {
        if (head == NULL) {
            head = existingNode;
        }
        else {
            GetLastNode()->ChangePtr(existingNode);
        }
    }

    VOID display() const {
        for (auto It = begin(); It != end(); ++It) {
            std::cout << *It << " ";
        }
        std::cout << "\n";
    }
    VOID AppendList(List secondList) {

        Node<T>* secondHead;

        secondHead = secondList.head;

        if (secondHead) { addExisting(secondHead); size += secondList.size; }

    }
};