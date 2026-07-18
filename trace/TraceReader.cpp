#include "TraceReader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

std::vector<MemoryAccess> TraceReader::fromFile(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        throw std::runtime_error("unable to open trace file: " + path);
    }

    std::vector<MemoryAccess> accesses;
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::istringstream iss(line);
        char op;
        std::string addrToken;
        if (!(iss >> op >> addrToken)) {
            continue;
        }

        unsigned long addr = std::stoul(addrToken, nullptr, 0);
        accesses.push_back({addr, op == 'W' || op == 'w'});
    }
    return accesses;
}

std::vector<MemoryAccess> TraceReader::stride(std::size_t count, unsigned long strideBytes, bool write) {
    std::vector<MemoryAccess> accesses;
    accesses.reserve(count);
    for (std::size_t i = 0; i < count; ++i) {
        accesses.push_back({static_cast<unsigned long>(i * strideBytes), write});
    }
    return accesses;
}
