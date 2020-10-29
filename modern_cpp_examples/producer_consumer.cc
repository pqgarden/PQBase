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
	bool notified = false; // ֪ͨ�ź�

	//������
	auto producer = [&]() {
		for (size_t i = 0; ; i++)
		{
			std::this_thread::sleep_for(std::chrono::microseconds(900));
			std::unique_lock<std::mutex> lock(mutex);
			std::cout << "producing " << i << std::endl;
			produced_nums.push(i);
			notified = true;
			cv.notify_all(); // �˴�Ҳ����ʹ�� notify_one
		}
	};

	//������
	auto cusumer = [&]() {
		while (true)
		{
			std::unique_lock<std::mutex> lock(mutex);
			while (!notified)
			{
				// ������ٻ���
				cv.wait(lock);
			}
			// ����ȡ������ʹ���������л��������������ѿ�ǰ��������
			lock.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // ����������������
			lock.lock();
			while (!produced_nums.empty())
			{
				std::cout << "consuming " << produced_nums.front() << std::endl;
				produced_nums.pop();
			}
			notified = false;
		}
	};


	// �ֱ��ڲ�ͬ���߳�������
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