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

//û�б�Ҫ���������ļ�����������Log.h��
#include "Ether/Core/Log.h"

#include "Ether/Debug/Instrumentor.h"

#ifdef ETH_PLATFORM_WINDOWS
#include <Windows.h>
#endif