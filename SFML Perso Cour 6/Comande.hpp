#pragma once

enum class CmdId : int {
    Advance,
    RotateLeft,
    RotateRight,
    Reset,
    PenChange,
};

struct Cmd {
    CmdId id = CmdId::Reset;
    double data = 0;

    Cmd(CmdId comande, double d) {
        id = comande;
        data = d;
    }
};