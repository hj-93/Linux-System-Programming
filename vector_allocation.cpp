#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <functional>

template<class Resolution = std::chrono::nanoseconds>
class ExecutionTimer {
public:
    using Clock = std::conditional_t<std::chrono::high_resolution_clock::is_steady,
                                     std::chrono::high_resolution_clock,
                                     std::chrono::steady_clock>;

    ExecutionTimer(std::function<void()> function, int times): mStart {Clock::now()}, repeatTimes{times} {
        for (auto i = 0; i < repeatTimes; ++i) {
          function();
        }
        

    }
    
    ~ExecutionTimer(){
        const auto end = Clock::now();
        
        std::ostringstream strStream;
        strStream << "Average per iteration: "
                  << std::chrono::duration_cast<Resolution>( end - mStart ).count() / repeatTimes
                  << std::endl;
        std::cout << strStream.str() << std::endl;
    }
    
private:
    const Clock::time_point mStart;
    int repeatTimes;
};

int main()
{
    ExecutionTimer([](){std::vector<char>(4 * 1024 * 1024);}, 1000);
    return 0;
}
