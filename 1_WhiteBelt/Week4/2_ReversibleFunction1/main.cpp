#include <iostream>
#include "Function.h"

using namespace std;

struct Image {
    double quality;
    double freshness;
    double rating;
};

struct Params {
    double a;
    double b;
    double c;
};

Function MakeWeightFunction(const Params& params,
                            const Image& image) {
    Function function;
    function.AddPart('-', image.freshness * params.a + params.b);
    function.AddPart('+', image.rating * params.c);
    return function;
}

double ComputeImageWeight(const Params& params, const Image& image) {
    Function function = MakeWeightFunction(params, image);
    return function.Apply(image.quality);
}

double ComputeQualityByWeight(const Params& params,
                              const Image& image,
                              double weight) {
    Function function = MakeWeightFunction(params, image);
    function.Invert();
    return function.Apply(weight);
}

int main() {
    Image image = {10, 2, 6};
    Params params = {4, 2, 6};
    cout << ComputeImageWeight(params, image) << endl;
    cout << ComputeQualityByWeight(params, image, 46) << endl;
    return 0;
}
