#ifndef HIERARCHY_H
#define HIERARCHY_H

#include "../cache/Cache.h"

class CacheHierarchy {
    Cache* L1;
    Cache* L2;
    int memoryLatency;

    long totalCycles = 0;

public:
    CacheHierarchy(Cache* l1, Cache* l2, int memoryLatency = 100);

    bool access(unsigned long addr, bool write);
    long cycles() const { return totalCycles; }
};

#endif
