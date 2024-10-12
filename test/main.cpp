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

int main(){

  pImplTest();
  int a = 203;
  console->info("This is an info message. {}",a);
  console->warn("This is a warning message.");
  console->error("This is an error message.");
  cout << " utils test " << endl;
  ringQueueTest();
  smartPtrTest();
  cout << "please enter any to quit" << endl;
  std::getchar();
  return 0;
}