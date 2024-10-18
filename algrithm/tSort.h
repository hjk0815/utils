

#pragma once

#include <iostream>
#include <vector>


void bubbleSort(std::vector<int> &v);

void myQuickSort(std::vector<int> &v, int low, int high);
int partition(std::vector<int> &v, int low, int high);