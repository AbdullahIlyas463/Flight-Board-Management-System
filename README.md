# Flight-Board-Management-System
A template-based C++ AVL Tree implementation for managing a flight board system, featuring automatic self-balancing rotations, rotation statistics, tree analytics, and an interactive CLI menu.

# Flight Board Management System (C++ AVL Tree)

A robust, template-based **AVL Tree (Self-Balancing Binary Search Tree)** implementation in C++ designed to manage a flight schedule and board efficiently. This project demonstrates advanced data structures and algorithms, specifically focusing on self-balancing mechanics (LL, RR, LR, and RL rotations), custom memory management, operator overloading, and an interactive command-line interface (CLI).

## Features

- **Generic AVL Tree Template (`AvlTree<T>`)**: Reusable template class capable of managing any comparable data type while maintaining strict $O(\log n)$ height balance.
- **Custom `Flight` Entity**: Stores flight records with unique **flight numbers**, **destinations**, and **available seats**, utilizing overloaded comparison operators (`<`, `>`, `==`) and stream insertion (`<<`).
- **Self-Balancing Rotations & Tracking**:
  - Automatically handles balance factors after insertions and deletions.
  - Performs **Right (LL)**, **Left (RR)**, **Left-Right (LR)**, and **Right-Left (RL)** rotations.
  - Tracks and outputs detailed **rotation statistics** and imbalance logs in real time.
- **Traversals & Tree Analytics**:
  - Tree Traversals: **In-order** (sorted), **Pre-order**, and **Post-order**.
  - Tree Structure Visualizer: Prints the tree sideways with balance factors.
  - Board Metrics: Track height, total node count, leaf node count, and balance validation.
- **Memory Safety**: Deep copying via copy constructors, assignment operators, custom cloning (`clone()`), and a recursive destructor (`clear()`) to prevent memory leaks.
- **Interactive CLI Menu**: A comprehensive menu system to test and monitor all flight board features seamlessly.


## Project Structure
├── main.cpp       # Contains Flight class, AvlTree template class, and interactive CLI menu
└── README.md      # Project documentation


Interactive Menu Guide
Upon launching the application, you will be greeted with the following menu:

1. Add flight               
2. Cancel flight          
3. Search flight          
4. Display InOrder        
5. Display PreOrder       
6. Display PostOrder      
7. Display Tree Structure 
8. Board Height
9. Total Flight Count
10. Find Highest / Lowest
11. Balance Check
12. Count Leaf Flights
13. Rotation Statistics
14. Copy Board
15. Clear Board
16. Display Saved Copy
0.  Exit
