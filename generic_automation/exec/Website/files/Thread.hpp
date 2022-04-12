#ifndef __GENAUTO_THREAD_HPP__
#define __GENAUTO_THREAD_HPP__

namespace genauto
{
    class Thread {
    protected:
        bool shouldStop_;
        bool running_;
        virtual bool exec() = 0;
    public:
        void run();
        bool& running();
        bool shouldStop();
        void stop();
        Thread();
        ~Thread();
    };
} // namespace genauto


#endif
