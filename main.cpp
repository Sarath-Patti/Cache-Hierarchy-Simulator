#include "cache/Cache.h"
#include "hierarchy/CacheHierarchy.h"
#include "metrics/Metrics.h"
#include "policy/FIFO.h"
#include "policy/LRU.h"
#include "trace/TraceReader.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
ReplacementPolicy* lruFactory(int assoc) { return new LRU(assoc); }
ReplacementPolicy* fifoFactory(int assoc) { return new FIFO(assoc); }

void usage(const char* prog) {
    std::cout << "Usage:\n"
              << "  " << prog << " [lru|fifo] [stride <count> <bytes>|trace <path>]\n"
              << "Examples:\n"
              << "  " << prog << " lru stride 100000 64\n"
              << "  " << prog << " fifo trace traces/simple.trace\n";
}
} // namespace

int main(int argc, char** argv) {
    try {
        std::string policyName = argc > 1 ? argv[1] : "lru";
        ReplacementPolicy* (*policyFactory)(int) = nullptr;

        if (policyName == "lru") {
            policyFactory = lruFactory;
        } else if (policyName == "fifo") {
            policyFactory = fifoFactory;
        } else {
            usage(argv[0]);
            return 1;
        }

        std::vector<MemoryAccess> accesses;
        if (argc >= 5 && std::string(argv[2]) == "stride") {
            std::size_t count = std::stoull(argv[3]);
            unsigned long strideBytes = std::stoul(argv[4]);
            accesses = TraceReader::stride(count, strideBytes);
        } else if (argc >= 4 && std::string(argv[2]) == "trace") {
            accesses = TraceReader::fromFile(argv[3]);
        } else {
            accesses = TraceReader::stride(100000, 64);
        }

        Cache* L1 = new Cache(32 * 1024, 8, 64, 4, policyFactory);
        Cache* L2 = new Cache(256 * 1024, 8, 64, 12, policyFactory);
        CacheHierarchy hierarchy(L1, L2);

        Metrics metrics;
        for (const auto& access : accesses) {
            bool hit = hierarchy.access(access.address, access.write);
            metrics.record(!hit);
        }

        double amat = accesses.empty() ? 0.0 : static_cast<double>(hierarchy.cycles()) / accesses.size();

        std::cout << std::fixed << std::setprecision(4);
        std::cout << "Policy: " << policyName << "\n";
        std::cout << "Accesses: " << metrics.totalAccesses() << "\n";
        std::cout << "Hit rate: " << metrics.hitRate() * 100.0 << "%\n";
        std::cout << "Miss rate: " << metrics.missRate() * 100.0 << "%\n";
        std::cout << "Average memory access latency (cycles): " << amat << "\n";

        delete L1;
        delete L2;
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "error: " << ex.what() << "\n";
        return 1;
    }
}
