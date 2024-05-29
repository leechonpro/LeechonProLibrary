#include "utility/CLFile.hpp"
namespace LPL
{

CLFile::CLFile()
{

}

CLFile::~CLFile()
{
    Shutdown();
}

LPLResult CLFile::Initialize()
{
    //do Nothing
    return LROK;
}
void CLFile::Shutdown()
{
    //do Nothing
}

LPLResult CLFile::Save( const std::string &arFileName )
{
    if( true == m_buffer.empty() )
    {
        return LRNODATA;
    }
    
    std::ofstream out( arFileName );

    std::copy( m_buffer.begin(), m_buffer.end(),std::ostreambuf_iterator<char>( out ) );

    out.close();

    return LROK;
}
LPLResult CLFile::Load( const std::string &arFileName )
{
    std::ifstream in( arFileName );
    
    if( in.is_open() )
    {
        m_buffer = std::vector<char>( (std::istreambuf_iterator<char>( in ) ), std::istreambuf_iterator<char>() );
        in.close();
        return LRNOFILE;
    }
    
    return LROK;
}

char* CLFile::GetData()
{
    size_t size = m_buffer.size();
    if( 0 == size )
    {
        return NULL;
    }

    char *pResult = new char[size];
    memcpy( pResult, &m_buffer[0], size );

    return pResult;
}

void CLFile::SetData( const char *apInput, size_t aSize )
{
    m_buffer.clear();
    m_buffer.reserve( aSize );
    
    for( size_t idx = 0; idx < aSize; idx++ )
    {
        m_buffer.push_back( apInput[idx] );
    }
}

}