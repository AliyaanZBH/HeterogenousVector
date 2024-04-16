#pragma once
//================================================
// name: Visitors.h
// desc: Helper file full of useful callables that we can use to test our heterogenous containers
// auth: Aliyaan Zulfiqar
//================================================

#include "TruestHeterogenousContainer.h"

//------------------------------------------------
//	Helper Callables (Functors)
//
//	Applying the Vistor Pattern to process our container, using callables that can be invoked using std::visit
//	https://en.wikipedia.org/wiki/Visitor_pattern

// This simple Visitor takes a variant input and doubles it.
struct DoubleVisitor
{
	void operator()(int& input) { input += input; }
	void operator()(float& input) { input += input; }
	void operator()(std::string& input) { input += input; }
};

// This simple functor takes a variant input and prints it.
struct PrintVisitor
{
	template <class T>
	void operator()(T&& input) { std::cout << input << std::endl; }
};
// Lambda version of the above cos I think it's cool.
auto lambdaPrintVisitor = [](auto&& input) { std::cout << input << std::endl; };

//------------------------------------------------
//	Truest Heterogenous Container bespoke visitors!

//
//	Note - all of these can be used any time you call std::visit aswell! This means the old functions above are no longer needed.
//		 - I decided to keep them for the sake of completeness.
//


// Use these by calling visit() on a THC and then passing this visitor in! e.g. container.visit(HeterogenousDoubleVisitor{});
// It's that easy!
struct HeterogenousDoubleVisitor : thc::VisitorBase<int, float>
{
	template<class T>
	void operator()(T& input)
	{
		input += input;
	}
};

struct HeterogenousPrintVisitor : thc::VisitorBase<int, float, char, std::string>
{
	template <class T>
	void operator()(T& input) { std::cout << input << std::endl; }
};

// Lambdas that take in a given container, and then proceed to call the containers visit() function, passing our new visitors to the container
auto doubleTHC	= [](thc::Container& input) { input.visit(HeterogenousDoubleVisitor{}); std::cout << std::endl; };
auto printTHC	= [](thc::Container& input) { input.visit(HeterogenousPrintVisitor{}); std::cout << std::endl; };
