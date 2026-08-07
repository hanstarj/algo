#include <list>
#include <unordered_map>

/*
   1. heap

 */
class LRUCache {
 public:
  using KeyType = int;
  using ValueType = int;

  LRUCache(int capacity) : capacity(capacity) { map.reserve(capacity); }

  /*
     - empty
       -> -1
     - (1, 1), (2, 2), get 1
       -> (2, 2), (1, 1) -> 1
     - (1, 1), (2, 2), get 2
       -> 2
     - (2, 2), get 1
  */
  int get(int key) {
    // 1. find the node in the list
    // 2. if it's the tail, no need to update list. Just return
    // 3. remove the value from the list
    // 4. push to back of the list
    auto iter = map.find(key);
    if (iter == map.end()) {
      return -1;
    }

    auto listIter = list->second;
    if (std::next(listIter) == list.end()) {
      return listIter->second;
    }

    auto pair = *listIter;
    list.erase(listIter);
    list.push_back(pair);
    iter->second = std::prev(list.end());
    return pair.second;
  }

  /*
     - {}, set (1, 1)
       -> {(1,1)}
     - {(1, 1)}, set (2, 2)
       -> {(1,1), (2,2)}
     - {(1, 1), (2, 2)}, set (1, 2)
       -> {(2,2), (1,2)}
     - {(1, 1), (2, 2)}, set (2, 3)
       -> {(1,1), (2,3)}
     - {(1, 1), (2, 2)}, set (3, 3)
       -> {(2,2), (3,3)}
  */
  void put(int key, int value) {
    auto iter = map.find(key);
    if (iter == map.end()) {
      if (map.size() == capacity) {
        auto [victimKey, _] = list.front();
        list.pop_front();
        map.erase(victimKey);
      }

      list.emplace_back(key, value);
      map[key] = std::prev(list.end());
      return;
    }

    auto listIter = iter->second;
    if (std::next(listIter) == list.end()) {
      *listIter = {key, value};
    } else {
      list.erase(listIter);
      list.emplace_back(key, value);
      iter->second = std::prev(list.end());
    }
  }

 private:
  std::unordered_map<KeyType, std::list<ValueType>::iterator> map;
  std::list<std::pair<KeyType, ValueType>> list;
  int capacity;
};