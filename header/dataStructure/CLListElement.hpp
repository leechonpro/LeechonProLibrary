#ifndef CLLIST_ELEMENT_HPP_
#define CLLIST_ELEMENT_HPP_
#include "LHeader.hpp"
#include "LPLDefine.hpp"
namespace LPL
{
template<typename T>
class CLListElement
{
    class iterator
    {
    public:
        iterator();
        iterator( const iterator& ) = delete;
        ~iterator();
        CLListElement<T>& operator++();
        T& operator*();
        bool operator==( const iterator& arInput );
        bool operator!=( const iterator& arInput );
    private:
        CLListElement<T>* mp_data;
    };
public:
    CLListElement();
    CLListElement( const CLListElement& ) = delete;
    ~CLListElement();

    T GetData();
    T& GetReference();
    void SetData( const T aInput );
    void SetLink( const CLListElement* apInput );
    CLListElement* GetLink();
private:
    T m_data;
    CLListElement<T> *m_link;
};

};
#endif