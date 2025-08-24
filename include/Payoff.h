#ifndef PAYOFF_H
#define PAYOFF_H

// Abstract base class: Payoff
class Payoff {
    public:
        // Virtual destructor to ensure proper cleanup of derived classes
        virtual ~Payoff();

        // Virtual function to evaluate the payoff at a given spot price
        virtual double evaluate(double spotPrice) const = 0; 

        virtual double get_strike() const = 0;

};

// Derived class: CallPayoff
class CallPayoff : public Payoff{
    private:
        double strikePrice; // Strike price

    public:
        // Constructor: takes in strike price
        explicit CallPayoff(double strikePrice);
        
        double get_strike() const override; 

        // Override evaluate() to compute max(spot - strike, 0)
        double evaluate(double spotPrice) const override; 
};

// Derived class: PutPayoff
class PutPayoff : public Payoff{
    private:
        double strikePrice; // Strike price

    public:
        // Constructor: takes in strike price
        explicit PutPayoff(double strikePrice);
        
        double get_strike() const override; 

        // Override evaluate() to compute max(strike - spot, 0)
        double evaluate(double spotPrice) const override; 
};

#endif // PAYOFF_H