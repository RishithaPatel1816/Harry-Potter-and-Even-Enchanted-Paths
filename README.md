# Harry-Potter-and-Even-Enchanted-Paths
We want to find even length shortest path using dynamic programming.
This C++ project solves the problem of finding the shortest path with an even number of edges (passages) in an undirected graph representing Hogwarts rooms and secret passages.

---

## Problem Description

Harry Potter needs to retrieve fireworks from a destination room in Hogwarts using the Marauder’s Map. The map shows Hogwarts as an undirected graph with rooms as nodes and secret passages as edges, each having a travel time.

Harry’s challenge is to find the shortest path from a source room to a destination room such that the number of passages (edges) in the path is **even**.

Due to his knowledge from Hermione’s lessons, Harry must implement a **generic minimum priority queue** in C++ using templates, instead of using the STL priority queue.

---

## Features

- Implementation of a **generic min-priority queue** supporting:
  - `push()`
  - `pop()`
  - `top()`
  - `empty()`
  - `size()`
- A `Node` class representing rooms with private attributes and proper getters/setters.
- Overloaded comparison operators for the `Node` class to support priority queue ordering.
- Dijkstra’s algorithm modified to find the shortest path constrained to **even number of edges**.
- Efficient priority queue operations in O(log n) time for insertion and deletion.

---

## Input Format

- The first line contains two integers, `n` and `m` — the number of rooms and number of bidirectional passages.
- Next `n` lines contain unique alphanumeric room IDs.
- Next `m` lines each contain: `ai bi wi`, describing an edge between rooms `ai` and `bi` with travel time `wi`.
- The last line contains the source room ID and the destination room ID.

---

## Output Format

- Print a single integer: the minimum time to reach the destination from the source using a path with an **even number of edges**.
- Print `-1` if no such path exists.

---

## Design Notes

- The priority queue is implemented as a **template class** with interface similar to STL priority queue.
- The `Node` class encapsulates room details, including room ID and current distance estimates.
- Overloading of comparison operators in `Node` enables the priority queue to order nodes based on their tentative distances.
- Dijkstra’s algorithm is adapted to track path parity (even or odd number of edges) by storing distances for both parities separately.

---

## Usage

- Compile the program using a standard C++ compiler (e.g., `g++`).
- Provide input according to the format described.
- The program outputs the shortest even-length path travel time or `-1`.

---

## Limitations and Assumptions

- Room IDs are assumed unique.
- Travel times are non-negative integers.
- The graph is undirected.
- The implemented priority queue does not support decrease-key operations but handles updates by inserting new entries.

---

Feel free to reach out for clarifications or code extensions!
