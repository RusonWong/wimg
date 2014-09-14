#include "common_utils.h"


string witoa(int val)
{
	ostringstream ostr;
	ostr << val;
	return ostr.str();
}
