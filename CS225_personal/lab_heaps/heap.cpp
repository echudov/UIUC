
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

#include <cmath>
#include <algorithm>

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return 2 * (currentIdx) + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return 2 * (currentIdx + 1);
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return (currentIdx - 1) / 2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    size_t left = leftChild(currentIdx);
    size_t right = rightChild(currentIdx);

    return left < _elems.size() || right < _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    size_t left = leftChild(currentIdx);
    size_t right = rightChild(currentIdx);

    if (right < _elems.size())
    {
        if (higherPriority(_elems[left], _elems[right]))
        {
            return left;
        }
        else
        {
            return right;
        }
    }
    else if (left < _elems.size())
    {
        return left;
    }
    else
    {
        return 0;
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    if (currentIdx >= _elems.size() || !hasAChild(currentIdx))
    {
        return;
    }
    size_t bestChild = maxPriorityChild(currentIdx);
    if (higherPriority(_elems[bestChild], _elems[currentIdx]))
    {
        std::swap(_elems[currentIdx], _elems[bestChild]);
        heapifyDown(bestChild);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx]))
    {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T> &elems)
{
    // @TODO Construct a heap using the buildHeap algorithm
    _elems = elems;
    for (int i = parent(_elems.size()); i >= 0; i--)
    {
        heapifyDown(i);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    if (!empty())
    {
        T toReturn = _elems[0];
        std::swap(_elems[0], _elems[_elems.size() - 1]);
        _elems.pop_back();
        if (!empty())
        {
            heapifyDown(0);
        }
        return toReturn;
    }
    return T();
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    if (!empty())
    {
        return _elems[0];
    }
    return T();
}

template <class T, class Compare>
void heap<T, Compare>::push(const T &elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t &idx, const T &elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    _elems[idx] = elem;
    if (!higherPriority(_elems[parent(idx)], elem))
    {
        heapifyUp(idx);
    }
    else if (higherPriority(_elems[maxPriorityChild(idx)], elem))
    {
        heapifyDown(idx);
    }
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    return _elems.size() == 0;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> &heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++)
    {
        heaped.push_back(_elems[i]);
    }
}
