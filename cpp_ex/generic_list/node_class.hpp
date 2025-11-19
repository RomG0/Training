#include <Windows.h>

template<typename T> class Node {

private:

    T NodeData;
    Node<T>* NextNode;

public:

    Node(T val) : NodeData(val), NextNode(NULL) {}

    VOID ChangePtr(Node<T>* ptrNextNode) {
        NextNode = ptrNextNode;
    }

    Node<T>* GetNextNode() {
        return NextNode;
    }

    T& GetData() {
        return NodeData;
    }

};

