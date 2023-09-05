#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <functional>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <thread>
#include <mutex>
#include <optional>

//没有必要在其他的文件中特意引入Log.h了
#include "Ether/Core/Log.h"

#include "Ether/Debug/Instrumentor.h"

#ifdef ETH_PLATFORM_WINDOWS
#include <Windows.h>
#endif