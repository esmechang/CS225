/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */


/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1

  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1

  return List<T>::ListIterator(tail_->next);
}

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <typename T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  _destroy();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode *previous = NULL;
  if (head_ != NULL) {
    while (head_->next != NULL) {
      previous = head_;
      head_ = head_->next;
      delete previous;
    }
    delete head_;
  }
  head_ = NULL;
  tail_ = NULL;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode *temp = new ListNode(ndata);
  if (head_ != NULL) {
    temp->next = head_;
    head_->prev = temp;
    head_ = temp;
    length_++;
  } else {
    head_ = temp;
    tail_ = temp;
    length_++;
  }
  temp = NULL;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode *temp = new ListNode(ndata);
  if (tail_ != NULL) {
    tail_->next = temp;
    temp->prev = tail_;
    tail_ = temp;
    temp = NULL;
    length_++;
  } else {
    head_ = temp;
    tail_ = temp;
    length_++;
  }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
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
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.1
  ListNode *beginning = startPoint;
  ListNode *node = NULL;
  ListNode *end = endPoint;

  startPoint = endPoint;
  endPoint = beginning;

  if ((startPoint == NULL) || (endPoint == NULL) || (startPoint == endPoint)) {
    return;
  }
  while (node != end) {
    node = beginning;
    beginning = beginning->next;
    node->next = node->prev;
    node->prev = beginning;
  }
  if (startPoint == tail_) {
    tail_ = endPoint;
  }
  if (endPoint == head_) {
    head_ = startPoint;
  }
  if (endPoint->next != NULL) {
    endPoint->next->next = startPoint;
    startPoint->prev = endPoint->next;
  } else {
    startPoint->prev = NULL;
  }
  if (beginning != NULL) {
    endPoint->next = beginning;
    beginning->prev = endPoint;
  } else {
    endPoint->next = NULL;
  }
  return;




  // if (startPoint != endPoint) {
  //   while (startPoint != endPoint->next) {
  //     startPoint = startPoint->prev;
  //     startPoint->prev = startPoint->next;
  //     startPoint->next = startPoint;
  //     startPoint = startPoint->prev;
  //   }
  //   if (startPoint == NULL) {
  //     endPoint->prev = NULL;
  //     head_ = endPoint;
  //   } else {
  //     startPoint->prev = endPoint;
  //     endPoint->prev = startPoint->prev;
  //   }
  //   if (endPoint->next == NULL) {
  //     startPoint->next = NULL;
  //     tail_ = startPoint;
  //   } else {
  //     endPoint->next = startPoint;
  //     startPoint->next = endPoint->next;
  //   }
  //   startPoint = endPoint;
  //   endPoint = startPoint;
  // }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  ListNode *beginning = head_;
  ListNode *node;
  ListNode *temp;

  if ((head_ == NULL) || (n <= 1)) {
    return;
  }
  if (n >= length_) {
    reverse();
    return;
  }
  while (beginning != NULL) {
    node = beginning;
    for (int i = 1; i < n; i++) {
      if (node->next == NULL) {
        break;
      }
      node = node->next;
    }
    temp = node->next;
    reverse(beginning, node);
    beginning = temp;
  }

  // if (length_ <= 1 || n == 1) {
  //   return;
  // } else {
  //   ListNode *beginning = head_;
  //   ListNode *end = head_;
  //   while (beginning != NULL) {
  //     for (int i = 0; i < n; i++) {
  //       if (end->next == NULL) {
  //         end = end->next;
  //       }
  //     }
  //     reverse(beginning, end);
  //     end = end->next;
  //     beginning = end;
  //   }
  // }
  // if (n == length_) {
  //   reverse();
  // }

}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  ListNode *beginning = head_;
  ListNode *next_ = head_->next;

  while (next_ != tail_) {
    beginning->next = next_->next;
    next_->next->prev = beginning;
    next_->next = NULL;
    next_->prev = tail_;
    tail_->next = next_;
    tail_ = next_;
    if (beginning->next->next != NULL) {
      beginning = beginning->next->next;
      next_ = beginning;
      beginning = beginning->prev;
    } else {
      if (next_->next == NULL) {
        return;
      }
    }
  }
  return;

  // if (length_ > 1) {
  //   ListNode *curr = head_->next;
  //   ListNode *next_after = curr->next;
  //   while (curr != NULL) {
  //     next_after = curr->next;
  //
  //     if (next_after != NULL && next_after->next != NULL) {
  //       curr = next_after->next;
  //     } else {
  //       return;
  //     }
  //   }
  // }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <typename T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
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
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
  return NULL;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
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
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  return NULL;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <typename T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  return NULL;
}
