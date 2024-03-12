#include "thread_pool.h"

void thread_pool::init(int count_threads)
{
    threads.resize(count_threads);
}

void thread_pool::add_task(FuncPtr task)
{
    {
        unique_lock<mutex> lock(main_mutex);

        tasks_queue.push(task);
    }
    main_cv.notify_one();
}

void thread_pool::start_working()
{
    for (auto& pair : threads)
    {
        auto thread_function = [this, &pair]()
        {
            while (true)
            {
                FuncPtr task;

                {
                    unique_lock<mutex> lock(main_mutex);
                    main_cv.wait(lock, [this] { return !tasks_queue.empty(); });
                    task = tasks_queue.front();
                    tasks_queue.pop();
                }

                pair.second = true;

                task();

                pair.second = false;
            }
        };

        if (!pair.second)
        {
            pair.first = thread(thread_function);
        }
    }
}


void thread_pool::show_info()
{
    int index{};

    for (auto& thread : threads)
    {
        cout << "Thread " << ++index << ": ";
        cout << (thread.second ? "Working" : "Sleeping") << endl;
    }
}

thread_pool::~thread_pool()
{
    for (auto& thread : threads)
    {
        if (thread.first.joinable())
        {
            thread.first.join();
        }
    }
}

