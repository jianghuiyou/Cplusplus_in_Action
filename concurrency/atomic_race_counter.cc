#include <iostream>
#include <thread>
#include <vector>

std::atomic<bool> ready{false};
std::atomic_flag winner_ok = ATOMIC_FLAG_INIT;

void race_counter(int id)
{
  while (!ready)
  {
    std::this_thread::yield();
  }
  //count to 1m
  for (int i = 0; i < 1000000; ++i);
  while (!winner_ok.test_and_set())
  {
    std::cout << "winner is:" << id << std::endl;
  }
}

int main()
{
  std::vector<std::thread> threads;
  for (int i = 0; i < 10; ++i)
  {
    threads.push_back(std::thread(race_counter, i));
  }
  std::cout << "ready!" << std::endl;
  sleep(1);
  std::cout << "go!" << std::endl;
  ready = true;
  for (auto &thread : threads)
  {
    thread.join();
  }
  return 0;
}