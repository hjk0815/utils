/** ===========================================
  * @file    :	smart_ptr.h
  * @brief   :	智能指针   减少对象的拷贝
  * @author  :	jk
  * @version :	
  * @date    :	2024-10-12
  * ===========================================
*/
#pragma once



template<typename T>
class smart_ptr
{
private:
  T *ptr_;
public:
  explicit smart_ptr(T *ptr = nullptr) : ptr_(ptr){};
  ~smart_ptr(){ delete ptr_; };

  T& operator*() const { return *ptr_; }
  T* operator->() const { return ptr_; }
  operator bool() const { return ptr_;}

  // 禁止拷贝
  smart_ptr(const smart_ptr&) = delete;
  smart_ptr &operator=(const smart_ptr&) = delete;

  T *get() const {return ptr_;}
};



// =========== auto_ptr 



// ===============