#pragma once
//================================================
// name: VariantContainer.h
// desc: Interface for a "simple" heterogenous container using std::variant
// auth: Aliyaan Zulfiqar
//================================================

//------------------------------------------------
//	STL Headers

#include <variant>
#include <vector>

//------------------------------------------------
//	Container Interface
//
//  It's tedious to write std::visit loops manually, so we encapsulate the our variant container into a class with a custom visit mechanism.
//

template <class... T>
struct VariantContainer
{
    template <class V>
    void visit(V&& visitor)
    {
        for (auto& object : objects)
        {
            std::visit(visitor, object);
        }
    }
    using value_type = std::variant<T...>;
    std::vector<value_type> objects;
};