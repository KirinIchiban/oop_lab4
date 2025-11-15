#pragma once

#include "shape.h"
#include <memory>
#include <utility>

template<typename T>
class Array {
public:
    Array();
    Array(size_t capacity);
    void Add(const T& shape);
    void Remove(size_t index);
    T get_element(size_t index) const;
    void Print() const;
    double All_squeare() const;
    void All_Centers() const;
    ~Array() = default;

private:
    std::shared_ptr<T[]> data;     
    size_t size;       
    size_t capacity;
    void Resize();
};

template<typename T>
Array<T>::Array() : data(nullptr), size(0), capacity(0) {}

template<typename T>
Array<T>::Array(size_t capacity) : size(0), capacity(capacity) {
    data = std::shared_ptr<T[]>(new T[capacity]);
}

template<typename T>
void Array<T>::Add(const T& shape) {
    if (size >= capacity) {
        Resize();
    }
    data[size++] = std::move(shape);
}

template<typename T>
void Array<T>::Remove(size_t index) {
    if (size == 0) {
        throw std::out_of_range("Empty_array");
    }
    if (index >= size) {
        throw std::out_of_range("Out_of_range");
    }
    data[index].reset();
    for (size_t i = index; i < size - 1; i++) {
            data[i] = std::move(data[i + 1]);
        }
    data[--size] = nullptr;
}

template<typename T>
void Array<T>::Print() const {
    if (size == 0) {
        return;
    }
    for (size_t i = 0; i < size; ++i) {
        if constexpr (requires { *data[i]; }) {
                std::cout << i << data[i]->get_name() << ": " << data[i]->Center()
                          << " | Area: " << static_cast<double>(*data[i]) << "\n";
        }
        else { return; }
    }
}

template<typename T>
T Array<T>::get_element(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index_out_of_range");
    }
    return data[index];
}

template<typename T>
double Array<T>::All_squeare() const {
    if (size == 0) {
        return -1.0;
    }
    double total = 0.0;
    for (size_t i = 0; i < size; i++) {
        total += static_cast<double>(*data[i]);  //перегруженный оператор вернет площадь фигуры
    }
    return total;
}

template<typename T>
void Array<T>::All_Centers() const {
    for (size_t i = 0; i < size; i++ ) {
        std::cout << "Figure: " << i << " : ";
        std::cout << "Center: " <<data[i]->Center();
    }
}

template<typename T>
void Array<T>::Resize() {
        size_t new_capacity = (capacity == 0) ? 2 : capacity * 2;
        auto newData = std::make_shared<T[]>(new_capacity);

        for (size_t i = 0; i < size; ++i)
            newData[i] = std::move(data[i]);

        data = std::move(newData);
        capacity = new_capacity;
}