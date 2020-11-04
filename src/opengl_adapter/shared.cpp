#include "shared.h"

const LAM::Color LAM::Color::RED = {255, 0, 0, 255};
const LAM::Color LAM::Color::BLUE = {0, 0, 255, 255};
const LAM::Color LAM::Color::GREEN = {0, 255, 0, 255};

const LAM::Color LAM::Color::CYAN = {0, 255, 255, 255};
const LAM::Color LAM::Color::MAGENTA = {255, 0, 255, 255};
const LAM::Color LAM::Color::YELLOW = {255, 255, 0, 255};

const LAM::Color LAM::Color::LIGHTGRAY = {50, 50, 80, 255};
const LAM::Color LAM::Color::TEAL = {0, 50, 80, 255};
const LAM::Color LAM::Color::PURPLE = {50, 0, 80, 255};
const LAM::Color LAM::Color::OLIVE = {50, 80, 0, 255};

const LAM::Color LAM::Color::BLACK = {0, 0, 0, 255};
const LAM::Color LAM::Color::GRAY = {50, 50, 50, 255};
const LAM::Color LAM::Color::WHITE = {255, 255, 255, 255};

LAM::Color LAM::Color::RandomColor() {
    return Color(
                rand() % 256,
                rand() % 256,
                rand() % 256,
                255
                );
}

std::string LAM::Color::toString() const {

    return "(" + std::to_string(static_cast<int>(this->R * 256)) + ", "
            + std::to_string(static_cast<int>(this->G * 256)) + ", "
            + std::to_string(static_cast<int>(this->B * 256)) + ", "
            + std::to_string(static_cast<int>(this->A * 256)) +
            ")";
}
