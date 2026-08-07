#include <condition_variable>
#include <cstdlib>
#include <mutex>

template <class T, std::size_t S>
class CircularBuffer {
 public:
  CircularBuffer() : size(size) {}

  void push(const T& v) {
    {
      std::lock_guard<std::mutex> lg(mut);
      if (count < S) {
        buffer[(start + count++) % S] = v;
      } else {
        buffer[start = (start + 1) % S] = v;
      }
    }
    buffer_has_some.notify_one();
  }

  void pop(T& v) {
    {
      std::unique_lock<std::mutex> ul(mut);
      buffer_has_some.wait(ul, [&]() { return count > 0; });
      v = std::move(buffer[start]);
      start = (start + 1) % S;
      --count;
    }
    buffer_has_slot.notify_one();
  }

 private:
  std::array<T, S> buffer;
  std::size_t start = 0;
  std::size_t count = 0;
  std::mutex mut;
  std::condition_variable buffer_has_slot;
  std::condition_variable buffer_has_some;
};