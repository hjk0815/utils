/** ===========================================
  * @file    :	main.cpp
  * @brief   :	utils 的测试代码
  * @author  :	jk
  * @version :	
  * @date    :	2024-10-11
  * ===========================================
*/
#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "RingQueue.h"
#include "smart_ptr.h"
#include "unorder.h"
#include "parallel.h"
#include "myHashTable.h"
#include "tSort.h"
#include "tHeapSort.h"



using std::cout;
using std::endl;


auto console = spdlog::stdout_color_mt("console");

void ringQueueTest(){
  CircularQ<int> queue(5);
  for (int i = 1; i <= 10; ++i) {
    queue.enqueue(i);
  }
  while (!queue.isEmpty()) {
    std::cout << "Dequeued: " << queue.dequeue() << std::endl;
  }
  try
  {
    std::cout << "Dequeued: " << queue.dequeue() << std::endl;
  }
  catch(const std::exception& e)
  {
    std::cerr << "some err is :: " << e.what() << '\n';
  }
}

// pImpl 

class X
{
private :
  struct XImpl;
  XImpl *pImpl;
public:
  X() ;
  ~X();

  void getImpl() ;
};

struct X::XImpl{
  int a;
  int b;
  
};

X::X(): pImpl(new XImpl){
    pImpl->a = 1;
    pImpl->b = 100;
};

X::~X(){
  delete pImpl;
}

void X::getImpl(){
  cout << "a :: " << pImpl->a << " b :: " << pImpl->b << endl;;
}
// 
void pImplTest(){
  X test = X();
  test.getImpl();
}

void smartPtrTest(){
  int *a = new int(100);
  smart_ptr<int> ptr(a);
  // smart_ptr<int> ptr2(ptr); // 禁止拷贝
  // smart_ptr<int> ptr2 = ptr;    // 禁止赋值
  cout << "smart ptr :: " << *ptr.get() << endl;


}
  // =========================
#include <algorithm>  // std::sort
#include <functional> // std::less/greater/hash
#include <iostream>   // std::cout/endl
#include <string>     // std::string
#include <vector>     // std::vector
#include <queue>
#include <set>
#include <complex>       // std::complex
#include <unordered_set> // std::unordered_set
#include <array>
#include "output.h"


void reference(){

  using namespace std;
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      q;
  q.push({1, 1});
  q.push({2, 2});
  q.push({0, 3});
  q.push({9, 4});
  while (!q.empty()) {
    cout << q.top() << endl;
    q.pop();
  }
}

// --------------
using namespace std;

template <int n> struct factorial {
  static_assert(n >= 0, "Arg must be non-negative");
  static const int value = n * factorial<n - 1>::value;
};

template <> struct factorial<0> { static const int value = 1; };

void factorialTest(){
  printf("factorialTest  %d\n", factorial<10>::value);
  array<int,5> my_array = {1,2,3,4,5};
  cout << " array :: " << my_array << endl;

}





#include <iostream>
#include <type_traits>

// 处理整数类型的模板
template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
process(T value) {
    std::cout << "Processing integral type: " << value << std::endl;
}

// 处理浮点数类型的模板
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, void>::type
process(T value) {
    std::cout << "Processing floating point type: " << value << std::endl;
}

void outputTest(){
  std::cout << std::boolalpha;

  // 测试 std::pair<int, double>
  std::cout << "is_pair<std::pair<int, double>>: " << is_pair_v<std::pair<int, double>> << std::endl;  // 输出 true

  // 测试 int 类型
  std::cout << "is_pair<int>: " << is_pair_v<int> << std::endl;  // 输出 false
}

void templateTest(){
  process(42);    // 调用整数版本
  process(3.14);
  cout << "========== output test " << endl;
  outputTest();
  cout << "========== output test end " << endl;

}



void threadTest(){

  background_task f;
  // f();

  std::thread t(f);
  std::thread t2 = std::move(t);
  // t.detach();
  // assert(!t.joinable());
  if(t.joinable()){
    t.join();
    cout << "thread t is join..." << endl;
  }
  else{
    cout << "thread t is not joinable" << endl;
  }

  if(t2.joinable()){
    t2.join();
    cout << "thread t2 is join..." << endl;
  }
  else{
    cout << "thread t2 is not joinable" << endl;
  }

  vector<int> v{3,4,5,6};
  int res=0;
  cout<<parallel_accumlate(v.begin(),v.end(),res) << endl;

}

extern int hashsize[];
extern int index;

void hashTest(){
	printf("-----哈希表-----\n");
	HashTable H;
	int i;
	int size = 11;
	KeyType array[8] = { 22, 41, 53, 46, 30, 13, 12, 67 };
	KeyType key;

	//初始化哈希表
	printf("初始化哈希表\n");
	cout << index << endl;
	// initHashTable(H, hashsize[index++]);
	if (HASHOK == initHashTable(H, hashsize[index++])) {
    printf("初始化成功\n");
  }
	//插入哈希表
	printf("插入哈希表\n");
	for (i = 0; i <= 7; i++) {
		key = array[i];
		insertHash(H, key);
		printHashTable(H);
	}

	//删除哈希表
	printf("删除哈希表中key为12的元素\n");
	int p, c;
	if (HASHOK == deleteHash(H, 12)) {
		printf("删除成功，此时哈希表为：\n");
		printHashTable(H);
	}

	//查询哈希表
	printf("查询哈希表中key为67的元素\n");
	if (HASHOK == searchHash(H, 67, p, c)) printf("查询成功\n");

	//再次插入，测试哈希表的重建
	printf("再次插入，测试哈希表的重建：\n");
	KeyType array1[8] = { 127,147, 157, 147, 137, 117, 193, 167 };
	for (i = 0; i <= 7; i++) {
		key = array1[i];
		insertHash(H, key);
		printHashTable(H);
	}


}

void sortTest(){
  vector<int> arr = {4,3,5,63,11,34,4,9,23};
  myQuickSort(arr,0,arr.size());
  cout << arr <<endl;
}
void heapSortTest(){
  vector<int> arr = { 3, 5, 3, 0, 8, 6, 1, 5, 8, 6, 2, 4, 9, 4, 7, 0, 1, 8, 9, 7, 3, 1, 2, 5, 9, 7, 4, 0, 2, 6 };
  maxHeapSort(arr);
  cout << arr << endl;
}





int main(){

  pImplTest();
  int a = 203;
  console->info("This is an info message. {}",a);
  console->warn("This is a warning message.");
  console->error("This is an error message.");
  cout << " utils test " << endl;
  ringQueueTest();
  smartPtrTest();
  reference();
  unorderTest();
  factorialTest();
  templateTest();
  threadTest();
  // ********************************
  // hashTest();  // 哈希表测试
  // sortTest();   // sort 测试 bubble, quick sort
  heapSortTest();  // 堆排序
  // ********************************
  cout << "please enter any to quit" << endl;
  std::getchar();
  return 0;
}