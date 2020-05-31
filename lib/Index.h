//
// Created by suhuiyuzhou on 26/05/2020.
//

#ifndef MAI_INDEX_H
#define MAI_INDEX_H

#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>
#include <vector>

namespace mai {

  namespace {
    // type config
    using IndexElemType = std::string;
  }

  struct IndexHash;

  class Index {
  public:
      // ctor etc.
      Index()
              :_idx{} { }

      Index(Index const&) = default; // required by find in hash
      Index& operator=(Index const&) = default;

      Index(Index&&) = default;
      Index& operator=(Index&&) = default;

      // template constructor
      template<typename T, typename... Args,
              typename=std::enable_if_t<std::is_constructible_v<IndexElemType, T>, void>>
      explicit Index(T i, Args... args)
              : _idx{}
      {
          this->add(i, args...);
      }

      // helper utils
      bool empty() const
      {
          return _idx.empty();
      }

      std::string to_string() const
      {
          std::string res{};
          for (auto const& e: _idx) {
              res += "+"+e;
          }
          return res;
      }

      Index common(Index const& other)
      {
          Index res{};
          auto p = std::mismatch(_idx.cbegin(), _idx.cend(), other._idx.cbegin(), other._idx.cend()).first;
          if (p!=_idx.cend()) {
              std::copy(_idx.cbegin(), p, std::back_inserter(res._idx));
          }
          return std::move(res);
      }

      // friend utls
      friend std::ostream& operator<<(std::ostream& os, Index const& index)
      {
          os << "# <Index>: ";
          for (auto const& e : index._idx) {
              os << e << ", ";
          }
          return os;
      }

      friend Index operator+(Index const& l, Index const& r)
      {
          Index res(l);
          std::copy(r._idx.cbegin(), r._idx.cend(), std::back_inserter(res._idx));
          return std::move(res);
      }

  private:
      // to construct index of any length
      template<typename T,
              typename=std::enable_if_t<std::is_constructible_v<IndexElemType, T>, void>>
      void add(T i)
      {
          _idx.emplace_back(std::move(i));
      }

      template<typename T, typename... Args,
              typename=std::enable_if_t<std::is_constructible_v<IndexElemType, T>, void>>
      void add(T i, Args... args)
      {
          add(std::move(i));
          add(args...);
      }

  private:
      std::vector<IndexElemType> _idx;

      friend IndexHash;
  };

  struct IndexHash {
    std::hash<IndexElemType> hash{};
    std::size_t operator()(Index const& key) const
    {
        std::size_t res{0};
        for (auto const& e : key._idx) {
            res += hash(e);
        }
        return res;
    }
  };

  struct IndexEqual {
    bool operator()(Index const& l, Index const& r) const
    {
        return l.to_string()==r.to_string();
    }
  };

}

#endif //MAI_INDEX_H
