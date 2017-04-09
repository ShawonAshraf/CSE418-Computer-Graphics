#include <iostream>
#include <cmath>

int main() {
    std::cout << "HSV to RGB Converter" << std::endl;

    double h, s, v;
    double r, g, b;

    std::cin >> h >> s >> v;

    if (s == 0) {
        r = g = b = 0; // achromatic light
        std::cout << r << " " << g << " " << b << std::endl;
        return 0;
    }

    h /= 60;
    int i = floor(h);
    double f = h - i;

    double p = v * (1 - s);
    double q = v * (1 - s * f);
    double t = v * (1 - s * (1 - f));

    switch (i) {
        case 0:
            r = v;
            g = t;
            b = p;
            break;
        case 1:
            r = q;
            g = v;
            b = p;
            break;
        case 2:
            r = p;
            g = v;
            b = t;
            break;
        case 3:
            r = p;
            g = q;
            b = v;
            break;
        case 4:
            r = t;
            g = p;
            b = v;
            break;
        default:
            r = v;
            g = p;
            b = q;
            break;

    }

    std::cout << r << " " << g << " " << b << std::endl;
    return 0;
}