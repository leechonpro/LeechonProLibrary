#ifndef ILTHREAD_HPP_
#define ILTHREAD_HPP_

#include "LHeader.hpp"
#include "LPLDefine.hpp"

namespace LPL
{
class ILThread
{
public:
    ILThread();
    ILThread( const ILThread& ) = delete;
    ~ILThread();
    LPLResult Begin();
    LPLResult Stop();
    LPLResult Wait();
protected:
    virtual void Run() = 0;
    bool IsRunning();
    void SetRunning( const bool aFlag );
private:
    static void Running( ILThread *pInst );
    std::unique_ptr<std::thread> m_pThread;
    bool m_bIsRunning;
};
}
#endif