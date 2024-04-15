//================================================
// name: main.cpp
// desc: Entry point into the application
// auth: Aliyaan Zulfiqar
//================================================

//------------------------------------------------
//	STL Headers

#include <iostream>

//------------------------------------------------
//	My headers

#include "Visitors.h"
#include "VariantContainer.h"

// The star of the show
#include "TruestHeterogenousContainer.h"

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
	VariantContainer<int, double, std::string> variantCollection;
	variantCollection.objects.emplace_back(1);
	variantCollection.objects.emplace_back(2.2f);
	variantCollection.objects.emplace_back("foo");

	// Repeat steps again, using custom implementation to avoid writing a for loop every time
	variantCollection.visit(PrintVisitor{});

	std::cout << std::endl;

	variantCollection.visit(DoubleVisitor{});

	variantCollection.visit(lambdaPrintVisitor);


	std::cout << std::endl << "//------------------------------------------------" << std::endl;
	std::cout << "// THE Heterogenous Container" << std::endl << std::endl;

	// Here he comes
	thc::Container heterogenous_container;
	heterogenous_container.push_back(1);
	heterogenous_container.push_back(2.f);
	heterogenous_container.push_back('c');

	// He can even push back custom types!
	struct randomCustomType {};
	heterogenous_container.push_back(randomCustomType{});


	return 0;
}
