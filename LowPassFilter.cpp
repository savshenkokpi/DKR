#include "LowPassFilter.h"
#include "Logger.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

LowPassFilter::LowPassFilter() : cutoffFrequency(0), resistance(1), capacitance(1) {
    updateCutoffFrequency();
    Logger::log("Створено фільтр за замовчуванням");
}

LowPassFilter::LowPassFilter(double r, double c) {
    setResistance(r);
    setCapacitance(c);
    updateCutoffFrequency();
    Logger::log("Створено фільтр з параметрами");
}

void LowPassFilter::setResistance(double r) {
    if (r <= 0) throw std::invalid_argument("Опір має бути позитивним.");
    resistance = r;
    updateCutoffFrequency();
}

void LowPassFilter::setCapacitance(double c) {
    if (c <= 0) throw std::invalid_argument("Ємність має бути позитивною.");
    capacitance = c;
    updateCutoffFrequency();
}

double LowPassFilter::getResistance() const { return resistance; }
double LowPassFilter::getCapacitance() const { return capacitance; }
double LowPassFilter::getCutoffFrequency() const { return cutoffFrequency; }

void LowPassFilter::updateCutoffFrequency() {
    cutoffFrequency = 1.0 / (2 * M_PI * resistance * capacitance);
}

double LowPassFilter::getTransferCoefficient(double frequency) const {
    double omega = 2 * M_PI * frequency;
    double rc = resistance * capacitance;
    return 1.0 / sqrt(1 + pow(omega * rc, 2));
}

std::string LowPassFilter::toString() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "RC Low-Pass Filter: R = " << resistance
        << " Ω, C = " << capacitance
        << " F, Cutoff = " << cutoffFrequency << " Hz";
    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const LowPassFilter& f) {
    os << f.toString();
    return os;
}

void LowPassFilter::saveEncrypted(const std::string& filename, char key) const {
    std::ofstream file(filename, std::ios::binary);
    std::string data = toString();
    for (char& c : data) {
        c ^= key;
    }
    file.write(data.c_str(), data.size());
    file.close();
    Logger::log("Фільтр збережено у файл з шифруванням");
}
