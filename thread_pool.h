#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <functional>
#include <future>
#include <iostream>
#include <queue>
#include <thread>
#include <vector>

class thread_pool {
public:
  thread_pool(int threads) : stop(false), active_tasks(0) {
    for (int i = 0; i < threads; ++i)
      workers.emplace_back([this] {
        for (;;) {
          std::function<void()> task;

          {
            std::unique_lock<std::mutex> lock(this->queue_mutex);
            this->condition.wait(
                lock, [this] { return this->stop || !this->tasks.empty(); });
            if (this->stop && this->tasks.empty())
              return;
            task = std::move(this->tasks.front());
            this->tasks.pop();
          }

          task();
        }
      });
  }

  template <class F, class... Args>
  auto enqueue(F &&f, Args &&...args)
      -> std::future<typename std::invoke_result<F, Args...>::type> {
    using return_type = typename std::invoke_result<F, Args...>::type;

    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));

    std::future<return_type> res = task->get_future();
    {
      std::unique_lock<std::mutex> lock(queue_mutex);

      if (stop)
        throw std::runtime_error("enqueue on stopped ThreadPool");

      tasks.emplace([this, task]() {
        (*task)();
        std::unique_lock<std::mutex> lock(this->queue_mutex);
        --this->active_tasks;
        this->condition.notify_all();
      });
      ++this->active_tasks;
    }
    condition.notify_one();
    return res;
  }

  void wait() {
    std::unique_lock<std::mutex> lock(queue_mutex);
    condition.wait(lock, [this] {
      return this->tasks.empty() && this->active_tasks == 0;
    });
  }

  ~thread_pool() {
    {
      std::unique_lock<std::mutex> lock(queue_mutex);
      stop = true;
    }
    condition.notify_all();
    for (std::thread &worker : workers)
      worker.join();
  }

private:
  std::vector<std::thread> workers;
  std::queue<std::function<void()>> tasks;
  std::mutex queue_mutex;
  std::condition_variable condition;
  bool stop;
  std::atomic<int> active_tasks;
};

#endif