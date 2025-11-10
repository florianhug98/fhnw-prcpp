#include "StringView.h"
#include "MyString.h"

using namespace std;

int main() {
	const StringView sv1 = "Hello World";
	const StringView sv2 = "Hello World";

	cout << sv1 << endl;
	cout << (sv1 == sv2) << endl;

	const StringView sv3 = sv1.removePrefix(5);
	const StringView sv4 = sv1.removeSuffix(5);

	cout << sv3 << endl;
	cout << sv4 << endl;
}