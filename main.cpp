#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <functional>
#include <thread>

template<typename T>
class ThreadSafeQueue
{
public:
    ThreadSafeQueue() {}

    void push(const T& value)
    {
       std::lock_guard<std::mutex> lock(mutex);
        queue.push(value);
    }

    void pop()
    {
        std::lock_guard<std::mutex> lock(mutex);
        queue.pop();
    }

    size_t size()
    {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.size();
    }

    bool empty()
    {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.empty();
    }

private:
    std::queue<T> queue;
    std::mutex mutex;
};

class ThreadPool
{
public:
    ThreadPool(int numThreads) : stop(false)
    {
        for (int i = 0; i < numThreads; ++i)
        {
            threads.emplace_back([this]() {
                while (true)
                {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(queueMutex);
                        condition.wait(lock, [this]() { return stop || !taskQueue.empty(); });
                        if (stop && taskQueue.empty()) {
                            return;
                        }
                        task = std::move(taskQueue.front());
                        taskQueue.pop();
                    }
                    task();
                }
            });
        }
    }

    ~ThreadPool()
    {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread& thread : threads) {
            thread.join();
        }
    }

    template<typename F, typename... Args>
    void enqueue(F&& f, Args&&... args)
    {
        auto task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            taskQueue.push(task);
        }
        condition.notify_one();
    }

private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> taskQueue;
    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop;
};

std::queue<int> queue;
std::mutex mutex;

void producer(ThreadSafeQueue<int>& threadSafeQueue)
{
    for (int i = 0; i < 10; ++i)
    {
        std::lock_guard<std::mutex> lock(mutex);
        queue.push(i);
        std::cout << "Producer: " << i << std::endl;
        threadSafeQueue.push(i);
    }
}

void consumer(ThreadSafeQueue<int>& threadSafeQueue)
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mutex); // Add argument list for std::unique_lock
        if (queue.empty()) {
            break;
        }
        int value = queue.front();
        queue.pop();
        std::cout << "Consumer: " << value << std::endl;
    }
}

int main() {
    ThreadSafeQueue<int> threadSafeQueue;
    ThreadPool threadPool(2);

    threadPool.enqueue(producer, std::ref(threadSafeQueue));
    threadPool.enqueue(consumer, std::ref(threadSafeQueue));

    return 0;
}