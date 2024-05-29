#include "dataStructure/CLBuffer.hpp"

namespace LPL
{
CLBuffer& CLBuffer::operator<<( const uint8_t aInput )
{
    m_sizeVec.push_back( 1 );
    m_dataVec.push_back( aInput );
    return *this;
}

CLBuffer& CLBuffer::operator<<( const uint16_t aInput )
{
    m_sizeVec.push_back( 2 );
    m_dataVec.push_back( static_cast<uint8_t>( ( aInput & 0xff00 ) >> 8 ) );
    m_dataVec.push_back( static_cast<uint8_t>( aInput & 0x00ff ) );

    return *this;
}

CLBuffer& CLBuffer::operator<<( const uint32_t aInput )
{
    m_sizeVec.push_back( 4 );
    m_dataVec.push_back( static_cast<uint8_t>( ( aInput & 0xff000000 ) >> 24 ) );
    m_dataVec.push_back( static_cast<uint8_t>( ( aInput & 0x00ff0000 ) >> 16 ) );
    m_dataVec.push_back( static_cast<uint8_t>( ( aInput & 0x0000ff00 ) >> 8 ) );
    m_dataVec.push_back( static_cast<uint8_t>( aInput & 0x000000ff ) );

    return *this;
}

CLBuffer& CLBuffer::operator<<( const uint64_t aInput )
{
    m_sizeVec.push_back( 8 );
    m_dataVec.push_back( static_cast<uint8_t>( ( aInput & 0xff00000000000000 ) >> 56 ) );
    m_dataVec.push_back( static_cast<uint8_t>( ( aInput & 0x00ff000000000000 ) >> 48 ) );
    m_dataVec.push_back( static_cast<uint8_t>( ( aInput & 0x0000ff0000000000 ) >> 40 ) );
    m_dataVec.push_back( static_cast<uint8_t>( ( aInput & 0x000000ff00000000 ) >> 32 ) );
    m_dataVec.push_back( static_cast<uint8_t>( ( aInput & 0x00000000ff000000 ) >> 24 ) );
    m_dataVec.push_back( static_cast<uint8_t>( ( aInput & 0x0000000000ff0000 ) >> 16 ) );
    m_dataVec.push_back( static_cast<uint8_t>( ( aInput & 0x000000000000ff00 ) >> 8 ) );
    m_dataVec.push_back( static_cast<uint8_t>( aInput & 0x00000000000000ff ) );

    return *this;
}

CLBuffer& CLBuffer::operator<<( const float aInput )
{
    uint32_t data = 0;
    memcpy( &data, &aInput, 4 );
    (*this) << data;

    return *this;    
}
CLBuffer& CLBuffer::operator<<( const double aInput )
{
    uint64_t data = 0;
    memcpy( &data, &aInput, 8 );
    (*this) << data;

    return *this;    
}
CLBuffer& CLBuffer::operator<<( const std::string aInput )
{
    char ch = '\0';
    const size_t size = aInput.size();
    m_sizeVec.push_back( size + 1 );
    for( size_t idx = 0; idx < size; idx++ )
    {
        m_dataVec.push_back( aInput.at( idx ) );
    }
    m_dataVec.push_back( static_cast<uint8_t>( 0 ) );

    return *this;    
}

CLBuffer& CLBuffer::operator>>( uint8_t& arOutput )
{
    const size_t size = m_dataVec.size();
    if( m_dataIndex < size )
    {
        arOutput = m_dataVec[m_dataIndex];
        m_dataIndex += 1;
    }
    return *this;
}

CLBuffer& CLBuffer::operator>>( uint16_t& arOutput )
{
    const size_t size = m_dataVec.size();
    if( ( m_dataIndex + 1 )< size )
    {
        arOutput = ( static_cast<uint16_t>( m_dataVec[m_dataIndex] ) << 8 ) |
                    static_cast<uint16_t>( m_dataVec[m_dataIndex + 1] );
        m_dataIndex += 2;
    }
    return *this;
}

CLBuffer& CLBuffer::operator>>( uint32_t& arOutput )
{
    const size_t size = m_dataVec.size();
    if( ( m_dataIndex + 3 ) < size )
    {
        arOutput = ( static_cast<uint32_t>( m_dataVec[m_dataIndex] ) << 24 ) |
                   ( static_cast<uint32_t>( m_dataVec[m_dataIndex + 1] ) << 16 ) |
                   ( static_cast<uint32_t>( m_dataVec[m_dataIndex + 2] ) << 8 ) |
                    static_cast<uint32_t>( m_dataVec[m_dataIndex + 3] );
        m_dataIndex += 4;
    }
    return *this;
}

CLBuffer& CLBuffer::operator>>( uint64_t& arOutput )
{
    const size_t size = m_dataVec.size();
    if( ( m_dataIndex + 7 ) < size )
    {
        arOutput = ( static_cast<uint64_t>( m_dataVec[m_dataIndex] ) << 56 ) |
                   ( static_cast<uint64_t>( m_dataVec[m_dataIndex + 1] ) << 48 ) |
                   ( static_cast<uint64_t>( m_dataVec[m_dataIndex + 2] ) << 40 ) |
                   ( static_cast<uint64_t>( m_dataVec[m_dataIndex + 3] ) << 32 ) |
                   ( static_cast<uint64_t>( m_dataVec[m_dataIndex + 4] ) << 24 ) |
                   ( static_cast<uint64_t>( m_dataVec[m_dataIndex + 5] ) << 16 ) |
                   ( static_cast<uint64_t>( m_dataVec[m_dataIndex + 6] ) << 8 ) |
                    static_cast<uint64_t>( m_dataVec[m_dataIndex + 7] );
        m_dataIndex += 8;
    }
    return *this;
}

CLBuffer& CLBuffer::operator>>( float& arOutput )
{
    uint32_t temp = 0;
    (*this) >> temp;
    memcpy( &arOutput, &temp, 4 );
    return *this;
}

CLBuffer& CLBuffer::operator>>( double& arOutput )
{
    uint64_t temp = 0;
    (*this) >> temp;
    memcpy( &arOutput, &temp, 8 );
    return *this;
}

CLBuffer& CLBuffer::operator>>( std::string& arOutput )
{
    char ch[2] = {'\0', '\0'};
    arOutput = "";
    do{
        uint8_t data = 0;
        (*this) >> data;
        ch[0] = static_cast<char>( data );

        arOutput += ch;
    }while( ch[0] != '\0' );
    
    return *this;
}


void CLBuffer::Clear()
{

}

void CLBuffer::Reset()
{

}

bool CLBuffer::IsEmpty()
{
    return m_dataVec.empty();
}
};