//================================================
// name: main.cpp
// desc: Entry point into the application
// auth: Aliyaan Zulfiqar
//================================================

//------------------------------------------------
//	STL Headers

#include <iostream>
#include <variant>

//------------------------------------------------
//	My headers

#include "AnyVariantContainer.h"

//------------------------------------------------
//	Global Scope


//------------------------------------------------
//	Entry point

int main()
{
	std::variant<int, double, std::string> myVariant;
	std::variant<int, double, std::string> myVariant2;
	myVariant = 1;
	myVariant2 = "foo";

	// Print original value
	std::visit(PrintVisitor{}, myVariant);
	std::visit(PrintVisitor{}, myVariant2);

	// Invoke our visitor
	std::visit(DoubleVisitor{}, myVariant);
	std::visit(DoubleVisitor{}, myVariant2);

	// Print new val
	std::visit(PrintVisitor{}, myVariant);
	std::visit(PrintVisitor{}, myVariant2);


	return 0;
}
