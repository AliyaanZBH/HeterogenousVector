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
//	Global Variables


//------------------------------------------------
//	Entry point
int main()
{

	std::cout << "//------------------------------------------------" << std::endl;
	std::cout << "// Single Variant"<< std::endl << std::endl;

	std::variant<int, float, std::string> myVariant;
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
	VariantContainer<int, float, std::string> variantCollection;
	variantCollection.elements.emplace_back(1);
	variantCollection.elements.emplace_back(2.2f);
	variantCollection.elements.emplace_back("foo");

	// Repeat steps again, using custom implementation to avoid writing a for loop every time
	variantCollection.visit(PrintVisitor{});

	std::cout << std::endl;

	variantCollection.visit(DoubleVisitor{});

	variantCollection.visit(lambdaPrintVisitor);


	std::cout << std::endl << "//------------------------------------------------" << std::endl;
	std::cout << "// THE Heterogenous Container" << std::endl << std::endl;

	// Here he comes
	thc::Container heterogenousContainer;
	heterogenousContainer.push_back(1);
	heterogenousContainer.push_back(2.3456f);
	heterogenousContainer.push_back('c');
	heterogenousContainer.push_back(std::string{ "foo" });

	// Lets print all these types and check that our visiting works
	std::cout << "Truest Heterogenous Container with integral types: " << std::endl << std::endl;

	// Call the lambda which in turn calls our visit function - method 1
	printTHC(heterogenousContainer);

	// Let's double them and print again
	std::cout << "Double Visitor (won't double chars or strings): " << std::endl;

	doubleTHC(heterogenousContainer);

	// We can also call the visit function directly here, and pass the visitor in that way - method 2
	heterogenousContainer.visit(HeterogenousPrintVisitor{});
	std::cout << std::endl;

	// He can even push back custom types! (Though visitors will need to be tweaked / written to account for this!)
	struct randomCustomType {};
	heterogenousContainer.push_back(randomCustomType{});

	// He comes with QoL tools such as copy construction / assignment
	thc::Container c2 = heterogenousContainer;
	std::cout << "New THC using assignment : " << std::endl << std::endl;
	printTHC(c2);

	// Test clearing by emptying our original THC
	heterogenousContainer.clear();
	std::cout << "Original THC after clearing it: " << std::endl << std::endl;
	printTHC(heterogenousContainer);

	// And lets test our copy by making sure it didn't also clear itself!
	std::cout << "New THC after clearing original: " << std::endl << std::endl;
	printTHC(c2);
	
	// Let's restore the original container now
	heterogenousContainer = c2;

	// Quick test to make sure that worked
	std::cout << "Original THC after copying the new one: " << std::endl << std::endl;
	printTHC(heterogenousContainer);

	// Finally, want to show off a neat little trick. To do so, let's double the new container
	std::cout << "Doubling the new THC!: " << std::endl;
	doubleTHC(c2);
	printTHC(c2);

	// Cool little trick - as the THC is a custom type... it can also store itself!
	std::cout << "Original THC after pushing the new one into it!: " << std::endl << std::endl;
	heterogenousContainer.push_back(c2);
	
	// We can even print it!
	printTHC(heterogenousContainer);


	return 0;
}
