#pragma once

#include <sstream>
#include <iomanip>
#include <cstdint>
#include <mutex>
#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <functional>
#include <chrono>
#include <ctime>
#include <limits>
#include <thread>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
#include <atomic>
#include <vector>
#include <unordered_set>
#include <type_traits>

#include <boost/optional.hpp>
#define BOOST_BIND_NO_PLACEHOLDERS
#include <boost/signals2/signal.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/ostream_iterator.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

// Include the library we build on top of
#include "HAL/HAL.hpp"

// include the base class for all proxies
#include "Titanium/Module.hpp"
// Include our constants
#include "Titanium/Codec/Constants.hpp"
#include "Titanium/Contacts/Constants.hpp"
#include "Titanium/Filesystem/Constants.hpp"
#include "Titanium/Map/Constants.hpp"
#include "Titanium/Media/Constants.hpp"
#include "Titanium/Network/Constants.hpp"
#include "Titanium/UI/Constants.hpp"
// and the most used structs/enums
#include "Titanium/UI/Point.hpp"
#include "Titanium/UI/Gradient.hpp"
#include "Titanium/UI/Font.hpp"
#include "Titanium/UI/Dimension.hpp"
#include "Titanium/UI/ShadowDict.hpp"
#include "Titanium/UI/TitleAttributesParams.hpp"
#include "Titanium/UI/ViewPadding.hpp"
#include "Titanium/ErrorResponse.hpp"
