#include <iostream>
#include "QUEUE.H"

using std::cout;
using std::endl;

int main()
{
    Queue<int> intQueue;

    intQueue.Enqueue(10);
    intQueue.Enqueue(20);

    return 0;
}
