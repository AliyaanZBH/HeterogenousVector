#pragma once
//================================================
// name: TruestHeterogenousContainer.h
// desc: Interface for the superstar heterogenous container using variadic templates to achieve the "truest" implementation of this concept in C++
// auth: Aliyaan Zulfiqar
//================================================

//------------------------------------------------
//	STL Headers

#include <unordered_map>

// The namespace stands for Truest Heterogenous Container, but I figured typing that our every time would be a pain :p
namespace THC {
    class Container {
    public:
        template <class T>
        void push_back(const T& _t)
        {
            items<T>[this].push_back(_t);
        }
    private:
        template<class T>
        static std::unordered_map<const Container*, std::vector<T>> items;
    };

    // Storage for the static member - abuseing variable templates and creating a mapping of container pointers to vectors
    template<class T>
    std::unordered_map<const Container*, std::vector<T>> Container::items;
}