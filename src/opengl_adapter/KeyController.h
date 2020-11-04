#pragma once
#include "Camera.h"
#include <vector>
#include <map>
#include <variant>

namespace LAM {
    class KeyController final {
    public:

        typedef void (*CameraAction)(Camera&, float);
        using Action = std::variant<CameraAction, ActionFunc>;

        static void AddAction(Keys, Action);
        static void RemoveActions(Keys);
        static void PerformAction(Keys, Camera&, float);
        static std::vector<Keys> GetKeys();
    private:
        static std::multimap<Keys, Action> _controls;
    };
}
