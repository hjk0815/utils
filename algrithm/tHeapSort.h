
/** ===========================================
  * @file    :	tHeapSort.h
  * @brief   :	max heap sort
  * @author  :	jk
  * @version :	
  * @date    :	2024-10-18
  * ===========================================
*/


#pragma once
#include <iostream>
#include <vector>



void heapify(std::vector<int> &v,int n, int i);



void maxHeapSort(std::vector<int> &v);




// 归并 
template<typename T>
void merge_sort_recursive(T arr[], T reg[], int start, int end) {
	if (start >= end)
		return;
	int len = end - start, mid = (len >> 1) + start;
	int start1 = start, end1 = mid;
	int start2 = mid + 1, end2 = end;
	merge_sort_recursive(arr, reg, start1, end1);
	merge_sort_recursive(arr, reg, start2, end2);
	int k = start;
	while (start1 <= end1 && start2 <= end2)
		reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
	while (start1 <= end1)
		reg[k++] = arr[start1++];
	while (start2 <= end2)
		reg[k++] = arr[start2++];
	for (k = start; k <= end; k++)
		arr[k] = reg[k];
}
//整數或浮點數皆可使用,若要使用物件(class)時必須設定"小於"(<)的運算子功能
template<typename T> 
void merge_sort(T arr[], const int len) {
	T *reg = new T[len];
	merge_sort_recursive(arr, reg, 0, len - 1);
	delete[] reg;
}

// shell sort
/*
  希尔排序是插入排序的一种，又称“缩小增量排序”，是直接插入排序算法的一种更高效的改进版本。
  希尔排序是非稳定排序算法。
  希尔排序是把记录按下标的一定增量分组，对每组使用直接插入排序算法排序；
  随着增量逐渐减少，每组包含的关键词越来越多，当增量减至1时，整个文件恰被分成一组，算法便终止。
*/
template<typename T>
void shellSort(std::vector<T> &arr){
	int len = arr.size();
	int h = 1;
	while (h < len / 3)
	{
		h = 3 * h + 1;
	}
	while (h >= 1){
		for (int i = h; i < len; i++){
			for (int j = i; j >= h && arr[j] < arr[j - h]; j-=h){
				std::swap(arr[j],arr[j-h]);
			}
		}
		h /= 3;
	}
}
