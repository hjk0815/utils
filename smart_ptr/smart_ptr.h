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
  explicit smart_ptr(T *ptr = nullptr) : ptr_(ptr){}
  ~smart_ptr(){ delete ptr_; };

  T &operator*() const { return *ptr_; }
  T *operator->() const { return ptr_; }
  operator bool() const { return ptr_;}

  // 禁止拷贝
  smart_ptr(const smart_ptr &) = delete;
  smart_ptr &operator=(const smart_ptr &) = delete;

  T *get() const {return ptr_;}
};



// =========== auto_ptr 
template<typename T>
class auto_ptr
{
private:
  T *ptr_;
public:
  auto_ptr(T *ptr = nullptr) noexcept : ptr_(ptr) {}
  ~auto_ptr() noexcept { delete ptr_; }

  T &operator*() const { return *ptr_; }
  T *operator->() const { return ptr_;}
  explicit operator bool() const { return ptr_; }

  T *get() const noexcept { return ptr_; }

  auto_ptr(auto_ptr &other) noexcept {
    ptr_ = other.release();
  }

  // copy and swap 
  auto_ptr &operator=(auto_ptr &rhs) noexcept {
    auto_ptr tmp(rhs.release());
    tmp.swap(*this);

    // auto_ptr(rhs.release()).swap(*this);
    return *this;
  }

  T *release() noexcept {
    T *ptr = ptr_;
    ptr_ = nullptr;
    return ptr;
  }

  void swap(auto_ptr &rhs) noexcept {
    using std::swap;
    swap(ptr_,rhs.ptr_);  // 转移指针所有权
  }

};


// ===============


class shared_count {
public:
    shared_count() : count_(1) {

    }

    // 增加计数
    void add_count() {
        ++count_;
    }

    // 减少计数
    long reduce_count() {
        return --count_;
    }

    // 获取当前计数
    long get_count() const {
        return count_;
    }

private:
    long count_;
};

template<typename T>
class shared_ptr {
public:
    explicit shared_ptr(
            T *ptr = nullptr) noexcept
            : ptr_(ptr) {
        if (ptr) {
            shared_count_ = new shared_count();
        }
    }

    ~shared_ptr() noexcept {
        // 最后一个shared_ptr再去删除对象与共享计数
        // ptr_不为空且此时共享计数减为0的时候,再去删除
        if(ptr_&&!shared_count_->reduce_count()) {
            delete ptr_;
            delete shared_count_;
        }
    }
	
    void swap(shared_ptr &rhs) noexcept {
        using std::swap;
        swap(ptr_, rhs.ptr_);   
        swap(shared_count_,rhs.shared_count_);
    }

    shared_ptr &operator=(shared_ptr rhs) noexcept {
        rhs.swap(*this);
        return *this;
    }
    template<typename U>
    friend class shared_ptr;
    shared_ptr(const shared_ptr<T> &other) noexcept {
        ptr_ = other.ptr_;
        if (ptr_) {
            other.shared_count_->add_count();
            shared_count_ = other.shared_count_;
        }
    }

    template<typename U>
    shared_ptr(shared_ptr<U> &&other) noexcept {
        ptr_ = other.ptr_;
        if (ptr_) {
            shared_count_ = other.shared_count_;
            other.shared_count_ = nullptr;
        }
    }
    long use_count() const noexcept {
        if (ptr_) {
            return shared_count_->get_count();
        } else {
            return 0;
        }
    }

private:
    T *ptr_;
    shared_count *shared_count_;
};
template<typename T>
void swap(shared_ptr<T>& lhs, shared_ptr<T>& rhs) noexcept {
  lhs.swap(rhs);
};
