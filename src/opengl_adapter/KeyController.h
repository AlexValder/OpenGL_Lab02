#pragma once
#include <vector>
#include <map>
#include <variant>
#include "Camera.h"

namespace LAM {
    class KeyController final {
    public:

        using Action = std::variant<CameraAction, ActionFunc>;

        static void AddAction(Keys, Action);
        static void RemoveActions(Keys);
        static void PerformAction(Keys, float);
        static std::vector<Keys> GetKeys();
    private:
        static std::multimap<Keys, Action> _controls;
    };
}
