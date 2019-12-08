#include "frame.h"
#include "drawframe.h"
#include <iostream>
int main() {
	try {
		Frame* win = new DrawFrame(L"����");
		win->run();
	}
	catch (int n) {
		std::cerr << "Error " << n << std::endl;
	}
	
}
