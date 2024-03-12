#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>


typedef std::function<void()> FuncPtr;

using std::vector;
using std::queue;
using std::thread;
using std::mutex;
using std::unique_lock;
using std::condition_variable;
using std::pair;
using std::make_pair;

using std::cout;
using std::cin;
using std::endl;


class thread_pool
{
	vector<pair<thread, bool>> threads;
	vector<int> nums_of_threads;
	queue<FuncPtr> tasks_queue;
	mutex main_mutex;
	condition_variable main_cv;
	thread listen_thread;

	int working_threads;

public:

	void init(int);

	void add_task(FuncPtr);

	void start_working();


	~thread_pool();

	// test methods

	void show_info();

};

