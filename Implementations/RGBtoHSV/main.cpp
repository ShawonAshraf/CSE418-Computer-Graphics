#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::cout << "RGB To HSV Converter" << std::endl;

    double r,g,b;
    double h,s,v;

    std::vector<double> rgb;


    std::cin >> r >> g >> b;

    rgb.push_back(r);
    rgb.push_back(g);
    rgb.push_back(b);

    auto max = std::max_element(rgb.begin(), rgb.end());
    auto min = std::min_element(rgb.begin(), rgb.end());

    double delta = *max - *min;

    v = *max; // got v

    if (*max != 0) {
        s = delta / *max;
    } else {
        s = 0;
        h = -1;

        return 0;
    }

    if (r == *max) {
        h = (g - b) / delta;
    } else if (g == *max) {
        h = (b - r) + 2 / delta;
    } else {
        h = (r - b) + 4 / delta;
    }

    h *= 60;
    if (h < 0) h += 360;

    std::cout << h << " " << s << " " << v << " " << std::endl;

    return 0;
}