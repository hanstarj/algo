// provided by leetcode
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};
// provided by leetcode end

#include <vector>
#include <algorithm>

bool Compare(const ListNode *a, const ListNode *b)
{
    return a->val > b->val;
}

ListNode *ListPop(std::vector<ListNode *> &lists)
{
    ListNode *bsf = lists.front();
    std::pop_heap(lists.begin(), lists.end(), Compare);
    if (bsf->next)
    {
        lists.back() = bsf->next;
        std::push_heap(lists.begin(), lists.end(), Compare);
    }
    else
    {
        lists.pop_back();
    }
    return bsf;
}

ListNode *mergeKLists(std::vector<ListNode *> &lists)
{
    lists.erase(
        std::remove_if(
            lists.begin(),
            lists.end(),
            [](const ListNode *node) { return !node; }),
        lists.end());

    if (lists.empty())
        return nullptr;

    std::make_heap(lists.begin(), lists.end(), Compare);
    ListNode *head = ListPop(lists);
    ListNode *tail = head;
    while (lists.size() > 1)
    {
        ListNode *bsf = ListPop(lists);
        tail->next = bsf;
        tail = bsf;
    }
    if (!lists.empty())
        tail->next = lists.front();
    return head;
}

int main()
{
    std::vector<ListNode *> lists;
    mergeKLists(lists);
    return 0;
}