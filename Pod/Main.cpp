#include "Rect.h"
#include "Setting.h"

using namespace std;

int main() {
	
	Setting* s1 = Setting::getInstance();

	s1->load();

	return 0;
}