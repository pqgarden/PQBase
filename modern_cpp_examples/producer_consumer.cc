#include <iostream>
#include <thread>
#include <queue>
#include <memory>
#include <chrono>
#include <mutex>
#include <condition_variable>

#include <vector>


int main()
{
	std::queue<int> produced_nums;
	std::mutex mutex;
	std::condition_variable cv;
	bool notified = false; // 通知信号

	//生产者
	auto producer = [&]() {
		for (size_t i = 0; ; i++)
		{
			std::this_thread::sleep_for(std::chrono::microseconds(900));
			std::unique_lock<std::mutex> lock(mutex);
			std::cout << "producing " << i << std::endl;
			produced_nums.push(i);
			notified = true;
			cv.notify_all(); // 此处也可以使用 notify_one
		}
	};

	//消费者
	auto cusumer = [&]() {
		while (true)
		{
			std::unique_lock<std::mutex> lock(mutex);
			while (!notified)
			{
				// 避免虚假唤醒
				cv.wait(lock);
			}
			// 短暂取消锁，使得生产者有机会在消费者消费空前继续生产
			lock.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 消费者慢于生产者
			lock.lock();
			while (!produced_nums.empty())
			{
				std::cout << "consuming " << produced_nums.front() << std::endl;
				produced_nums.pop();
			}
			notified = false;
		}
	};


	// 分别在不同的线程中运行
	std::thread p(producer);
	std::vector<std::thread> cs;
	cs.emplace_back(std::thread(cusumer));
	cs.emplace_back(std::thread(cusumer));

	p.join();
	for (auto& v : cs){
		v.join();
	}

	return 0;
}