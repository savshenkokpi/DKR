#ifndef LOWPASSFILTER_H
#define LOWPASSFILTER_H

#include <string>
#include <iostream>

class LowPassFilter {
private:
    double cutoffFrequency;
    double resistance;
    double capacitance;

    void updateCutoffFrequency();

public:
    LowPassFilter();
    LowPassFilter(double resistance, double capacitance);

    void setResistance(double resistance);
    void setCapacitance(double capacitance);

    double getResistance() const;
    double getCapacitance() const;
    double getCutoffFrequency() const;

    double getTransferCoefficient(double frequency) const;
    std::string toString() const;

    void saveEncrypted(const std::string& filename, char key = 'X') const;

    friend std::ostream& operator<<(std::ostream& os, const LowPassFilter& f);
};

#endif // LOWPASSFILTER_H
