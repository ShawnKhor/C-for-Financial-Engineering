#ifndef _AMERICAN_TRADE
#define _AMERICAN_TRADE

#include <cassert>
#include "TreeProduct.h"
#include "Types.h"
#include "Payoff.h"

class AmericanOption : public TreeProduct {
public:
    AmericanOption(OptionType _optType, double _strike, const Date &_expiry, string _name) :
            optType(_optType), strike(_strike), expiryDate(_expiry), name(_name) {}

    virtual double Payoff(double S) const {
        return PAYOFF::VanillaOption(optType, strike, S);
    }

    virtual Date GetExpiry() const {
        return expiryDate;
    }
    virtual double GetPrice() const
    {
        return strike;
    }

    virtual string GetNotional() const override
    {
        return "not applicable";
    }

    virtual double ValueAtNode(double S, double t, double continuation) const {
        return std::max(Payoff(S), continuation);
    }

    virtual string getName() const {
        return name;
    }

private:
    OptionType optType;
    double strike;
    string name;
    Date expiryDate;
};

class AmerCallSpread : public TreeProduct {
public:
    AmerCallSpread(double _k1, double _k2, const Date &_expiry)
            : strike1(_k1), strike2(_k2), expiryDate(_expiry) {
        assert(_k1 < _k2);
    };

    virtual double Payoff(double S) const {
        return PAYOFF::CallSpread(strike1, strike2, S);
    }

    virtual Date GetExpiry() const {
        return expiryDate;
    }


private:
    double strike1;
    double strike2;
    Date expiryDate;
};

#endif