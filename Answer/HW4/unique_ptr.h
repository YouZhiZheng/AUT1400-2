#ifndef UNIQUE_PTR
#define UNIQUE_PTR

#include <utility>

template <typename T>
class UniquePtr
{
public:
    UniquePtr():_p(nullptr) {}
    UniquePtr(T* p):_p(std::move(p)) {}
    ~UniquePtr() { if(_p) {delete _p; _p = nullptr;} }
    // 禁止进行拷贝
    UniquePtr(const UniquePtr &) = delete;
    UniquePtr& operator=(const UniquePtr &) = delete;

    T* get(){ return _p; }
    T& operator*() const {
        if(_p) return *_p;
        else { throw std::runtime_error("cannot dereference a nullptr"); }
    }
    // UniquePtr<std::string> p;
    // p->size();会被重新解释为 (p.operator->)->size()
    T* operator->() const { 
        if(_p) return _p;
        else  { throw std::runtime_error("cannot dereference a nullptr"); }
    }
    // 重载 bool运算符 可使得该类对象作为条件作用于 if() 中
    operator bool() const { return _p != nullptr; }
    void reset() { if(_p) { delete _p; _p = nullptr; } }
    void reset(T* p) { if(_p) { delete _p; } _p = std::move(p); }
    T* release() { T* temp = _p; _p = nullptr; return temp;}

private:
    T* _p;
};

// 这里使用了完美转发+模板参数列表+函数参数列表
// 请自行学习了解相关内容
template <typename T, typename... Args>
UniquePtr<T> make_unique(Args&&... args)
{
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

#endif //UNIQUE_PTR