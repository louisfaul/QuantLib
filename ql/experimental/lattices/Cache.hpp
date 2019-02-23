#ifndef quantlib_cache_hpp
#define quantlib_cache_hpp

#include <ql/functional.hpp>
#include<tr1/unordered_map>

namespace QuantLib {

    template <class T1, class T2>
    class Cache {
      public:
        Cache() {}
        explicit Cache(const QuantLib::ext::function<T2(T1)> f): f{f} {}
        T2 operator()(T1 key) const {
            typename std::tr1::unordered_map<T1, T2>::iterator it = memory_map.find(key);
            if (it != memory_map.end())
                return it->second;
            else
                return calculateData(key);
        }

        void setf(const QuantLib::ext::function<T2(T1)> f_) { f = f_; }

        void clear() { memory_map.clear; }
        void erase(T1 key) { memory_map.erase(key); }

      private:
        QuantLib::ext::function<T2(T1)> f;
        mutable std::tr1::unordered_map<T1, T2> memory_map;

        T2 calculateData(T1 key) const {
            T2 value = f(key);
            memory_map[key] = value;
            return value;
        }
    };

}

#endif
