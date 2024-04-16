#pragma once
//================================================
// name: AnyContainer.h
// desc: Interface for a "heterogenous" container using std::any
// auth: Aliyaan Zulfiqar
//================================================

//------------------------------------------------
//	STL Headers

#include <vector>
#include <any>

//------------------------------------------------
//	Container Interface
//

// Very similar to the Variant container, but this time using std::any
struct AnyContainer
{
    // The very same as the one used in THC, needed for visiting of any type
    template<class...>
    struct TypeList {};


    template<class T>
    void push_back(const T& input)
    {
        items.push_back(input);
    }

    template <class V, class... U>
    void visit(V&& visitor, TypeList<U...>)
    {
        (..., visitHelper<std::decay_t<V>, U>(visitor));
    }

    template <class V, class U>
    void visitHelper(V& visitor)
    {
        for (auto& i : items)
        {
            try {
                visitor(std::any_cast<U&>(i));
            }
            catch (...) {}
        }
    }

    std::vector<std::any> items;
};