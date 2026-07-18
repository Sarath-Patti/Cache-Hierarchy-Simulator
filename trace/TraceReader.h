#ifndef TRACE_READER_H
#define TRACE_READER_H

#include <string>
#include <vector>

struct MemoryAccess {
    unsigned long address;
    bool write;
};

class TraceReader {
public:
    static std::vector<MemoryAccess> fromFile(const std::string& path);
    static std::vector<MemoryAccess> stride(std::size_t count, unsigned long strideBytes, bool write = false);
};

#endif
