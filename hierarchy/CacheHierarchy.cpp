#include "CacheHierarchy.h"

CacheHierarchy::CacheHierarchy(Cache* l1, Cache* l2, int memoryLatency_)
    : L1(l1), L2(l2), memoryLatency(memoryLatency_) {}

bool CacheHierarchy::access(unsigned long addr, bool write) {
    if (L1->access(addr, write)) {
        totalCycles += L1->getLatency();
        return true;
    }

    totalCycles += L1->getLatency();

    if (L2->access(addr, write)) {
        totalCycles += L2->getLatency();
        return true;
    }

    totalCycles += L2->getLatency() + memoryLatency;
    return false;
}
