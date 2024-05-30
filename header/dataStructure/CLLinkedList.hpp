#ifndef CLLINKED_LIST_HPP_
#define CLLINKED_LIST_HPP_
#include "LHeader.hpp"
#include "LPLDefine.hpp"
namespace LPL
{
    /*
template<typename T>
class CLListElement
{
    class iterator
    {
    public:
        iterator();
        iterator( const iterator& ) = delete;
        ~iterator();
        CLListElement& opreator++();
        CLListElement& operator*();
        bool operator==( const iterator& arInput );
        bool operator!=( const iterator& arInput );
    private:
        CLListElement<T>* mp_data;
    }
public:
    CLListElement();
    CLListElement( const CLListElement& ) = delete;
    ~CLListElement();

    T getData();
    T& getReference();
    void setData( const T aInput );
    void setLink( const CLListElement* apInput );
    CLListElement* getLink();
private:
    T m_data;
    CLListElement<T> *m_link;
};
class CLLinkedList
{
public:
    CLLinkedList();
    CLLinkedList( const CLLinkedList& ) = delete;
    ~CLLinkedList();

    

private:
    CLListElement* mp_cur;
    CLListElement* mp_head;
    CLListElement* mp_tail;
};
*/
};

#endif