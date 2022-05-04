#include "Thread.hpp"

#include "Common.h"

using namespace genauto;


void Thread::run()
{
    if (running() || shouldStop()) return;
    callAsync([this]()
    {
        running() = true;
        while (true) {
            if (!this->exec()) {
                this->running() = false;
                return;
            }
            if (this->shouldStop()) {
                dlog("Thread stoped\n");
                this->running() = false;
                this->cleanup();
                return;
            }
        }
    });
}

void Thread::cleanup()
{}

void Thread::stop()
{
    shouldStop_ = true;
}

Thread::Thread()
{
    shouldStop_ = false;
    running_ = false;
}

Thread::~Thread()
{
    if (running()) {
        stop();
        while(running());
    }
}

bool Thread::shouldStop()
{
    return shouldStop_;
}

bool& Thread::running()
{
    return running_;
}