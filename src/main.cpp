#include <iostream>
#include "thread_pool.h"
#include <chrono>

void ThreadInfo()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	cout << " + Start thread: " << std::this_thread::get_id() << endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
	cout << " - End thread: " << std::this_thread::get_id() << endl;
}


int main()
{
	thread_pool pool;

	pool.init(2);

	pool.start_working();

	pool.show_info();

	pool.add_task(ThreadInfo);

	std::this_thread::sleep_for(std::chrono::seconds(2));

	pool.add_task(ThreadInfo);

	std::this_thread::sleep_for(std::chrono::seconds(2));

	pool.show_info();
}
