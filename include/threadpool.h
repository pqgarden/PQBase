#pragma once

#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_

#include <vector>
#include <queue>
#include <atomic>
#include <future>
#include <stdexcept>

class ThreadPool
{
public:
	ThreadPool(size_t size = 4) 
	{
		int nThreads = size;
		if(nThreads <= 0)
		{
			nThreads = std::thread::hardware_concurrency();
			nThreads = (nThreads == 0 ? 2 : nThreads);
		}
		addThread(nThreads); 
	}
	
	~ThreadPool()
	{
		_stop = true;
		
		_task_cv.notify_all();
		
		for( auto& t : _pool){
			if(t.joinable()){
				t.join();
			}
		}
	}
	
	// Two ways to invoking class mem function:
	// use bind, enqueue(std::bind(&Dog::sayHello, &dog));
	// use mem_fn, enqueue(std::mem_fn(&Dog::sayHello), this);

	template<class F, class... Args>
	auto enqueue(F&& f, Args&&... args) -> std::future<decltype(f(args...))>
	{
		using return_type = decltype(f(args...));
		
		// 把函数入口及参数,打包(绑定)
		auto task = std::make_shared<std::packaged_task<return_type()>>(
			std::bind(std::forward<F>(f), std::forward<Args>(args)...)
		); 
		
		std::future<return_type> future = task->get_future();
		
		{    // 添加任务到队列
			std::lock_guard<std::mutex> lock{ _mutex };

			// don't allow enqueueing after stopping the pool
			if (_stop)
				throw std::runtime_error("ThreadPool is stopped.");

			_tasks.emplace([task](){ 
				(*task)();
			});
		}

		_task_cv.notify_one(); // 唤醒一个线程执行
		
		return future;
	}

	void addThread(size_t size)
	{
		for (size_t i = 0; i < size; ++i)
		{   
			_pool.emplace_back( [this]{
				while (!_stop)
				{
					std::function<void()> task;  // 获取一个待执行的 task

					{
						std::unique_lock<std::mutex> lock{ _mutex };
						_task_cv.wait(lock, [this]{
								return _stop || !_tasks.empty();
						});   // wait 直到有 task
						
						if (_stop && _tasks.empty())
							return;
						
						task = std::move(_tasks.front()); // 按先进先出从队列取一个task
						_tasks.pop();
					}

					task();//执行任务

				}
			});
		}
	}
	
private:
	ThreadPool(const ThreadPool&)= delete;
	ThreadPool(ThreadPool&&) = delete;
	ThreadPool& operator=(const ThreadPool&) = delete;
	ThreadPool& operator=(ThreadPool&&) = delete;

	// need to keep track of threads so we can join them
	std::vector<std::thread> _pool;

	// the task queue
	std::queue<std::function<void()>> _tasks;

	// synchronization
	std::mutex _mutex;
	std::condition_variable _task_cv; // 条件

	std::atomic<bool> _stop { false }; 

};

#endif 