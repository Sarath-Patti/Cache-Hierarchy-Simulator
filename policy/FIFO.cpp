#include "FIFO.h"

FIFO::FIFO(int assoc) {
    for (int i = 0; i < assoc; ++i) {
        order.push(i);
    }
}

int FIFO::victim() {
    int v = order.front();
    order.pop();
    order.push(v);
    return v;
}

void FIFO::touch(int) {
    // FIFO does not reorder on hits.
}
