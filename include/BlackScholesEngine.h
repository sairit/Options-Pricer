#ifndef BLACKSCHOLESENGINE_H
#define BLACKSCHOLESENGINE_H

#include <cmath>
#include <algorithm>
#include "Option.h"

class BlackScholesEngine {
    private:
        double spot;      // Spot price
        double rate;      // Risk-free rate
        double volatility;  // Volatility
        static constexpr double TINY_EPSILON = 1e-8; 

        // Normal CDF helper
        static double norm_cdf(double x);

    public:
        BlackScholesEngine(double spot, double rate, double volatility);

        // Pricing methods
        double call_price(const Option& option) const;
        double put_price(const Option& option) const;

        // Future plans for extensions (Greeks): double delta_call(...), double vega(...), etc.
};

#endif // BLACKSCHOLESENGINE_H