#include "multiThreading/ILThread.hpp"
namespace LPL
{
    
ILThread::ILThread() :
m_bIsRunning( false )
{
}


ILThread::~ILThread()
{
    Stop();
}

LPLResult ILThread::Begin()
{
    LPLResult result = LRALREADYDONE;
    if( false == IsRunning() )
    {
        SetRunning( true );
        if( NULL != m_pThread )
        {
            m_pThread.reset();
        }

        m_pThread = std::make_unique<std::thread>( ILThread::Running, this );
        
        if( NULL == m_pThread )
        {
            SetRunning( false );
        }
        else
        {
            result = LROK;
        }
    }

    return result;
}

LPLResult ILThread::Stop()
{
    SetRunning( false );
    LPLResult result = Wait();
    return result;
}

LPLResult ILThread::Wait()
{
    LPLResult result = LRALREADYDONE;
    if( NULL != m_pThread )
    {
        m_pThread->join();
        m_pThread.reset();
        SetRunning( false );
        result = LROK;
    }
    return result;
}

bool ILThread::IsRunning()
{
    return m_bIsRunning;
}

void ILThread::SetRunning( const bool aFlag )
{
    m_bIsRunning = false;
}

void ILThread::Running( ILThread *pInst )
{
    pInst->Run();
}
}