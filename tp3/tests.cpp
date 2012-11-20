#include "Driver.h"
#include <stdarg.h>
using namespace std;
using namespace aed2;

// auxiliares para tests
#include <iostream>
#include <sstream>
void mt_assert(bool expr, string lhs, string rhs, int line) { if (!expr) {ostringstream os;os << "error en linea " << line << endl;os << "   se esperaba: " << rhs << endl;os << "     se obtuvo: " << lhs;throw os.str();} }
void mt_str_assert(string lhs, string rhs, int line) { if (lhs.compare(rhs) != 0) { ostringstream os;os << "error en linea " << line << endl;os << "   se esperaba: " << rhs << endl;os << "     se obtuvo: " << lhs;throw os.str();} }
#define RUN_TEST(test) {\
	{bool ok = true;\
	cout << #test << "..." << flush;\
	try { test(); }\
	catch (string& msg) { ok = false; cout << msg; } \
	catch (...) { ok = false; cout << "error"; }\
	if (ok) { cout << "ok"; }\
	cout << endl << flush;\
	}\
}
#define ASSERT_EQ(lhs, rhs) {{ostringstream lhss, rhss;lhss << (lhs);rhss << (rhs);mt_assert((lhs) == (rhs), lhss.str(), rhss.str(), __LINE__);}}
#define ASSERT(expr) { mt_assert((expr), "false", "true", __LINE__); }
#define ASSERT_STR_EQ(lhs, rhs) { mt_str_assert(string((lhs)), string((rhs)), __LINE__); }
// fin auxiliares para tests

/**
 * Permite construir una lista de strings de forma comoda.
 * l("lorem", "ipsum", NULL) equivale a la lista ["lorem", "ipsum"]
 * l(NULL) equivale a la lista vacia.
 *
 * siembre es necesario poner un NULL para indicar el final de la lista
 */

int main(void) {
        cout << "Facu es el mejor";
	return 0;
}
