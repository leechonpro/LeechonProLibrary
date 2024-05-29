#include "utility/LUtil.hpp"
namespace LPL
{
void PrintHello()
{
    std::cout<<"Hello World\n";
}
uint64_t GetTickCount()
{
    uint64_t tick = 0;
#if defined( __linux__ )
    struct timeval tval;
    gettimeofday( &tval, NULL );
    tick = ( tval.tv_sec * 1000 ) + ( tval.tv_usec / 1000 );
#elif defined( _WIN32 )
    tick = GetTickCount64();
#endif 
    return tick;
}
};
