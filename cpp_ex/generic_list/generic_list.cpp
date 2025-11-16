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

    T GetData() {
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


    template<typename T> struct Iterator {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;

        Iterator(Node<T>* ptr) : m_ptr(ptr) {}

        Node<T>* operator->() { return m_ptr; }

        Iterator operator++() {
            m_ptr = m_ptr->GetNextNode();
            return *this;
        }


    private:
        Node<T>* m_ptr;
    };

    void display() const {
        for (auto It = head; It->GetNextNode() != nullptr; It++) {
            std::cout << It->GetData() << " ";

        }
        //Node<T>* current = head;
        //while (current != nullptr) {
        //    current = current->GetNextNode();
        //}
    }

};



int main()
{

    List<char> CharList;
    CharList.add('a');
    CharList.add('a');
    CharList.add('a');
    CharList.display();
    std::cout<<CharList.GetSize();
}

