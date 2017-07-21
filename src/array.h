#include <stdint.h>

template<typename T, uint8_t N>
struct array{

    T data[N] = {};
    T* end;

    array(){ end = data; }

    T& operator[](uint8_t index){ return data[index]; }
    const T& operator[](uint8_t index)const{ return data[index]; }

    T* push_back(const T& value){
        if (end != data + N)
            *(end++) = value;
        return end;
    }

    void erase(uint8_t index){
        --end;
        for (T* ref = data + index; ref != end; ++ref)
            *ref = *(ref + 1);
    }

    void erase(T* reference){
        --end;
        for (T* ref = reference; ref != end; ++ref)
            *ref = *(ref + 1);
    }

    void erase(const T& value){
        for (T* ref = data; ref != end; ++ref)
            if (*ref == value){
                erase(ref);
                break;
            }
    }

    uint8_t size(){ return end - data; }
};
