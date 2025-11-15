#include "include/square.h"
#include "include/triangle.h"
#include "include/rectangle.h"
#include "include/array.h"
#include <iostream>
#include <limits>
#include <memory>

using namespace std;

int main() {
    Array<shared_ptr<Shape<double>>> figures; 
    int ch;

    while (true) {
        cout << "1. Add Square\n"
                "2. Add Triangle\n"
                "3. Add Rectangle\n"
                "4. Print array\n"
                "5. Print centers\n"
                "6. Total Area\n"
                "7. Remove\n"
                "0. Exit\n"
                "-> ";

        if (!(cin >> ch)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again\n";
            continue;
        }

        switch (ch) {
            case 0:
                return 0;

            case 1: { 
                cout << "Enter square data (cx cy radius): ";
                Square<double>* sq = new Square<double>();
                if (cin >> *sq) {
                    figures.Add(shared_ptr<Shape<double>>(sq));
                } else {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Input error.\n";
                    delete sq;
                }
                break;
            }

            case 2: {  
                cout << "Enter triangle data (cx cy radius): ";
                Triangle<double>* tri = new Triangle<double>();
                if (cin >> *tri) {
                    figures.Add(shared_ptr<Shape<double>>(tri));
                } else {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Input error.\n";
                    delete tri;
                }
                break;
            }

            case 3: { 
                cout << "Enter rectangle data (cx cy radius height_ratio): ";
                Rectangle<double>* rect = new Rectangle<double>();
                if (cin >> *rect) {
                    figures.Add(shared_ptr<Shape<double>>(rect));
                } else {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Input error.\n";
                    delete rect;
                }
                break;
            }

            case 4: {  
                cout << "All figures:\n";
                figures.Print();
                break;
            }

            case 5: {  
                cout << "Centers of all figures:\n";
                figures.All_Centers();
                break;
            }

            case 6: {  
                cout << "Total area: " << figures.All_squeare() << "\n";
                break;
            }

            case 7: {  
                size_t idx;
                cout << "Index: ";
                if (cin >> idx) {
                    try {
                        figures.Remove(idx);
                        cout << "Figure at index " << idx << " removed successfully\n";
                    } catch (const exception& ex) {
                        cerr << "Error: " << ex.what() << "\n";
                    }
                } else {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid index\n";
                }
                break;
            }

            default:
                cout << "Invalid choice. Try again.\n";
                break;
        }
    }

    return 0;
}
