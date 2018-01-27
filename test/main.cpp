#include <thread>
#include <string>
#include "../shorthash.cpp"

void checkBatch(int thread_no, int start, int finish) 
{
    ShortHash sh;
    std::string str;
    long long int a;
    for (int i=start; i < finish; ++i) {
        str = sh.unique("NEDRYERSON0148878282");
        a+=(long long int)i;
    };
    std::cout << "Thread #" << thread_no << "  " << str.c_str() << "  :  " << a << std::endl;
}

int main() 
{
    const int num_threads = 8;
    std::thread t[num_threads];
    int batch = 2000000;

    // launch our threads
    for (int i = 0; i < 8; ++i) {
        t[i] = std::thread(checkBatch, i, i * batch, (i * batch) + batch -1);
    }

    std::cout << "Launched from main thread\n";
 
    // join our threads with this thread
    for (int i = 0; i < 8; ++i) {
        t[i].join();
    }
    return 0;
}