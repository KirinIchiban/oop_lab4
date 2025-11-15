#include <gtest/gtest.h>
#include <stdexcept>
#include <iostream>

#include "../include/point.h"
#include "../include/triangle.h"
#include "../include/square.h"
#include "../include/array.h"
#include "../include/rectangle.h"

using namespace std;


TEST(FigureTest, SquareDefault) {
    Square<double> s;
    EXPECT_EQ(s.get_radius(), 1.0);
    EXPECT_EQ(s.Center().get_x(), 0.0);
    EXPECT_EQ(s.Center().get_y(), 0.0);
}

TEST(FigureTest, SquareByUs) {
    Square<double> s(Point<double>(1.0, 2.0), 3.0);
    EXPECT_EQ(s.get_radius(), 3.0);
    EXPECT_EQ(s.Center().get_x(), 1.0);
    EXPECT_EQ(s.Center().get_y(), 2.0);
}

TEST(FigureTest, TriangleDefault) {
    Triangle<double> t;
    EXPECT_EQ(t.get_radius(), 1.0);
    EXPECT_EQ(t.Center().get_x(), 0.0);
    EXPECT_EQ(t.Center().get_y(), 0.0);
}

TEST(FigureTest, RectanglebUs) {
    Rectangle<double> r(Point<double>(3.0, 4.0), 5.0, 2.0); 
    EXPECT_EQ(r.get_radius(), 5.0);
    EXPECT_EQ(r.Center().get_x(), 3.0);
    EXPECT_EQ(r.Center().get_y(), 4.0);
}

// ТЕСТЫ ПЛОЩАДЕЙ 

TEST(FigureTest, SquareArea) {
    Square<double> s(Point<double>(0, 0), 5.0);
    double expected_area = 2 * 5.0 * 5.0;
    EXPECT_DOUBLE_EQ(static_cast<double>(s), expected_area);
    EXPECT_DOUBLE_EQ(s.Squere(), expected_area);
}

TEST(FigureTest, TriangleArea) {
    Triangle<double> t;
    double area = static_cast<double>(t);
    EXPECT_GT(area, 0.5);
    EXPECT_LT(area, 1.5);
}

TEST(FigureTest, RectangleArea) {
    Rectangle<double> r(Point<double>(0, 0), 5.0, 2.0);
    double area = static_cast<double>(r);
    EXPECT_GT(area, 0.0);
}

// ТЕСТЫ ОПЕРАТОРОВ РАВЕНСТВА 

TEST(FigureTest, SquareEq) {
    Square<double> s1(Point<double>(1, 2), 3.0);
    Square<double> s2(Point<double>(1, 2), 3.0);
    Square<double> s3(Point<double>(0, 0), 3.0);
    Square<double> s4(Point<double>(1, 2), 4.0);
    
    Shape<double>& sh1 = s1;
    Shape<double>& sh2 = s2;
    Shape<double>& sh3 = s3;
    Shape<double>& sh4 = s4;

    EXPECT_TRUE(sh1 == sh2);
    EXPECT_TRUE(sh1 == sh3);
    EXPECT_FALSE(sh1 == sh4);
}

TEST(FigureTest, TriangleEqual) {
    Triangle<double> t1(Point<double>(1, 2), 3.0, M_PI/3);
    Triangle<double> t2(Point<double>(1, 2), 3.0, M_PI/3);
    Triangle<double> t3(Point<double>(0, 0), 3.0, M_PI/3);
    Triangle<double> t4(Point<double>(1, 2), 3.0, M_PI/4); 
    
    Shape<double>& sh1 = t1;
    Shape<double>& sh2 = t2;
    Shape<double>& sh3 = t3;
    Shape<double>& sh4 = t4;

    EXPECT_TRUE(sh1 == sh2);
    EXPECT_FALSE(sh1 == sh3);
    EXPECT_FALSE(sh1 == sh4);
}

TEST(FigureTest, RectangleEq) {
    Rectangle<double> r1(Point<double>(1, 2), 3.0, 2.0);
    Rectangle<double> r2(Point<double>(1, 2), 3.0, 2.0);
    Rectangle<double> r3(Point<double>(0, 0), 3.0, 2.0);
    Rectangle<double> r4(Point<double>(1, 2), 3.0, 1.0); 
    
    Shape<double>& sh1 = r1;
    Shape<double>& sh2 = r2;
    Shape<double>& sh3 = r3;
    Shape<double>& sh4 = r4;

    EXPECT_TRUE(sh1 == sh2);
    EXPECT_FALSE(sh1 == sh3);
    EXPECT_FALSE(sh1 == sh4);
}

// ТЕСТЫ РАЗНЫХ ФИГУР 

TEST(FigureTest, DiffShapesEq) {
    Square<double> square(Point<double>(1, 2), 3.0);
    Triangle<double> triangle(Point<double>(1, 2), 3.0, M_PI/3);
    Rectangle<double> rectangle(Point<double>(1, 2), 3.0, 2.0);
    
    Shape<double>& shSquare = square;
    Shape<double>& shTriangle = triangle;
    Shape<double>& shRectangle = rectangle;

    EXPECT_FALSE(shSquare == shTriangle);
    EXPECT_FALSE(shSquare == shRectangle);
    EXPECT_FALSE(shTriangle == shRectangle);
}

TEST(FigureTest, SquareCopy) {
    Square<double> original(Point<double>(1, 2), 3.0);
    Square<double> copy = original;
    EXPECT_TRUE(original == copy);
    EXPECT_DOUBLE_EQ(static_cast<double>(original), static_cast<double>(copy));
}

TEST(FigureTest, TriangleCp) {
    Triangle<double> original(Point<double>(1, 2), 3.0, M_PI/3);
    Triangle<double> copy(original);

    Shape<double>& orig = original;
    Shape<double>& cop = copy; 
    EXPECT_TRUE(orig == cop);
}

TEST(FigureTest, SquareMove) {
    Square<double> original(Point<double>(1, 2), 3.0);
    double original_area = static_cast<double>(original);
    Square<double> moved = std::move(original);
    EXPECT_DOUBLE_EQ(static_cast<double>(moved), original_area);
}

TEST(FigureTest, SquareOutput) {
    Square<double> s(Point<double>(1, 2), 3.0);
    testing::internal::CaptureStdout();
    std::cout << s;
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Square") != std::string::npos);
    EXPECT_TRUE(output.find("(1, 2)") != std::string::npos);
    EXPECT_TRUE(output.find("3") != std::string::npos);
}

TEST(FigureTest, ZeroRadius) {
    Square<double> s(Point<double>(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(static_cast<double>(s), 0.0);
    
    Triangle<double> t(Point<double>(0, 0), 0.0, M_PI/3);
    EXPECT_DOUBLE_EQ(static_cast<double>(t), 0.0);
}

TEST(FigureTest, SelfComparison) {
    Square<double> s(Point<double>(1, 2), 3.0);
    EXPECT_TRUE(s == s);
}

// ==================== MAIN ====================

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
