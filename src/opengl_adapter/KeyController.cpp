#include "KeyController.h"
using namespace LAM;

std::multimap<Keys, KeyController::Action> KeyController::_controls {};

void KeyController::AddAction(Keys key, Action action) {
    KeyController::_controls.insert({key, action});
}

void KeyController::RemoveActions(Keys key) {
    auto [begin, end] = KeyController::_controls.equal_range(key);
    while (begin != end) {
        KeyController::_controls.erase(begin++);
    }
}

void KeyController::PerformAction(Keys key, float deltaTime) {
    auto [begin, end] = KeyController::_controls.equal_range(key);
    while (begin != end) {
        auto i = begin->second.index();
        if (i == 0) // CameraAction
            std::get<0>(begin->second)(deltaTime);
        else // ActionFunc
            std::get<1>(begin->second)();
        begin++;
    }
}

std::vector<Keys> KeyController::GetKeys() {
    std::vector<Keys> ret{};
    for (auto it = _controls.begin(), end = _controls.end(); it != end; it = _controls.upper_bound(it->first)) {
          ret.push_back(it->first);
      }
    return ret;
}
