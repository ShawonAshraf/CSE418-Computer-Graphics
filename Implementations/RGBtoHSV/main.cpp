#include <iostream>
#include <algorithm>

double max(double r, double g, double b);

int main() {
    std::cout << "RGB To HSV Converter" << std::endl;

    double r,g,b;
    double h,s,v;

    std::cin >> r >> g >> b;
    double max = max(r, g, b);

    v = max; // got v

    if (max != 0) {

    }


    return 0;
}

double max(double r, double g, double b) {
    if(r > g && r > b) return r;
    else if (g > r && g > b) return g;
    else return b;
}