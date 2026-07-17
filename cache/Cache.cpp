#include "Cache.h"

Cache::Cache(int size, int assoc_, int block, int latency_,
             ReplacementPolicy* (*policyFactory)(int))
    : assoc(assoc_), blockSize(block), latency(latency_) {
    sets = size / (assoc * blockSize);
    table.assign(sets, std::vector<CacheLine>(assoc));
    policies.reserve(sets);
    for (int i = 0; i < sets; ++i) {
        policies.push_back(policyFactory(assoc));
    }
}

Cache::~Cache() {
    for (ReplacementPolicy* p : policies) {
        delete p;
    }
}

bool Cache::access(unsigned long addr, bool write) {
    unsigned long blockAddr = addr / blockSize;
    int set = static_cast<int>(blockAddr % sets);
    unsigned long tag = blockAddr / sets;

    for (int way = 0; way < assoc; ++way) {
        CacheLine& line = table[set][way];
        if (line.valid && line.tag == tag) {
            if (write) {
                line.dirty = true;
            }
            policies[set]->touch(way);
            return true;
        }
    }

    int victimWay = -1;
    for (int way = 0; way < assoc; ++way) {
        if (!table[set][way].valid) {
            victimWay = way;
            break;
        }
    }
    if (victimWay == -1) {
        victimWay = policies[set]->victim();
    }

    CacheLine& victim = table[set][victimWay];
    victim.valid = true;
    victim.tag = tag;
    victim.dirty = write;
    policies[set]->touch(victimWay);
    return false;
}
