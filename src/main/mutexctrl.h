#pragma once
#include <shared_mutex>
#include <cmath>
#include <assert.h>
#include "utils.h"

#define IS_SET(var,pos) ((var) & (1<<(pos)))

const int N_MUTEXES = 2;

extern std::shared_mutex mutexes[N_MUTEXES];

// flags
const long LEAD_DEST =  1 << 0;
const long MAP_SCROLL = 1 << 1;

inline void lock(long readWriteFlags, long readOnlyFlags);

inline void unlock(long readWriteFlags, long readOnlyFlags);

struct locker{

    locker(long readWriteFlags, long readOnlyFlags);

    ~locker();

private:
    long readWriteFlags = 0;
    long readOnlyFlags = 0;
};



inline int bitPos(long flag);

template <typename T>
inline T readConcurrent(T& field, std::shared_mutex* lock_ptr);

template <typename T>
inline void readConcurrent(T& value, T& field, std::shared_mutex* lock_ptr);

template <typename T>
inline T readConcurrent(T& field, long flag);

template <typename T>
inline void readConcurrent(T& value, T& field, long flag);

template <typename T>
inline void writeConcurrent(T& field, T value, std::shared_mutex* lock_ptr);

template <typename T>
inline void writeConcurrent(T& field, T value, long flag);

template <typename T>
inline void appendConcurrent(std::vector<T>& vector, T value, std::shared_mutex* lock_ptr);

template <typename T>
inline void appendConcurrent(std::vector<T>& vector, T value, long flag);
