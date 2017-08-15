#pragma once
#include <stdint.h>
#include <cmath>
#include <iostream>

template<typename T, uint32_t N>
struct array{

    T data[N] = {};
    T* end;

    array(){ end = &data[0]; }

    T& operator[](uint32_t index){ return data[index]; }
    const T& operator[](uint32_t index)const{ return data[index]; }

    T& back(){ return *(end-1); }

    T* push_back(const T& value){
        if (end != data + N)
            *end = value;
        std::cout << "e: " << end << "\n";
        return ++end;
    }

    T* push_back(T* otherData, uint32_t n){
        uint32_t ext = std::min(n, N - size());
        memcpy(end, otherData, ext*sizeof(T));
        end += ext;
        return end;
    }

    //void erase(uint32_t index){
    //    --end;
    //    for (T* ref = data + index; ref != end; ++ref)
    //        *ref = *(ref + 1);
    //}

    void erase(T* reference){
        --end;
        for (T* ref = reference; ref != end; ++ref)
            *ref = *(ref + 1);
    }

    void erase(const T& value){
        for (T* ref = data; ref != end;)
            if (*ref == value){
                erase(ref);
                break;
            }else
                ++ref;
    }

    void insert(const T& value, T* reference){
        if (size() < N)
            ++end;
        for (T* ref = reference+1; ref != end; ++ref)
            *ref = *(ref - 1);
        *reference = value;
    }

    void clear(){ end = &data[0]; }

    void fill(const T& value){
        for (auto& dat : data)
            dat = value;
    }

    uint32_t size()const{ return end - data; }

    bool empty()const{ return end == data; }

    friend std::ostream& operator<<(std::ostream& os, const array& ar){ for (uint32_t i=0;i<ar.size();++i)os << ar[i] << ","; return os; }

    //template<uint32_t M>
    //array<T,N> operator=(const array<T,M>& rhs){
    //    uint32_t indices = std::min(N,M);
    //    memcpy(data, rhs.data, indices);
    //    end = data + indices;
    //    return *this;
    //}

    //template<uint32_t M>
    //array<T,N+M> operator+(const array<T,M>& rhs)const{
    //    array<T,N+M> cat;
    //    memcpy(cat.end, data, size());
    //    memcpy(cat.end, rhs.data, rhs.size());
    //    return cat;
    //}
};
