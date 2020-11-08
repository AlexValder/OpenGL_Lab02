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

LAM::Color::Color(const glm::vec3& vec) : R(vec[0]), G(vec[1]), B(vec[2]), A(1.f) {}

LAM::Color::Color(const glm::vec4& vec) : R(vec[0]), G(vec[1]), B(vec[2]), A(vec[3]) {}

LAM::Color::operator glm::vec3() const {
    return glm::vec3(this->R, this->G, this->B);
}

LAM::Color::operator glm::vec4() const {
    return glm::vec4(this->R, this->G, this->B, this->A);
}


LAM::Color LAM::Color::RandomColor(uint8_t lower, uint8_t upper) {
    assert(0 <= lower && lower <= upper && upper <= 255);
    return Color(
                rand() % upper + lower,
                rand() % upper + lower,
                rand() % upper + lower,
                rand() % upper + lower
                );
}

std::string LAM::Color::toString() const {

    return "(" + std::to_string(static_cast<int>(this->R * 256)) + ", "
            + std::to_string(static_cast<int>(this->G * 256)) + ", "
            + std::to_string(static_cast<int>(this->B * 256)) + ", "
            + std::to_string(static_cast<int>(this->A * 256)) +
            ")";
}
