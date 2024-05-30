#include "dataStructure/CLListElement.hpp"

namespace LPL
{
template<typename T>
CLListElement<T>::iterator::iterator() : mp_data( NULL )
{

}

template<typename T>
CLListElement<T>::iterator::~iterator()
{
    mp_data = NULL;
}

template<typename T> 
CLListElement<T>& CLListElement<T>::iterator::operator++()
{
    if( NULL != mp_data )
    {
        mp_data = mp_data->m_link;
    }
    return *mp_data;
}

template<typename T> 
T& CLListElement<T>::iterator::operator*()
{
    if( NULL != mp_data )
    {
        return mp_data->m_data;
    }
    return T();
}

template<typename T> 
bool CLListElement<T>::iterator::operator==( const iterator& arInput )
{
    if( NULL != mp_data )
    {
        return mp_data->m_data == arInput.m_data;
    }
    return false;
}

template<typename T> 
bool CLListElement<T>::iterator::operator!=( const iterator& arInput )
{
    if( NULL != mp_data )
    {
        return mp_data->m_data == arInput.m_data;
    }
    return true;
}
template<typename T> 
CLListElement<T>::CLListElement() : m_data( T() ), m_link(NULL)
{

}

template<typename T> 
CLListElement<T>::~CLListElement()
{
    if( NULL != m_link )
    {
        delete m_link;
        m_link = NULL;
    }
}

template<typename T> 
T CLListElement<T>::GetData()
{
    return m_data;
}

template<typename T> 
T& CLListElement<T>::GetReference()
{
    return m_data;
}

template<typename T> 
void CLListElement<T>::SetData( const T aInput )
{
    m_data = aInput;
}

template<typename T>
void CLListElement<T>::SetLink( const CLListElement* apInput )
{
    m_link = apInput;
}

template<typename T>
CLListElement<T>* CLListElement<T>::GetLink()
{
    return m_link;
}
};
