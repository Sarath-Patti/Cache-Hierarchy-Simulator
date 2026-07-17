# Cache Memory Simulator (C++)

## Overview

A modular C++ cache simulator for computer architecture experiments. It models an L1/L2 hierarchy with configurable associativity, block size, and replacement policy, then runs either file-based traces or synthetic stride workloads to report hit/miss behavior and latency.

## Highlights

- L1/L2 cache simulator with configurable associativity and block size.
- Supports **LRU** and **FIFO** replacement policies.
- Supports both input traces and synthetic stride-based workloads.
- Reports hit rate, miss rate, and average memory access latency (AMAT).
- Modular structure separating cache model, replacement policy, hierarchy control, trace generation, and metrics.

## Project Structure

```
cache/
hierarchy/
metrics/
policy/
trace/
main.cpp
README.md
```

## Build

```bash
g++ -std=c++17 main.cpp cache/*.cpp hierarchy/*.cpp policy/*.cpp metrics/*.cpp trace/*.cpp -o cache_sim
```

## Run

Default (LRU + stride workload):

```bash
./cache_sim
```

Choose replacement policy and workload:

```bash
./cache_sim lru stride 100000 64
./cache_sim fifo stride 100000 64
./cache_sim lru trace traces/sample.trace
```

Trace format example (`R`/`W`, then address in hex or decimal):

```text
R 0x1000
W 0x1040
R 4096
```

## Optional: Correlate with Hardware Cache Misses

If running on Linux, compare simulator behavior to hardware counters:

```bash
perf stat -e cache-references,cache-misses ./cache_sim lru stride 100000 64
```

This helps contrast model predictions with observed miss behavior on a real CPU.
