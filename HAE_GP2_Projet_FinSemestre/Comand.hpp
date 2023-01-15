#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

enum class CmdId : int {
    Advance,
    Shoot,
    Reset
};

struct Cmd {
    CmdId id = CmdId::Reset;
    Vector2f direction = Vector2f(0, 0);

    Cmd(CmdId comande, Vector2f d = Vector2f(0, 0)) {
        id = comande;
        direction = d;
    }
};