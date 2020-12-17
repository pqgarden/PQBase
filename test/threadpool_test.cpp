#include <iostream>
#include <vector>
#include <chrono>

#include "threadpool.h"

int main()
{
    ThreadPool pool(4);
    std::vector< std::future<int> > results;

    for (int i = 0; i < 8; ++i) 
    {
        results.emplace_back(
            pool.enqueue([i] {
                std::cout << "hello " << i  << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "world " << i << std::endl;
                return i * i;
                })
        );
    }

    for (auto&& result : results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;

    return 0;
}

/*
使用方法
在代码的最开头定义线程池全局变量，如：ThreadPool::ThreadPool rec_keyword_threadpool(5);
在初始化阶段启动线程池，如：rec_keyword_threadpool.StartThreadPool();
在线程池中加入绑定函数，如：std::future<int> result = rec_keyword_threadpool.enqueue(std::bind(&AudioTransform, clientID, accessToken, ref(allText)));
函数运行完毕后取出运行结果，如：int back_transform_int = result.get();
*/