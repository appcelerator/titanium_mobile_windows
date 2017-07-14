/**
 * Util
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */
#ifndef _TITANIUM_MOBILE_WINDOWS_UTIL_OUTPUTDEBUGSTRINGBUF_HPP_
#define _TITANIUM_MOBILE_WINDOWS_UTIL_OUTPUTDEBUGSTRINGBUF_HPP_
#if defined(_DEBUG)

#include <ostream>
#include <sstream>
#include <vector>
#include <Windows.h>

namespace TitaniumWindows {

  // This class is a derivate of basic_stringbuf which will output
  // all the written data using the OutputDebugString function.
  template<typename TChar, typename TTraits = std::char_traits<TChar>>
  class OutputDebugStringBuf final : public std::basic_stringbuf < TChar, TTraits > {

  public:

    explicit OutputDebugStringBuf() : buffer_(256) {
      setg(nullptr, nullptr, nullptr);
      setp(buffer_.data(), buffer_.data(), buffer_.data() + buffer_.size());
    }

    ~OutputDebugStringBuf() {
    }

    static_assert(std::is_same<TChar, char>::value || std::is_same<TChar, wchar_t>::value, "OutputDebugStringBuf only supports char and wchar_t types");

    int sync() try {
      MessageOutputer<TChar, TTraits>()(pbase(), pptr());
      setp(buffer_.data(), buffer_.data(), buffer_.data() + buffer_.size());
      return 0;
    }
    catch (...) {
      return -1;
    }

    int overflow(int c = TTraits::eof()) {
      auto syncRet = sync();
      if (c != TTraits::eof()) {
        buffer_[0] = c;
        setp(buffer_.data(), buffer_.data() + 1, buffer_.data() + buffer_.size());
      }
      return syncRet == -1 ? TTraits::eof() : 0;
    }


  private:

    std::vector<TChar> buffer_;

    template<typename TChar, typename TTraits>
    struct MessageOutputer;

    template<>
    struct MessageOutputer < char, std::char_traits<char> > {
      template<typename TIterator>
      void operator()(TIterator begin, TIterator end) const {
        std::string s(begin, end);
        OutputDebugStringA(s.c_str());
      }
    };

    template<>
    struct MessageOutputer < wchar_t, std::char_traits<wchar_t> > {
      template<typename TIterator>
      void operator()(TIterator begin, TIterator end) const {
        std::wstring s(begin, end);
        OutputDebugStringW(s.c_str());
      }
    };

  };

}  // namespace TitaniumWindows {

#endif
#endif  // _TITANIUM_MOBILE_WINDOWS_UTIL_OUTPUTDEBUGSTRINGBUF_HPP_
