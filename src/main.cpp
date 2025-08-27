#include "../include/BinomialTreeEngine.h"
#include "../include/BlackScholesEngine.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <chrono>
#include <vector>

struct TestCase {
    double spot, strike, rate, vol, maturity;
    bool isCall;
};

int main() {
    // ~10 varied test cases
    std::vector<TestCase> tests = {
        {100, 100, 0.05, 0.2, 1.0, false}, // ATM Put
        {100, 100, 0.05, 0.2, 1.0, true},  // ATM Call
        {120, 100, 0.05, 0.2, 1.0, false}, // ITM Put
        {80, 100, 0.05, 0.2, 1.0, true},   // ITM Call
        {100, 100, 0.05, 0.4, 1.0, false}, // High vol Put
        {100, 100, 0.05, 0.4, 1.0, true},  // High vol Call
        {100, 100, 0.01, 0.2, 2.0, false}, // Low rate, long T Put
        {100, 100, 0.01, 0.2, 2.0, true},  // Low rate, long T Call
        {100, 90,  0.05, 0.2, 0.5, false}, // Short T Put
        {100, 110, 0.05, 0.2, 0.5, true}   // Short T Call
    };

    std::ofstream csv("../docs/pricing_comparison.csv");
    csv << "Spot,Strike,Rate,Volatility,Maturity,Type,Model,Price,Runtime_ms\n";

    int steps = 1000; // Binomial Tree resolution

    for (const auto& tc : tests) {
        std::shared_ptr<Payoff> payoff = tc.isCall
            ? std::static_pointer_cast<Payoff>(std::make_shared<CallPayoff>(tc.strike))
            : std::static_pointer_cast<Payoff>(std::make_shared<PutPayoff>(tc.strike));
        Option option(tc.maturity, payoff);

        // Black–Scholes
        auto t1 = std::chrono::high_resolution_clock::now();
        BlackScholesEngine bs(tc.spot, tc.rate, tc.vol);
        double euro = tc.isCall ? bs.call_price(option) : bs.put_price(option);
        auto t2 = std::chrono::high_resolution_clock::now();

        // Binomial Tree
        auto t3 = std::chrono::high_resolution_clock::now();
        BinomialTreeEngine bt(tc.spot, tc.rate, tc.vol, steps);
        double amer = bt.price(option);
        auto t4 = std::chrono::high_resolution_clock::now();

        double timeBS = std::chrono::duration<double, std::milli>(t2 - t1).count();
        double timeBT = std::chrono::duration<double, std::milli>(t4 - t3).count();

        std::string type = tc.isCall ? "Call" : "Put";

        // Console
        std::cout << "\nCase: Spot=" << tc.spot << " Strike=" << tc.strike
                  << " Rate=" << tc.rate << " Vol=" << tc.vol
                  << " T=" << tc.maturity << " (" << type << ")\n"
                  << "   Black–Scholes (Euro) : " << euro << " | " << timeBS << " ms\n"
                  << "   Binomial Tree (Amer) : " << amer << " | " << timeBT << " ms\n"
                  << "   Premium Difference   : " << (amer - euro) << "\n";

        // CSV
        csv << tc.spot << "," << tc.strike << "," << tc.rate << "," << tc.vol << "," << tc.maturity << "," << type
            << ",Black-Scholes," << euro << "," << timeBS << "\n";
        csv << tc.spot << "," << tc.strike << "," << tc.rate << "," << tc.vol << "," << tc.maturity << "," << type
            << ",Binomial Tree," << amer << "," << timeBT << "\n";
    }

    csv.close();
    std::cout << "\nResults written to ../docs/pricing_comparison.csv ✅\n";
    return 0;
}
