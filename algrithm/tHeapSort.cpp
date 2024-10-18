
#include "tHeapSort.h"

void heapify(std::vector<int> &v, int n, int i)
/* 堆化 */
{
  int largest = i;
  int left = 2*i + 1;
  int right = 2*i +2;

  if (left < n && v[left] > v[largest])
  {
    largest = left;
  }
  if (right < n && v[right] > v[largest])
  {
    largest = right;
  }

  if (largest != i)
  {
    std::swap(v[i],v[largest]);
    heapify(v, n, largest);
  }
}

void maxHeapSort(std::vector<int> &v)
{
  int n = v.size();
  // 构建最大堆
  for (int i = n/2 -1; i >= 0; i--)  
  {
    heapify(v, n, i);
  }

  for (int i = n-1; i >= 0; i--)
  {
    std::swap(v[0],v[i]);
    heapify(v,i,0);
  }
}

