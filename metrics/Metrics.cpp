#include "Metrics.h"

void Metrics::record(bool miss) {
    ++accesses;
    if (miss) {
        ++misses;
    }
}

long Metrics::totalAccesses() const {
    return accesses;
}

long Metrics::totalMisses() const {
    return misses;
}

double Metrics::missRate() const {
    return accesses == 0 ? 0.0 : static_cast<double>(misses) / static_cast<double>(accesses);
}

double Metrics::hitRate() const {
    return 1.0 - missRate();
}
