#pragma once

#include <cstddef>
#include <vector>
#include <iostream>

template <typename TypeData, std::size_t CAPACITY>
struct CircularBuffer {
    
    explicit CircularBuffer () {
        buffer_.reserve(CAPACITY);
    }

    void clear () noexcept {
        buffer_.clear();
        last_ = 0;
    }
    
    void push_back (const TypeData& data) {
        if (buffer_.size() < CAPACITY) {
            buffer_.push_back(data);
        } else {
            buffer_.at(last_) = data;
        }        
        last_ = (last_ + 1) % CAPACITY;
    }

    const std::vector<TypeData>& getBuffer() const noexcept {
        return buffer_;
    }

    void print () const {
        std::cout << "size: " << buffer_.size() << "\n";
        for (std::size_t i = 0 ; i < buffer_.size() ; ++i) {
            std::cout << buffer_.at((last_ + i) % buffer_.size()) << " ";
        }
    }

private:
    std::size_t last_ { 0 };
    std::vector<TypeData> buffer_;
};