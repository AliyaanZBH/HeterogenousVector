#pragma once
//================================================
// name: TruestHeterogenousContainer.h
// desc: Interface for the superstar heterogenous container using variadic templates to achieve the "truest" implementation of this concept in C++
// auth: Aliyaan Zulfiqar
//================================================

//------------------------------------------------
//	STL Headers

#include <unordered_map>
#include <functional>

// The namespace stands for "Truest Heterogenous Container", but I figured typing that out every time would be a pain :p
namespace thc {

    //------------------------------------------------
    //	Visitor Support

    // A class that utilises variadic templates to create a list of types
    // Used to communicate the types that our visitors are capable of visiting
    template<class...>
    struct TypeList {};

    // Templated base class for visitors that defines a given type list
    // Use this when writing a visitor callable, ensuring it inherits from this base
    template<class... TYPES>
    struct VisitorBase
    {
        using Types = thc::TypeList<TYPES...>;
    };

    //------------------------------------------------
    //	Container Interface

    // Our actual Heterogenous Container!
    class Container {
    public:

        Container() = default;

        Container(const Container& _other)
        {
            *this = _other;
        }

        Container& operator=(const Container& other)
        {
            clear();
            clearFunctions = other.clearFunctions;
            copyFunctions = other.copyFunctions;

            for (auto&& copyFunction : copyFunctions)
            {
                copyFunction(other, *this);
            }
            return *this;
        }

        // Used to empty our container
        void clear()
        {
            // Iterate through all clear functions and call them
            for (auto&& clearFunc : clearFunctions)
            {
                clearFunc(*this);
            }
        }

        template<class T>
        void push_back(const T& elem)
        {
            // Check if this type is already in the container
            // If not, create a new function for destroying that type
            if (items<T>.find(this) == std::end(items<T>))
            {
                // Push an function into our container of function pointers via lambda
                clearFunctions.emplace_back([](Container& container)
                {
                    items<T>.erase(&container);
                });

                // Repeat the same for copy, every unique type will need a bespoke copy function, and the container we're copying to will need these
                copyFunctions.emplace_back([](const Container& from, Container& to)
                {
                    items<T>[&to] = items<T>[&from];
                });

            }
            // Actually push the item back into the container
            items<T>[this].push_back(elem);
        }
    private:
        template<class T>
        static std::unordered_map<const Container*, std::vector<T>> items;

        // Whenever we want to destroy an element of a given heterogeneous container, we can call the appropriate its clear_function
        std::vector<std::function<void(Container&)>> clearFunctions;
        // One for copying aswell
        std::vector<std::function<void(const Container&, Container&)>> copyFunctions;
    };

    // Storage for the static member - abuseing variable templates and creating a mapping of container pointers to vectors
    template<class T>
    std::unordered_map<const Container*, std::vector<T>> Container::items;
}