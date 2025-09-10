# Options Pricing Engine

A high-performance C++ library for pricing European and American-style options using Black-Scholes and Binomial Tree models.

## Features

- **Multiple Pricing Models**
  - Black-Scholes analytical solution for European options
  - Binomial Tree numerical method for American options with early exercise
- **Flexible Payoff System**
  - Call and Put options
  - Extensible architecture for custom payoffs
- **Performance Benchmarking**
  - Runtime comparison between pricing models
  - CSV export of results for analysis
- **Comprehensive Testing**
  - Unit tests for all components
  - Convergence tests between models
  - Edge case validation

## Project Structure

```
project/
├── include/
│   ├── BlackScholesEngine.h    # Black-Scholes pricing engine
│   ├── BinomialTreeEngine.h    # Binomial tree pricing engine
│   ├── Option.h                # Option contract class
│   └── Payoff.h                # Payoff function classes
├── src/
│   ├── BlackScholesEngine.cpp
│   ├── BinomialTreeEngine.cpp
│   ├── Option.cpp
│   ├── Payoff.cpp
│   ├── main.cpp               # Performance comparison demo
│   └── tests.cpp              # Unit tests
└── docs/
    └── pricing_comparison.csv  # Generated benchmark results
```

## Quick Start

### Prerequisites

- C++11 compatible compiler (GCC, Clang, MSVC)
- Standard math library support

### Building

```bash
# Compile the main benchmark program
g++ -std=c++11 -O2 -I./include src/*.cpp -o pricing_engine

# Compile the test suite
g++ -std=c++11 -O2 -I./include src/tests.cpp src/BlackScholesEngine.cpp src/BinomialTreeEngine.cpp src/Option.cpp src/Payoff.cpp -o tests
```

### Running

```bash
# Run performance benchmark
./pricing_engine

# Run unit tests
./tests
```

## Usage Examples

### Basic Option Pricing

```cpp
#include "BlackScholesEngine.h"
#include "BinomialTreeEngine.h"

// Create a call option: Strike $100, 1 year to expiration
auto callPayoff = std::make_shared<CallPayoff>(100.0);
Option callOption(1.0, callPayoff);

// Price with Black-Scholes (European)
BlackScholesEngine bs(100.0, 0.05, 0.2);  // S=$100, r=5%, σ=20%
double europeanPrice = bs.call_price(callOption);

// Price with Binomial Tree (American)
BinomialTreeEngine bt(100.0, 0.05, 0.2, 1000);  // 1000 steps
double americanPrice = bt.price(callOption);

std::cout << "European Call: $" << europeanPrice << std::endl;
std::cout << "American Call: $" << americanPrice << std::endl;
```

### Custom Payoffs

```cpp
// Put option example
auto putPayoff = std::make_shared<PutPayoff>(100.0);
Option putOption(1.0, putPayoff);

double putPrice = bs.put_price(putOption);
std::cout << "Put Price: $" << putPrice << std::endl;
```

## API Reference

### BlackScholesEngine

Analytical pricing engine for European options using the Black-Scholes formula.

**Constructor:**
```cpp
BlackScholesEngine(double spot, double rate, double volatility)
```

**Methods:**
- `double call_price(const Option& option)` - Price European call option
- `double put_price(const Option& option)` - Price European put option

### BinomialTreeEngine

Numerical pricing engine supporting both European and American options with early exercise capability.

**Constructor:**
```cpp
BinomialTreeEngine(double spot, double rate, double volatility, int steps)
```

**Methods:**
- `double price(const Option& option)` - Price option (handles early exercise automatically)

### Option

Represents an option contract with maturity and payoff function.

**Constructor:**
```cpp
Option(double maturity, std::shared_ptr<Payoff> payoff)
```

**Methods:**
- `double get_maturity()` - Get time to expiration in years
- `std::shared_ptr<Payoff> get_payoff()` - Get payoff function

### Payoff Classes

**CallPayoff:**
```cpp
CallPayoff(double strikePrice)
double evaluate(double spotPrice)  // Returns max(spot - strike, 0)
```

**PutPayoff:**
```cpp
PutPayoff(double strikePrice)
double evaluate(double spotPrice)  // Returns max(strike - spot, 0)
```

## Performance Characteristics

The benchmark compares pricing accuracy and computational efficiency:

- **Black-Scholes**: Analytical solution, ~0.01ms per option
- **Binomial Tree**: Numerical approximation, ~1-10ms per option (depends on steps)

For European options, both methods should converge to the same price. American options may show early exercise premium in the binomial tree model.

## Test Cases

The test suite validates:

1. **Payoff Functions**: Correct intrinsic value calculations
2. **Black-Scholes Accuracy**: Known benchmark values
3. **Special Cases**: Zero volatility, expired options
4. **Convergence**: Binomial tree approaching Black-Scholes limit
5. **American Premium**: Early exercise detection

## Mathematical Background

### Black-Scholes Formula

For a European call option:
```
C = S₀N(d₁) - Ke^(-rT)N(d₂)

where:
d₁ = [ln(S₀/K) + (r + σ²/2)T] / (σ√T)
d₂ = d₁ - σ√T
```

### Binomial Tree Model

Uses Cox-Ross-Rubinstein parameterization:
```
u = e^(σ√Δt)
d = 1/u
p = (e^(rΔt) - d) / (u - d)
```

## Extensions

The modular design supports easy extensions:

- **New Payoffs**: Inherit from `Payoff` base class
- **Exotic Options**: Barrier, Asian, Lookback options
- **Greeks Calculation**: Delta, Gamma, Vega, Theta
- **Alternative Models**: Heston, Black-Scholes-Merton

## Contributing

1. Fork the repository
2. Create a feature branch
3. Add comprehensive tests for new functionality
4. Ensure all existing tests pass
5. Submit a pull request

## License

This project is open source. See LICENSE file for details.

## References

- Black, F., & Scholes, M. (1973). The Pricing of Options and Corporate Liabilities
- Cox, J., Ross, S., & Rubinstein, M. (1979). Option Pricing: A Simplified Approach
- Hull, J. (2017). Options, Futures, and Other Derivatives

## Benchmarks

Real performance results from 1000-step binomial tree vs analytical Black-Scholes:

| Scenario | Model | Option Type | Price | Runtime | Notes |
|----------|-------|-------------|-------|---------|-------|
| ATM, σ=20% | Black-Scholes | Call | $10.45 | 0.006ms | Analytical |
| ATM, σ=20% | Binomial Tree | Call | $10.45 | 15.98ms | 2600x slower |
| ATM, σ=20% | Black-Scholes | Put | $5.57 | 0.007ms | European |
| ATM, σ=20% | Binomial Tree | Put | $6.09 | 11.11ms | **American premium** |
| High Vol, σ=40% | Black-Scholes | Put | $13.15 | 0.037ms | European |
| High Vol, σ=40% | Binomial Tree | Put | $13.67 | 9.26ms | **Early exercise value** |
| ITM Put (S=120) | Black-Scholes | Put | $1.29 | 0.005ms | European |
| ITM Put (S=120) | Binomial Tree | Put | $1.37 | 13.17ms | American premium |

### Key Observations:
- **Speed**: Black-Scholes is ~1000-3000x faster than binomial trees
- **American Premium**: Puts show consistent early exercise premium (0.17-0.52)
- **Calls**: Minimal difference (no early exercise advantage for non-dividend paying stocks)
- **Accuracy**: Both models converge well for European-style pricing

*Results from 1000-step binomial tree on standard hardware.*
