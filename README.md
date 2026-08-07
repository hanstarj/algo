# Algorithms and Data Structures
for practice.

## Layout
* `cpp/` — algorithms, data structures, and problems in C++17
* `rust/` — Cargo workspace, problems only for now (Rust 1.97.1, edition 2024)

## Algorithms
### Graph
* [Kruskal](cpp/algorithms/graph/Kruskal.cpp)
* [Prim](cpp/algorithms/graph/Prim.cpp)
* [Dijkstra](cpp/algorithms/graph/Dijkstra.cpp)

### Sort
* Bucket Sort
* [Heap Sort](cpp/algorithms/sort/HeapSort.cpp)
* [Insertion Sort](cpp/algorithms/sort/InsertionSort.cpp)
* [Merge Sort](cpp/algorithms/sort/MergeSort.cpp)
* [Selection Sort](cpp/algorithms/sort/SelectionSort.cpp)
* [Quick Sort](cpp/algorithms/sort/QuickSort.cpp)

## Data Structures
### Array
* [Stack](cpp/data_structures/Stack.cpp)
* [Queue](cpp/data_structures/Queue.cpp)
* Dequeue

### List
* [Singly-Linked List](cpp/data_structures/SinglyLinkedList.cpp)
* Skip List
* [Doubly-Linked List](cpp/data_structures/DoublyLinkedList.cpp)

### Tree
* Trie Tree
* Binary Tree
* Red-Black Tree

## Problems
* C++: one standalone file per problem in [cpp/problems](cpp/problems), named `<id>_<Name>.cpp`
* Rust: one module per problem in [rust/problems/src](rust/problems/src), named `p<id padded to 4>_<snake_case_name>.rs`, registered in `lib.rs` and covered by `#[cfg(test)]` tests

```
cd rust && cargo test
```
