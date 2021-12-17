//
// Allocator class as a set of memory-functions
//

#pragma once
#include <iostream>

template <typename T>
class Allocator{
public:
    // Formal constructors (to implement MyMatrix<type> copy-constructor from MyMatrix<other type>)
    Allocator() = default;

    template <typename T_1>
    Allocator(const Allocator<T_1>&){};

    // Memory allocation:
    static T* allocate(size_t count){
        if (count > 0)
            return reinterpret_cast<T*>(::operator new(count * sizeof(T)));
        else
            return nullptr;
    }

    // Free memory:
    static void deallocate(T* ptr){
        ::operator delete (reinterpret_cast<void*>(ptr));
    }

    // Constructor & destructor:
    template<typename ...types>
    static void construct(T* ptr, const types&... parameters) {
        new(ptr) T(parameters...);
    }
    static void destroy(T* ptr) {
        ptr->~T();
    }
};