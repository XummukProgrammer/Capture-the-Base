#ifndef __APPLICATION_INCLUDE_FILE__
#define __APPLICATION_INCLUDE_FILE__

namespace Core
{
    class Window;

    class Application final
    {
    public:
        Application() = default;
        ~Application() = default;

    public:
        void exec();

    private:
        void init();
        void deinit();

        void start();

        void initWindow();
        void destroyWindow();

    private:
        Window* _wndPtr = nullptr;
    };

}

#endif // __APPLICATION_INCLUDE_FILE__
