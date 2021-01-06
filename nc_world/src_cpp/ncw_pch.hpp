#ifndef NCW_PCH_H
#define NCW_PCH_H

// --<standart>--
// --stl
#include <array>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <map>
#include <set>
#include <utility>
#include <functional>
#include <algorithm>
// --streams
//#include <iomanip>
//#include <streambuf>
#include <iostream>
//#include <ostream>
//#include <istream>
#include <sstream>
#include <fstream>
//#include <iosfwd>
//#include <ios>
// --numbers
#include <random>
//#include <complex>
//#include <valarray>
//#include <numeric>
//#include <limits>
// --strings
#include <string>
//#include <regex>
// --support
#include <exception>
//#include <stdexcept>
//#include <locale>
#include <typeinfo>
#include <typeindex>
// --memory
#include <new>
#include <memory>
// --parallel computation
#include <thread>
#include <future>
#include <mutex>
// --</standart>--

// --<native>--
#include <cstddef>

#include <cstdarg>
#include <cstdio>
#include <ctime>

//#include <cassert>
//#include <clocale>
//#include <climits>
//#include <cerrno>

//#include <cfloat>
//#include <cmath>

//#include <cstring>
//#include <cctype>
//#include <cwchar>
//#include <cwctype>
// --</native>--

// --<platform>--
#ifdef NCW_PLATFORM_WINDOWS
#include <Windows.h>
#include <conio.h>
#endif
// --</platform>--

#endif // CNC_PCH_H