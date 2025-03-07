#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <iostream>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> heap_store_;
  int m_;
  PComparator c_;
  void heapify(int loc);
};

// Add implementation of member functions here
// constructor
template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c) : m_(m), c_(c) {}

// destructor
template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap(){}

// push
template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item) {
  heap_store_.push_back(item);
  int loc = heap_store_.size() - 1;
 
  int parent_loc = (loc - 1) / m_;
  while (parent_loc >= 0 && c_(heap_store_[loc], heap_store_[parent_loc])) {
    std::swap(heap_store_[parent_loc], heap_store_[loc]);
    loc = parent_loc;
    parent_loc = (loc - 1) / m_;
  }
  
}

//empty
template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const {
  return heap_store_.empty();
}

//size
template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const {
  return heap_store_.size();
}


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Empty");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return heap_store_[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Empty");

  }
  heap_store_[0] = heap_store_.back();
  heap_store_.pop_back();
  heapify(0);
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::heapify(int loc) {
  int last_loc = heap_store_.size() - 1;
  int smaller_child = (m_ * loc) + 1;
  // checks for leaf node
  if (smaller_child > last_loc) return; 
  int highest_priority = smaller_child;

  // iterates through all m children
  for (int i = 1; i < m_; i++) {
    int next_child = smaller_child + i;
    if (next_child <= last_loc && next_child > 0) {
      if (c_(heap_store_[next_child], heap_store_[highest_priority])) {
        highest_priority = next_child;
      }
    }
  }

  if (c_(heap_store_[highest_priority], heap_store_[loc])) {
    std::swap(heap_store_[loc], heap_store_[highest_priority]);
    heapify(highest_priority);
  }

}

#endif



