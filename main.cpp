#include <iostream>
#include "LowPassFilter.h"

int main() {
    try {
        LowPassFilter filter(1000, 0.000001);  // R = 1kΩ, C = 1μF
        std::cout << filter << std::endl;

        double freq = 1000;  // Частота 1 кГц
        std::cout << "Коефіцієнт передачі на " << freq << " Гц: "
                  << filter.getTransferCoefficient(freq) << std::endl;

        filter.saveEncrypted("filter.dat");

    } catch (const std::exception& e) {
        std::cerr << "Помилка: " << e.what() << std::endl;
        Logger::log(std::string("Виключення: ") + e.what());
    }

    return 0;
}
