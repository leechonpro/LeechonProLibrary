#ifndef CLFILE_HPP_
#define CLFILE_HPP_
#include "LHeader.hpp"
#include "LPLDefine.hpp"
namespace LPL
{
class CLFile
{
public:
    CLFile();
    CLFile( const CLFile& ) = delete;
    ~CLFile();
    
    LPLResult Initialize();
    void Shutdown();

    LPLResult Save( const std::string &arFileName );
    LPLResult Load( const std::string &arFileName );

    char* GetData();
    void SetData( const char *apInput, size_t aSize );
private:
    std::vector<char> m_buffer;
};
}
#endif//