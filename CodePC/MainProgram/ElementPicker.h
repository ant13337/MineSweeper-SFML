#pragma once

#include <vector>

template <typename T>
class ElementPicker {
public:
    ElementPicker(const std::vector<T>& elements, const std::vector<T>& excludeElements = {});
    T pickRandomElement() const;
private:
    std::vector<T> elements_;
    std::vector<T> excludeElements_;
};