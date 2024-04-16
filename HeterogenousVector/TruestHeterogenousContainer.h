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
#include <vector>

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

        //------------------------------------------------
        //	Constructors and Destructors

        Container() = default;

        Container(const Container& _other)
        {
            *this = _other;
        }
        
        // Call our bespoke clear function
        ~Container()
        {
            clear();
        }

        //------------------------------------------------
        //	Operators

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

        //------------------------------------------------
        //	Key Methods

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

        template<class T>
        void visit(T&& visitor)
        {
            // Pass on the visitor, aswell as try to construct an instance of T::Types
            // Using std::decay to pass the type by value - importantly, if T is a function type (or callable), the decayed type will be a function pointer
            // Regardless, it will be a non-reference, non-cv-qualified(const volatile) type 
            visitHelper(visitor, typename std::decay_t<T>::Types{});
        }

    private:

        //------------------------------------------------
        //	Attributes (Member Variables)

        // Static variable template map of all the items in our container
        // But with our heterogeneous container we want instances to only know or care about the types that have been used for that specific instance
        template<class T>
        static std::unordered_map<const Container*, std::vector<T>> items;

        // Whenever we want to destroy an element of a given heterogeneous container, we can call the appropriate its clear_function
        std::vector<std::function<void(Container&)>> clearFunctions;
        // One for copying aswell
        std::vector<std::function<void(const Container&, Container&)>> copyFunctions;

        //------------------------------------------------
        //	Private helper Methods

        // Helper for visit(), provides the implementation for a given visitor, using template template arguments
        template<class T, template<class...> class TLIST, class... TYPES>
        void visitHelper(T&& visitor, TLIST<TYPES...>)
        {
            // This function also needs a helper, so call that via a unary left fold
            // Also implement a decay to get the function pointer
            (..., visitHelper2<std::decay_t<T>, TYPES>(visitor));
        }

        template<class T, class U>
        void visitHelper2(T& visitor)
        {
            // TODO: Little bit of debugging here to let the client know if the visitor they have written is acceptable would be GREAT!
            for (auto&& element : items<U>[this])
            {
                // Call the visitor object against every element, we are now successfuly visiting!
                visitor(element);
            }
        }
    };

    // Storage for the static member - abusing variable templates and creating a mapping of container pointers to vectors
    template<class T>
    std::unordered_map<const Container*, std::vector<T>> Container::items;
};