#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
  string getDirections(TreeNode *root, int startValue, int destValue)
  {
    string path1;
    string path2;
    bool bPath1Start;

    findTwo(root, startValue, destValue, path1, path2, bPath1Start);

    if (!bPath1Start)
    {
      swap(path1, path2);
    }

    for (auto &c : path1)
    {
      c = 'U';
    }
    reverse(begin(path2), end(path2));

    return path1 + path2;
  }

  int findTwo(TreeNode *root, int startV, int endV, string &path1, string &path2, bool &bPath1Start)
  {
    if (root->val == startV || root->val == endV)
    {
      bPath1Start = root->val == startV;
      int value = bPath1Start ? endV : startV;
      if (root->left && findOne(root->left, value, path2))
      {
        path2.push_back('L');
        return 2;
      }
      if (root->right && findOne(root->right, value, path2))
      {
        path2.push_back('R');
        return 2;
      }
      return 1;
    }

    int found = root->left ? findTwo(root->left, startV, endV, path1, path2, bPath1Start) : 0;
    if (found == 1)
    {
      path1.push_back('L');
      if (root->right && findOne(root->right, bPath1Start ? endV : startV, path2))
      {
        path2.push_back('R');
        return 2;
      }
      return 1;
    }
    if (found == 0)
    {
      found = root->right ? findTwo(root->right, startV, endV, path1, path2, bPath1Start) : 0;
      if (found == 1)
      {
        path1.push_back('R');
      }
    }
    return found;
  }

  bool findOne(TreeNode *root, int value, string &path)
  {
    if (root->val == value)
    {
      return true;
    }

    if (root->left && findOne(root->left, value, path))
    {
      path.push_back('L');
      return true;
    }
    if (root->right && findOne(root->right, value, path))
    {
      path.push_back('R');
      return true;
    }
    return false;
  }
};

class Solution2
{
public:
  string getDirections(TreeNode *root, int startValue, int destValue)
  {
    string startPath, destPath;
    getPath(root, startValue, startPath);
    getPath(root, destValue, destPath);

    while (!startPath.empty() && !destPath.empty() && startPath.back() == destPath.back())
    {
      startPath.pop_back();
      destPath.pop_back();
    }

    for (auto &c : startPath)
    {
      c = 'U';
    }
    reverse(begin(destPath), end(destPath));
    return startPath + destPath;
  }

  bool getPath(TreeNode *root, int value, string &path)
  {
    if (root->val == value)
    {
      return true;
    }

    if (root->left && getPath(root->left, value, path))
    {
      path.push_back('L');
      return true;
    }
    if (root->right && getPath(root->right, value, path))
    {
      path.push_back('R');
      return true;
    }
    return false;
  }
};