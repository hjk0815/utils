/** ===========================================
  * @file    :	RingQueue.h
  * @brief   :	ring queue
  * @author  :	jk
  * @version :	1.0.0
  * @date    :	2024-10-11
  * ===========================================
*/

#pragma once
#include <vector>
#include <stdexcept>
#include <iostream>


template<typename T>
class CircularQ
{
private:
  std::vector<T> buffer;
  size_t max_size;
  size_t head;  // 读指针
  size_t tail;  // 写指针
  bool full;    // 标记队列是否已满

public:
  CircularQ(size_t size);
  ~CircularQ();

  void enqueue(const T& item);  
  T dequeue();   
  bool isEmpty() const;
  bool isFull() const;
  size_t size() const; 
  void clear();
  
};


// =============== impl  ================

template <typename T>
inline CircularQ<T>::CircularQ(size_t size)
  : buffer(size)
  , max_size(size)
  , head(0)
  , tail(0)
  , full(false)
{
}

template <typename T>
CircularQ<T>::~CircularQ()
{
}

template <typename T>
void CircularQ<T>::enqueue(const T &item)
{
  buffer[tail] = item;
  if (full){
    head = (head + 1) % max_size;
  }
  tail = (tail + 1) % max_size;
  full = (tail == head);
}

template <typename T>
T CircularQ<T>::dequeue()
{
  if (isEmpty()){
   throw std::runtime_error("Queue is empty"); 
  }
  T item = buffer[head];
  full = false;
  head = (head + 1) % max_size;
  return item;
}

template <typename T>
bool CircularQ<T>::isEmpty() const
{
  return (!full && (head == tail));
}

template <typename T>
bool CircularQ<T>::isFull() const
{
  return full;
}

template <typename T>
size_t CircularQ<T>::size() const
{
  size_t size = max_size;
  if (!full){
    if (tail >= head){
      size = tail - head;
    }else {
      size = max_size + tail - head;
    }
  }
  return size;
}

template <typename T>
inline void CircularQ<T>::clear()
{
  head = 0;
  tail = 0;
  full = false;
}
