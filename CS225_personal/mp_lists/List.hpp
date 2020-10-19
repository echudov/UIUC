/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List()
{
  // @TODO: graded in MP3.1
  ListNode *head_ = NULL;
  ListNode *tail_ = NULL;
  length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const
{
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const
{
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy()
{
  /// @todo Graded in MP3.1
  if (length_ == 0)
  {
    return;
  }
  ListNode *current = head_;
  ListNode *toDelete;
  while (current != NULL)
  {
    toDelete = current;
    current = current->next;
    delete toDelete;
  }
  head_ = NULL;
  tail_ = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const &ndata)
{
  /// @todo Graded in MP3.1
  ListNode *newNode = new ListNode(ndata);

  if (length_ == 0)
  {
    head_ = newNode;
    tail_ = newNode;
    newNode->prev = nullptr;
    newNode->next = nullptr;
  }
  else
  {
    newNode->next = head_;
    newNode->prev = nullptr;
    head_->prev = newNode;
    head_ = newNode;
  }
  ++length_;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T &ndata)
{
  /// @todo Graded in MP3.1
  ListNode *newNode = new ListNode(ndata);

  if (length_ == 0)
  {
    head_ = newNode;
    tail_ = newNode;
    newNode->prev = nullptr;
    newNode->next = nullptr;
  }
  else
  {
    newNode->prev = tail_;
    newNode->next = nullptr;
    tail_->next = newNode;
    tail_ = newNode;
  }
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode *List<T>::split(ListNode *start, int splitPoint)
{
  /// @todo Graded in MP3.1
  if (start == NULL)
    return NULL;
  ListNode *curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++)
  {
    curr = curr->next;
  }

  if (curr != NULL)
  {
    if (curr->prev != NULL)
      curr->prev->next = NULL;
    tail_ = curr->prev;
    curr->prev = NULL;
  }

  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate()
{
  // @todo Graded in MP3.1
  ListNode *first = head_;
  ListNode *second, *third, *previousGroup, *nextGroup, *tmp;

  for (int i = 0; i < length_ / 3; ++i)
  {
    previousGroup = first->prev;
    second = first->next;
    third = second->next;
    nextGroup = third->next;
    second->prev = previousGroup;
    if (previousGroup != nullptr)
    {
      previousGroup->next = second;
    }
    third->next = first;
    first->prev = third;
    first->next = nextGroup;
    if (nextGroup != nullptr)
    {
      nextGroup->prev = first;
    }
    first = nextGroup;
    if (i == 0)
    {
      head_ = second;
    }
    if ((i + 1) * 3 == length_)
    {
      tail_ = first;
    }
  }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse()
{
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *&startPoint, ListNode *&endPoint)
{
  /// @todo Graded in MP3.2
  ListNode *start = startPoint;
  ListNode *end = endPoint;
  ListNode *pastStart = startPoint->prev;
  ListNode *pastEnd = endPoint->next;
  ListNode *nextTmp = nullptr, *current = nullptr;
  for (current = startPoint; current != end; current = current->prev)
  {
    if (current == start)
    {
      nextTmp = pastEnd;
    }
    else
    {
      nextTmp = current->prev;
    }
    current->prev = current->next;
    current->next = nextTmp;
  }
  current->next = current->prev;
  current->prev = pastStart;
  if (head_ != start)
  {
    pastStart->next = current;
  }
  else
  {
    head_ = endPoint;
  }
  if (tail_ != end)
  {
    pastEnd->prev = start;
  }
  else
  {
    tail_ = startPoint;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n)
{
  ListNode *start = head_;
  ListNode *end = start;
  ListNode *tmp;
  while (start != nullptr)
  {
    for (int j = 0; j < n - 1; j++)
    {
      if (end->next != nullptr)
      {
        end = end->next;
      }
    }
    tmp = end->next;
    reverse(start, end);
    start = tmp;
    end = start;
  }
  /// @todo Graded in MP3.2
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> &otherList)
{
  // set up the current list
  head_ = merge(head_, otherList.head_);
  tail_ = head_;

  // make sure there is a node in the new list
  if (tail_ != NULL)
  {
    while (tail_->next != NULL)
      tail_ = tail_->next;
  }
  length_ = length_ + otherList.length_;

  // empty out the parameter list
  otherList.head_ = NULL;
  otherList.tail_ = NULL;
  otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode *List<T>::merge(ListNode *first, ListNode *second)
{
  /// @todo Graded in MP3.2
  if (first == nullptr)
  {
    return second;
  }
  else if (second == nullptr)
  {
    return first;
  }
  bool noHead = true;
  ListNode *head;
  if (first->data < second->data)
  {
    head = first;
    first = first->next;
  }
  else
  {
    head = second;
    second = second->next;
  }
  ListNode *current = head;
  while (first != nullptr && second != nullptr)
  {
    if (first->data < second->data)
    {
      current->next = first;
      first->prev = current;
      first = first->next;
    }
    else
    {
      current->next = second;
      second->prev = current;
      second = second->next;
    }
    current = current->next;
  }
  if (first == nullptr)
  {
    current->next = second;
    second->prev = current;
  }
  else if (second == nullptr)
  {
    current->next = first;
    first->prev = current;
  }
  return head;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode *List<T>::mergesort(ListNode *start, int chainLength)
{
  /// @todo Graded in MP3.2
  if (chainLength <= 1)
  {
    return start;
  }

  ListNode *second = split(start, chainLength / 2);
  start = mergesort(start, chainLength / 2);
  second = mergesort(second, chainLength - (chainLength / 2));

  return merge(start, second);
}
