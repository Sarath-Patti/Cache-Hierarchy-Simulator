#ifndef FIFO_H
#define FIFO_H

#include "ReplacementPolicy.h"
#include <queue>

class FIFO : public ReplacementPolicy {
    std::queue<int> order;
public:
    explicit FIFO(int assoc);
    int victim() override;
    void touch(int way) override;
};

#endif
