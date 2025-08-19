// Online C++ compiler to run C++ program online
#include <iostream>
#include <memory>
using namespace std;

template<typename T>
class Uniqueptr{
    private:
    T* res;
    
  public:
  
  Uniqueptr(T* ptr): res(ptr){
      cout<<"ctor called\n";
  }
  
  Uniqueptr(const Uniqueptr& ptr) = delete;
  Uniqueptr& operator=(const Uniqueptr& ptr) = delete;
  
  //move copy ctor
  //p3(p2) : free resources of p2 and p3 will point to p2 resource
  Uniqueptr(Uniqueptr&& ptr){
      std::cout<<"\nmove copy ctor called\n";
      res = ptr.res;
      ptr.res = nullptr;
  }
  
  //p2 = p3 
  //p2 will free it's resource and point to p3
  //p3 will free
  Uniqueptr& operator=(Uniqueptr&& ptr){
      std::cout<<"\nmove copy assignment operator called\n";
      if(this != &ptr){
          if(res) delete res;
          res = ptr.res;
          ptr.res = nullptr;
      }
      return *this;
  }
  
  //get res ka value
  T& operator*() const{
      return *res;
  }
  
  T* operator->() const{
      return res;
  }
  
  T* get() const{
      return res;
  }
    
};


int main() {
    // Write C++ code here
    std::cout << "Try programiz.pro\n";

    Uniqueptr<int> ptr1(new int(1));
    cout<<"Ptr1 : "<<*(ptr1)<<" "<<ptr1.get()<<"\n";
    
    Uniqueptr<int> ptr2(new int(7));
    ptr2 = std::move(ptr1);
    
    cout<<"Ptr2 : "<<*(ptr2)<<" pointer: "<<ptr2.get()<<"\n";
    Uniqueptr<int> ptr3(new int(5));
    cout<<ptr3.get();
    Uniqueptr<int> ptr4 = (std::move(ptr3));
    cout<<"\n"<<ptr4.get();
    cout<<"\n unique pointer below\n";
    
    
    std::unique_ptr<int> uq_ptr = std::make_unique<int>(5);
    std::cout<<*(uq_ptr)<<"\n";

    return 0;
}
