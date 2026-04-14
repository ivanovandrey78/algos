#include <string>
#include <array>
#include <cstddef>

using ull = unsigned long long;

struct Point {
    ull x; 
    ull y;
};

namespace hash {

static constexpr size_t kTABLE_SIZE = 50000;

namespace hash_func {

template<typename T>
struct Hash;

template<>
struct Hash<std::string> {
    static size_t hash(const std::string& str) {
        unsigned long h = 5381;
        for (char c : str) {
            h = ((h << 5) + h) ^ static_cast<unsigned long>(c);
        }
        return h % kTABLE_SIZE;
    }
};

template<>
struct Hash<int> {
    static size_t hash(int x) {
        unsigned long h = static_cast<unsigned long>(x) * 0x9e3779b9;
        h = (h ^ (h >> 16)) * 0x85ebca6b;
        h = h ^ (h >> 13);
        return h % kTABLE_SIZE;
    }
};

template<>
struct Hash<ull> {
    static size_t hash(ull x) {
        ull h = x * 0x9e3779b9;
        h = (h ^ (h >> 16)) * 0x85ebca6b;
        h = h ^ (h >> 13);
        return h % kTABLE_SIZE;
    }
};

template<>
struct Hash<double> {
    static size_t hash(double x) {
        unsigned long long bits;
        std::memcpy(&bits, &x, sizeof(bits));
        unsigned long h = static_cast<unsigned long>(bits) ^ static_cast<unsigned long>(bits >> 32);
        h = h * 0x9e3779b9;
        h = (h ^ (h >> 16)) * 0x85ebca6b;
        h = h ^ (h >> 13);
        return h % kTABLE_SIZE;
    }
};

} // namespace hash_func

template<typename KeyType>
class HashMap {
public:
    enum class CellState {
        kEMPTY,
        kRESERVED,
        kDELETED
    };

    struct Cell {
        std::string key;
        std::string value;
        CellState state = CellState::kEMPTY;
    };

    HashMap() = default;
    
    bool insert(const KeyType& key, const std::string& value) {
        if (size_ >= capacity_) return false;
        if (value.empty()) return false;

        if constexpr (std::is_same_v<KeyType, std::string>) 
            if (key.empty()) return false;

        size_t index = findIndex(key);
        
        if (table_[index].state == CellState::kRESERVED &&
            table_[index].key == key) 
        {
            table_[index].value = value;
            return true;
        }

        table_[index].key = key;
        table_[index].value = value;
        table_[index].state = CellState::kRESERVED;
        ++size_;
        return true;
    }

    bool erase(const KeyType& key) {
        size_t index = findIndexConst(key);
        
        if (index != kTABLE_SIZE && 
            table_[index].state == CellState::kRESERVED && 
            table_[index].key == key) {
            table_[index].state = CellState::kDELETED;
            table_[index].key = KeyType{};
            table_[index].value.clear();
            --size_;
            return true;
        }
        return false;
    }
    
    bool erase(const std::string& key) {
        size_t index = FindIndex(key);

        if (table_[index].state == CellState::kRESERVED && table_[index].key == key) {
            table_[index].state = CellState::kDELETED;
            table_[index].key.clear();
            table_[index].value.clear();
            --size_;
            return true;
        }
        return false;
    }

    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }

private:    
    size_t FindIndex(const std::string& key) const {
        size_t index = hash_func::Hash<KeyType>::hash(key);
        const size_t start = index;
        size_t first_deleted = kTABLE_SIZE; 

        while (true) {
            const auto& cell = table_[index];
            
            if (cell.state == CellState::kEMPTY) break;
            if (cell.state == CellState::kRESERVED && cell.key == key) return index;
            if (cell.state == CellState::kDELETED && first_deleted == kTABLE_SIZE) 
                first_deleted = index;
            
            index = (index + 1) % kTABLE_SIZE;
            if (index == start) break;
        }
        return first_deleted != kTABLE_SIZE ? first_deleted : start;
    }

    std::array<Cell, kTABLE_SIZE> table_;
    size_t size_ = 0;
    size_t capacity_ = kTABLE_SIZE;
};

} // namespace hash