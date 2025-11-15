#pragma once

#include "shape.h"

template <Scalar T>
class Rectangle : public Shape<T>
{
public:
    Rectangle(): Shape<T>(), scale(1) {
        this->make_figure();
    };
    Rectangle(const Point<T> &center, T radius, T us_scale = 1.0) : Shape<T>(center, radius), scale(us_scale) {
        this->make_figure();
    }

    Rectangle& operator=(const Rectangle& other) {
        if (this != &other) {
            Shape<T>::operator=(other);  
            scale = other.scale; 
            make_figure(); 
        }
        return *this;
    }

    bool operator==(const Shape<T>& other) const override {
        auto o = dynamic_cast<const Rectangle*>(&other);
        if (!o) return false;
        return this->center == o->center && this->radius == o->radius && this->scale == o->scale;
    }

    virtual double Squere() const override {
        double S1 = Squere_triangle(*this->coords[0], *this->coords[1], *this->coords[2]);
        double S2 = Squere_triangle(*this->coords[0], *this->coords[2], *this->coords[3]);
        return S1 + S2;
    }

protected:
    T scale;  //scale = height/width

    void make_figure() override {
        this->coords.clear();
        T diag = 2 * this->radius;
        T cx = this->center.get_x();
        T cy = this->center.get_y();

        T width  = diag / std::sqrt(1 + scale * scale);
        T height = width * scale;

        T half_w = width / 2;
        T half_h = height / 2;

        // Вершины по часовой стрелке
        this->coords.push_back(std::make_unique<Point<T>>(cx - half_w, cy - half_h)); 
        this->coords.push_back(std::make_unique<Point<T>>(cx - half_w, cy + half_h));  
        this->coords.push_back(std::make_unique<Point<T>>(cx + half_w, cy + half_h));  
        this->coords.push_back(std::make_unique<Point<T>>(cx + half_w, cy - half_h));  
    }

    const char* get_name() const override {
        return "Rectangle";
    }
};

template<Scalar T>
inline double Squere_Rectangle(const Point<T>& A, const Point<T>& B, const Point<T>& C) {
    return std::fabs(
        A.get_x() * (B.get_y() - C.get_y()) + 
        B.get_x() * (C.get_y() - A.get_y()) + 
        C.get_x() * (A.get_y() - B.get_y())
    ) / 2.0;  
}
