#include "Application2D.h"
#include "CDDS_BinaryTreesApp.h"

int main() {
	
	// allocation
	auto app = new CDDS_BinaryTreesApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}