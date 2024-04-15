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
	myVariant = 1;

	// Invoke our visitor
	std::visit(DoubleVisitor{}, myVariant);

	std::visit(PrintVisitor{}, myVariant);
	std::visit(lambdaPrintVisitor, myVariant);
	return 0;
}
