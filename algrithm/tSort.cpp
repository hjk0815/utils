#include "tSort.h"

void bubbleSort(std::vector<int> &v)
{
  int n = v.size();
  bool orderly = false;
  for(int i = 0; i < n-1 && !orderly; i++){
    orderly = true;
    for(int j=0; j < n-1-i; j++){
      if(v[j] > v[j+1]){
        std::swap(v[j],v[j+1]);
        orderly = false;   // 发送swap 仍然无序
      }
    }
  }
}

void myQuickSort(std::vector<int> &v, int low, int high)
{
  if (low < high){
    int pi = partition(v,low,high);
    myQuickSort(v,low,pi-1);
    myQuickSort(v,pi+1,high);
  }
}

int partition(std::vector<int> &v, int low, int high)
{
  int pivot = v[high];
  int i = low - 1;
  for(int j=low;j<high;j++){
    if(v[j] < pivot){
      i++;
      std::swap(v[i],v[j]);
    }
  }

  std::swap(v[high],v[i+1]);
  return i+1;
}

// void QuickSort(std::vector<int>& v, int low, int high) {
// 	if (low >= high)		// 结束标志
// 		return;
// 	int first = low;		// 低位下标
// 	int last = high;		// 高位下标
// 	int key = v[first];		// 设第一个为基准

// 	while (first < last)
// 	{
// 		// 将比第一个小的移到前面
// 		while (first < last && v[last] >= key)
// 			last--;
// 		if (first < last)
// 			v[first++] = v[last];

// 		// 将比第一个大的移到后面
// 		while (first < last && v[first] <= key)
// 			first++;
// 		if (first < last)
// 			v[last--] = v[first];
// 	}
// 	// 基准置位
// 	v[first] = key;
// 	// 前半递归
// 	QuickSort(v, low, first - 1);
// 	// 后半递归
// 	QuickSort(v, first + 1, high);
// }








