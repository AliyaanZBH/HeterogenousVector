#pragma once
//================================================
// name: AnyVariantContainer.h
// desc: Interface for a "simple" heterogenous container using std::variant and std::any
// auth: Aliyaan Zulfiqar
//================================================

//------------------------------------------------
//	STL Headers


//------------------------------------------------
//	Helper Visitors (Functors)
//
// Applying the Vistor Pattern to process our container
// https://en.wikipedia.org/wiki/Visitor_pattern


// This simple Visitor takes a variant input and doubles it.
struct DoubleVisitor
{
	void operator()(int& input) { input += input; }
	void operator()(double& input) { input += input; }
	void operator()(std::string& input) { input += input; }
};

// This simple functor takes a variant input and prints it.
struct PrintVisitor
{
	template <class T>
	void operator()(T&& input) { std::cout << input << std::endl; }
};
// Lambda version of the above cos I think it's cool.
auto lambdaPrintVisitor = [](auto&& input) {std::cout << input << std::endl; };

//------------------------------------------------
//	Container Interface
