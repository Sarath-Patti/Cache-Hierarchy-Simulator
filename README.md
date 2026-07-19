# Cache Hierarchy Simulator

> A modular, configurable C++ simulator for exploring CPU cache behavior, replacement policies, and multi-level memory hierarchy performance.

![Language](https://img.shields.io/badge/Language-C%2B%2B17-blue)
![Architecture](https://img.shields.io/badge/Architecture-Multi--Level%20Cache-success)
![Build](https://img.shields.io/badge/Build-GCC%20%7C%20Clang-orange)
![License](https://img.shields.io/badge/License-MIT-green)

---

## Overview

Modern processors rely on cache memories to bridge the performance gap between high-speed CPUs and comparatively slower main memory. The efficiency of a cache hierarchy significantly impacts overall system performance.

**Cache Hierarchy Simulator** is a modular C++ application that models a configurable multi-level cache system. It enables users to study cache behavior under different workloads, evaluate replacement policies, and analyze memory hierarchy performance using detailed execution statistics.

The simulator emphasizes clean software architecture, modularity, and extensibility, making it suitable for computer architecture coursework, operating systems projects, and systems programming practice.

---

## Features

- Configurable cache size
- Configurable block size
- Configurable associativity
- Multi-level cache hierarchy (L1 & L2)
- LRU replacement policy
- FIFO replacement policy
- Trace-driven memory simulation
- Synthetic memory access workload generation
- Cache hit and miss statistics
- Average Memory Access Time (AMAT) calculation
- Modular object-oriented design
- Easily extensible replacement policy framework

---

## Architecture

```
                    CPU
                     │
                     ▼
             ┌────────────────┐
             │    L1 Cache    │
             └────────────────┘
                │         │
             Hit│         │Miss
                │         ▼
             ┌────────────────┐
             │    L2 Cache    │
             └────────────────┘
                │         │
             Hit│         │Miss
                │         ▼
             ┌────────────────┐
             │  Main Memory   │
             └────────────────┘
```

---

## Project Structure

```
Cache-Hierarchy-Simulator/
│
├── cache/
│   ├── Cache.cpp
│   ├── Cache.h
│   └── CacheLine.h
│
├── hierarchy/
│   ├── CacheHierarchy.cpp
│   └── CacheHierarchy.h
│
├── policy/
│   ├── ReplacementPolicy.h
│   ├── LRU.cpp
│   ├── LRU.h
│   ├── FIFO.cpp
│   └── FIFO.h
│
├── trace/
│   ├── TraceReader.cpp
│   └── TraceReader.h
│
├── metrics/
│   ├── Metrics.cpp
│   └── Metrics.h
│
├── traces/
│
├── README.md
└── main.cpp
```

---

## Simulation Workflow

```
Memory Trace
      │
      ▼
Trace Reader
      │
      ▼
Cache Hierarchy
      │
 ┌────┴────┐
 │         │
Hit      Miss
 │         │
 ▼         ▼
Update   Access Next Level
Stats      Cache/Memory
```

---

## Replacement Policies

| Policy | Description |
|---------|-------------|
| **LRU (Least Recently Used)** | Evicts the cache block that has not been accessed for the longest time. |
| **FIFO (First In First Out)** | Evicts the oldest cache block in the set. |

The replacement policy framework is abstracted, allowing additional algorithms to be implemented with minimal code changes.

---

## Cache Configuration

Each cache can be configured using parameters such as:

- Cache Size
- Block Size
- Associativity
- Access Latency
- Replacement Policy

Example:

```cpp
Cache cache(
    cacheSize,
    blockSize,
    associativity,
    latency,
    replacementPolicy
);
```

---

## Performance Metrics

The simulator reports several important performance statistics.

### Cache Hit Rate

```
Hit Rate = Hits / Total Accesses
```

### Cache Miss Rate

```
Miss Rate = Misses / Total Accesses
```

### Average Memory Access Time (AMAT)

```
AMAT = Hit Time + (Miss Rate × Miss Penalty)
```

These metrics help evaluate cache efficiency under different workloads and configurations.

---

## Building

Compile using any C++17 compatible compiler.

```bash
git clone https://github.com/Sarath-Patti/Cache-Hierarchy-Simulator.git

cd Cache-Hierarchy-Simulator

g++ -std=c++17 \
main.cpp \
cache/*.cpp \
hierarchy/*.cpp \
policy/*.cpp \
trace/*.cpp \
metrics/*.cpp \
-o cache_sim
```

---

## Running

Run the simulator using the default configuration.

```bash
./cache_sim
```

Or execute using a memory trace.

```bash
./cache_sim traces/sample.trace
```

---

## Example Output

```
========== Cache Statistics ==========

L1 Cache
--------------------------------
Hits               : 9245
Misses             : 755
Hit Rate           : 92.45 %

L2 Cache
--------------------------------
Hits               : 618
Misses             : 137

Overall Statistics
--------------------------------
Total Accesses     : 10000
Overall Miss Rate  : 1.37 %
AMAT               : 2.81 cycles
```

---

## Design Principles

The simulator is designed with the following goals:

- Modular software architecture
- Separation of concerns
- Object-oriented design
- Extensibility
- Maintainability
- Reusable components
- Clean implementation
- Easy experimentation

---

## Extending the Simulator

New replacement algorithms can be added by inheriting from the abstract replacement policy interface.

```
ReplacementPolicy
        ▲
        │
 ┌──────┴────────┐
 │               │
LRU            FIFO
 │
 ▼
YourPolicy
```

No changes are required in the cache implementation itself, making the design highly extensible.

---

## Applications

This project can be used for:

- Computer Architecture coursework
- Operating Systems laboratories
- Cache performance analysis
- Memory hierarchy experimentation
- Systems programming practice
- Interview preparation
- Research prototyping

---

## Future Enhancements

- Write-through cache
- Write-back cache
- Write allocate / No-write allocate
- Random replacement policy
- Pseudo-LRU replacement
- Victim cache
- Hardware prefetching
- Stride prefetcher
- Miss classification
- Inclusive / Exclusive caches
- Multi-core cache simulation
- MESI cache coherence protocol
- Interactive cache visualization
- JSON and CSV statistics export

---

## References

- John L. Hennessy & David A. Patterson — *Computer Architecture: A Quantitative Approach*
- David A. Patterson & John L. Hennessy — *Computer Organization and Design*
- Intel® 64 and IA-32 Architectures Optimization Manual
- AMD Software Optimization Guide

---

## License

This project is licensed under the MIT License.

---

## Author

**Sarath Patti**

M.Tech Computer Science  
National Institute of Technology Rourkela

If you found this project useful, consider giving it a ⭐ on GitHub.