#ifndef SIMULATE_KEYSTROKES_H
#define SIMULATE_KEYSTROKES_H 
#include <windows.h> 
#include "mingw.mutex.h"
#include "mingw.thread.h"
#include <map> 
#include <chrono> 

using namespace std;
class Sleep_For{
	public:
    template <class callable, class... arguments>
    Sleep_For(int after, callable&& f, arguments&&... args)
    {
        function<typename std::result_of<callable(arguments...)>::type()> task(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));
        this_thread::sleep_for(chrono::nanoseconds(after));
        task();
    }
};

#endif