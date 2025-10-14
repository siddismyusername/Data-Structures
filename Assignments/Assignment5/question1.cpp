#include <iostream>
using namespace std;
// WAP to build a simple stock price tracker that keeps a history of
// daily stock prices entered by the user. To allow users to go back
// and view or remove the most recent price, implement a stack
// using a linked list to store these integer prices.
// Implement the following operations:
struct node
{
    int price;
    node* next;
};

// 1. record(price) – Add a new stock price (an integer) to the
// stack.
// 2. remove() – Remove and return the most recent price
// (top of the stack).
// 3. latest() – Return the most recent stock price without
// removing it.
// 4. isEmpty() – Check if there are no prices recorded.