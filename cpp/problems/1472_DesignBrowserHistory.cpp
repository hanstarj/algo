#include <algorithm>
#include <string>
#include <vector>

// a -> b -> back (1)
// ^a -> b

class BrowserHistory {
 public:
  BrowserHistory(std::string homepage) : history{std::move(homepage)}, cursor(0) {}

  void visit(std::string url) {
    history.erase(history.begin() + cursor + 1, history.end());
    history.push_back(std::move(url));
    ++cursor;
  }

  std::string back(int steps) {
    cursor = std::max(0, cursor - steps);
    return history[cursor];
  }

  std::string forward(int steps) {
    cursor = std::min(int(history.size()) - 1, cursor + steps);
    return history[cursor];
  }

  std::vector<std::string> history;
  int cursor;
};
/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */