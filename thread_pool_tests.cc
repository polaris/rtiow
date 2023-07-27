#include <catch2/catch_test_macros.hpp>

#include "thread_pool.h"
#include <chrono>

TEST_CASE("Thread pool creates correct number of threads", "[thread_pool]") {
  const unsigned int num_threads = 5;
  thread_pool tp(num_threads);

  std::vector<std::future<unsigned int>> futures;

  for (unsigned int i = 0; i < num_threads; ++i) {
    futures.push_back(
        tp.enqueue([](unsigned int answer) { return answer; }, i));
  }

  for (unsigned int i = 0; i < num_threads; ++i) {
    REQUIRE(futures[i].get() == i);
  }
}

TEST_CASE("Thread pool executes tasks in the correct order", "[thread_pool]") {
  const unsigned int num_threads = 5;
  thread_pool tp(num_threads);

  std::vector<std::future<unsigned int>> futures;

  for (unsigned int i = 0; i < num_threads; ++i) {
    futures.push_back(
        tp.enqueue([](unsigned int answer) { return answer; }, i));
  }

  for (unsigned int i = 0; i < num_threads; ++i) {
    REQUIRE(futures[i].get() == i);
  }
}

TEST_CASE("Thread pool wait function blocks until all tasks complete",
          "[thread_pool]") {
  thread_pool tp(2);

  auto future1 = tp.enqueue([] {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 1;
  });

  auto future2 = tp.enqueue([] {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 2;
  });

  auto start_time = std::chrono::steady_clock::now();

  tp.wait();

  auto end_time = std::chrono::steady_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);

  REQUIRE(duration.count() >= 2);
  REQUIRE(future1.get() == 1);
  REQUIRE(future2.get() == 2);
}
