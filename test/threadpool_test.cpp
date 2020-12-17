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
ʹ�÷���
�ڴ�����ͷ�����̳߳�ȫ�ֱ������磺ThreadPool::ThreadPool rec_keyword_threadpool(5);
�ڳ�ʼ���׶������̳߳أ��磺rec_keyword_threadpool.StartThreadPool();
���̳߳��м���󶨺������磺std::future<int> result = rec_keyword_threadpool.enqueue(std::bind(&AudioTransform, clientID, accessToken, ref(allText)));
����������Ϻ�ȡ�����н�����磺int back_transform_int = result.get();
*/