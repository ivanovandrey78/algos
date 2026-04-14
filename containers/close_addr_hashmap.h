#include <vector>
#include <cstdint>
#include <list>

namespace nr {

class HashMap {
public:
    using Cell = std::pair<int, int>;

    static uint64_t hash(uint64_t x) noexcept {
        uint64_t h = 5381;
        for (int i = 0; i < 8; ++i) {
            uint8_t byte = (x >> (i * 8)) & 0xFF;
            h = ((h << 5) + h) ^ byte;
        }
        return h;
    }

    explicit HashMap(int expected_size = 1) {
        int cap = 1;
        while (cap < expected_size * 2) cap <<= 1;
        table_.resize(cap);
        size_ = 0;
        mask_ = cap - 1;
    }

    void add(int key, int delta = 1) {
        size_t pos = hash((uint64_t)key) & mask_;
        for (auto& p : table_[pos]) {
            if (p.first == key) {
                p.second += delta;
                return;
            }
        }
        table_[pos].emplace_back(key, delta);
        ++size_;
    }

    int get(int key) const {
        size_t pos = hash((uint64_t)key) & mask_;
        for (const auto& p : table_[pos]) {
            if (p.first == key) return p.second;
        }
        return 0;
    }

    bool contains(int key) const {
        size_t pos = hash((uint64_t)key) & mask_;
        for (const auto& p : table_[pos]) {
            if (p.first == key) return true;
        }
        return false;
    }

    void set(int key, int value) {
        size_t pos = hash((uint64_t)key) & mask_;
        for (auto& p : table_[pos]) {
            if (p.first == key) {
                p.second = value;
                return;
            }
        }
        table_[pos].emplace_back(key, value);
        ++size_;
    }

    void clear() {
        for (auto& bucket : table_) {
            bucket.clear();
        }
        size_ = 0;
    }

    int size() const noexcept { 
        return size_; 
    }

private:
    bool CompareCell(const Cell& c1, const Cell& c2) {
        return (c1.first == c2.first &&
                c1.second == c2.second) ? true : false;
    }

    std::vector<std::list<std::pair<int, int>>> table_;
    size_t mask_;
    int size_;
};

} // namespace nr