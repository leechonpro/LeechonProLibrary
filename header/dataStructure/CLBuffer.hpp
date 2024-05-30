#ifndef CLBUFFER_HPP_
#define CLBUFFER_HPP_
#include "LHeader.hpp"
#include "LPLDefine.hpp"
namespace LPL
{
class CLBuffer
{
public:
    CLBuffer();
    CLBuffer(const CLBuffer&) = delete;
    ~CLBuffer();
// Push back
    CLBuffer& operator<<( const uint8_t aInput );
    CLBuffer& operator<<( const uint16_t aInput );
    CLBuffer& operator<<( const uint32_t aInput );
    CLBuffer& operator<<( const uint64_t aInput );
    CLBuffer& operator<<( const float aInput );
    CLBuffer& operator<<( const double aInput );
    CLBuffer& operator<<( const std::string aInput );
// Pop front
    CLBuffer& operator>>( uint8_t& arOutput );
    CLBuffer& operator>>( uint16_t& arOutput );
    CLBuffer& operator>>( uint32_t& arOutput );
    CLBuffer& operator>>( uint64_t& arOutput );
    CLBuffer& operator>>( float& arOutput );
    CLBuffer& operator>>( double& arOutput );
    CLBuffer& operator>>( std::string& arOutput );

    void Clear();
    void Reset();
    bool IsEmpty();
protected:
    std::vector<uint8_t> m_dataVec;
    size_t m_dataIndex;
};

}
#endif