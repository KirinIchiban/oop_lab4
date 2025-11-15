#pragma once

#include "shape.h"

template <Scalar T>
class Triangle : public Shape<T>
{
public:
    Triangle() : Shape<T>(), alpha(M_PI / 3) {
        this->make_figure();
    }
    Triangle(const Point<T> &center, T radius, T alpha_rad = M_PI / 3) : Shape<T>(center, radius), alpha(alpha_rad) {
        this->make_figure();
    }

    virtual double Squere() const override {
        return Squere_triangle(*this->coords[0], *this->coords[1], *this->coords[2]);
    }

    Triangle& operator=(const Triangle& other) {
        if (this != &other) {
            Shape<T>::operator=(other);  
            alpha = other.alpha; 
            make_figure(); 
        }
        return *this;
    }

    bool operator==(const Shape<T>& other) const override{
        auto o = dynamic_cast<const Triangle*>(&other);
        if (!o) return false;
        return this->center == o->center && this->radius == o->radius && this->alpha == o->alpha;
    }


protected:
    T alpha; 

    void make_figure() override {
        this->coords.clear();

        T cx = this->center.get_x();
        T cy = this->center.get_y();
        T R  = this->radius;

        // по теореме синусов
        T half_base = R * std::sin(alpha);
        T h = R * std::cos(alpha / 2);

        bool is_sharp = (alpha <= M_PI / 2);
        T y_top, y_base;
        if (is_sharp) {
            y_top  = cy + 2*h/3;
            y_base = cy - h/3;
 
        } else {
            y_top  = cy + h + std::sqrt(R*R - half_base*half_base);
            y_base = cy + std::sqrt(R*R - half_base*half_base);
        }

        this->center.m_y = y_base + h/3;
        T xA = cx - half_base;
        T yA = y_base;
        T xB = cx + half_base;
        T yB = y_base;
        T xC = cx;
        T yC = y_top;

        this->coords.push_back(std::make_unique<Point<T>>(xA, yA));
        this->coords.push_back(std::make_unique<Point<T>>(xB, yB));
        this->coords.push_back(std::make_unique<Point<T>>(xC, yC));
    }

    const char* get_name() const override {
        return "Triangle";
    }
};

template<Scalar T>
inline double Squere_triangle(const Point<T>& A, const Point<T>& B, const Point<T>& C) {
    return std::fabs(
        A.get_x() * (B.get_y() - C.get_y()) + 
        B.get_x() * (C.get_y() - A.get_y()) + 
        C.get_x() * (A.get_y() - B.get_y())
    ) / 2.0;  
}
