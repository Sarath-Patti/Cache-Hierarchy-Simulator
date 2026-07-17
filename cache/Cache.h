#ifndef CACHE_H
#define CACHE_H

#include "CacheLine.h"
#include "../policy/ReplacementPolicy.h"
#include <vector>

class Cache {
    int sets;
    int assoc;
    int blockSize;
    int latency;

    std::vector<std::vector<CacheLine>> table;
    std::vector<ReplacementPolicy*> policies;

public:
    Cache(int size, int assoc, int block, int latency,
          ReplacementPolicy* (*policyFactory)(int));
    ~Cache();

    bool access(unsigned long addr, bool write);
    int getLatency() const { return latency; }
};

#endif
