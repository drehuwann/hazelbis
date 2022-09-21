#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#ifdef HZ_PLATFORM_WINDOWS
    #include "Windows.h"
#else  // HZ_PLATFORM_WINDOWS
    #error non windows systems not implemented yet.
#endif  // HZ_PLATFORM_WINDOWS
