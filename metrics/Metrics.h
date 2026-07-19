#ifndef METRICS_H
#define METRICS_H

class Metrics {
    long accesses = 0;
    long misses = 0;

public:
    void record(bool miss);
    long totalAccesses() const;
    long totalMisses() const;
    double missRate() const;
    double hitRate() const;
};

#endif
