#include <iostream>
#include <thread>

const int max = 1 << 30;
const int bucketCount = 4;

void compute(int start, u_int64_t *result)
{
  u_int64_t sum = 0;
  int end = start + max / bucketCount < max ? start + max / bucketCount : max;
  for (int i = start; i < end; ++i) 
  {
    sum += i;
  }
  *result = sum;
}

int main()
{
  u_int64_t result = 0;
  int interval = max / bucketCount;
  u_int64_t *res = new u_int64_t[bucketCount]{0};
  std::thread threads[bucketCount];
  auto start = std::chrono::system_clock::now();
  for (int i = 0; i < bucketCount; ++i) 
  {
    threads[i] = std::thread(compute, i * interval, &res[i]);
  }
  for (auto &thread : threads) 
  {
    thread.join();
  }
  for (int i = 0; i < bucketCount;++i) 
  {
    result += res[i];
  }
  delete[] res;
  auto end = std::chrono::system_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "consume time : "<< double(duration.count()) / 1000000 <<  "s" << std::endl;
  std::cout << "sum = " << result << std::endl;
  return 0;
}
