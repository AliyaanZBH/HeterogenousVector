//================================================
// name: main.cpp
// desc: Entry point into the application
// auth: Aliyaan Zulfiqar
//================================================

//------------------------------------------------
//	STL Headers

#include <iostream>
#include <variant>
#include <vector>

//------------------------------------------------
//	My headers

#include "Visitors.h"

//------------------------------------------------
//	Global Scope


//------------------------------------------------
//	Entry point

int main()
{

	std::cout << "//------------------------------------------------" << std::endl;
	std::cout << "// Single Variant"<< std::endl << std::endl;

	std::variant<int, double, std::string> myVariant;
	myVariant = 1;

	// Print original value
	std::visit(PrintVisitor{}, myVariant);

	// Invoke our visitor
	std::visit(DoubleVisitor{}, myVariant);

	// Print new val using lambda cos I like it (Lambdas 4lyf!)
	std::visit(lambdaPrintVisitor, myVariant);


	// Repeat with a string to prove that multiple types can be used
	myVariant = "foo";
	std::visit(PrintVisitor{}, myVariant);
	std::visit(DoubleVisitor{}, myVariant);
	std::visit(lambdaPrintVisitor, myVariant);

	std::cout << std::endl << "//------------------------------------------------" << std::endl;
	std::cout << "// Variant Vector" << std::endl << std::endl;

	// Now for a container
	std::vector<std::variant<int, double, std::string>> variantCollection;
	variantCollection.emplace_back(1);
	variantCollection.emplace_back(2.2f);
	variantCollection.emplace_back("foo");

	// Repeat steps again, using a for loop as we now have multiple elements
	for (const auto& variant : variantCollection)
	{
		std::visit(PrintVisitor{}, variant);
	}
	std::cout << std::endl;

	for (auto& variant : variantCollection)
	{
		std::visit(DoubleVisitor{}, variant);
	}

	for (const auto& variant : variantCollection)
	{
		std::visit(lambdaPrintVisitor, variant);
	}

	std::cout << std::endl << "//------------------------------------------------" << std::endl;
	return 0;
}
