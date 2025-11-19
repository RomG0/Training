#include "list_class.hpp"

INT main()
{
    List<CHAR> CharList;
    List<CHAR> Charlist2;

    CharList.add('a');
    CharList.add('b');
    CharList.add('v');
    Charlist2.add('a');
    Charlist2.add('c');
    Charlist2.add('w');
    CharList.AppendList(Charlist2);
    CharList.display();
    CharList.DeleteLast();
    CharList.display();
    std::cout << CharList.GetSize();
}