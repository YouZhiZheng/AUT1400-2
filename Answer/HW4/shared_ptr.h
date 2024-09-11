#ifndef SHARED_PTR
#define SHARED_PTR

template <typename T>
class SharedPtr
{
public:
    SharedPtr(): _p(nullptr), _refCount(nullptr) {}
    SharedPtr(T* p):_p(p) {
        if(p) _refCount = new size_t(1);
        else _refCount = nullptr;
    }
    SharedPtr(const SharedPtr &other) {
        if(&other != this)
        {
            _p = other._p;
            _refCount = other._refCount;
            if( _refCount != nullptr ) ++(*_refCount);
        }
    }
    ~SharedPtr() {
        if(_p)
        {
            --(*_refCount);
            
            if( (*_refCount) == 0)
            {
                delete _p;
                delete _refCount;
            }
        }

        _p = nullptr;
        _refCount = nullptr;
    }
    SharedPtr& operator=(const SharedPtr &other) {
        if(&other != this)
        {
            _p = other._p;
            _refCount = other._refCount;
            if( _refCount != nullptr ) ++(*_refCount);
        }

        return *this;
    }
    size_t use_count() const { 
        if( _refCount == nullptr )
        {
            // 测试样例需要返回 0，不能采用抛出异常的方式
            //throw std::runtime_error("The current pointer is a nullptr");
            return 0;
        }
        else return *_refCount; 
    }
    T* get() const { return _p; }
    T& operator*() const {
        if(_p) return *_p;
        else { throw std::runtime_error("cannot dereference a nullptr"); }
    }
    T* operator->() const {
        if(_p) return _p;
        else { throw std::runtime_error("cannot dereference a nullptr"); }
    }
    void reset() {
        if(_refCount != nullptr)
        {
            --(*_refCount);
            if( !(*_refCount) )
            {
                delete _p;
                delete _refCount;
            }
            _p = nullptr;
            _refCount = nullptr;
        }
    }
    void reset(T *other) {
        if(_refCount != nullptr)
        {
            --(*_refCount);
            if( !(*_refCount) )
            {
                delete _p;
                delete _refCount;
            }
        }
        _p = other;
        _refCount = new size_t(1);
    }
    operator bool() { return _p != nullptr; }

private:
    T* _p;
    size_t *_refCount;
};

template <typename T, typename... Args>
SharedPtr<T> make_shared(Args&&... args)
{
    return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

#endif //SHARED_PTR