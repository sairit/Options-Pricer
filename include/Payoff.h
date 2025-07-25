#ifndef PAYOFF_H
#define PAYOFF_H

// Abstract base class: Payoff
class Payoff {
    public:
        // Virtual destructor to ensure proper cleanup of derived classes
        virtual ~Payoff();
        // Virtual function to evaluate the payoff at a given spot price
        virtual double evaluate(double spotPrice) const = 0; 

};

class CallPayoff : public Payoff{
    private:
        double strikePrice; 

    public:
        explicit CallPayoff(double strikePrice);
        
        double evaluate(double spotPrice) const override; 
};

class PutPayoff : public Payoff{
    private:
        double strikePrice; 

    public:
        explicit PutPayoff(double strikePrice);
        
        double evaluate(double spotPrice) const override; 
};


#endif // PAYOFF_H