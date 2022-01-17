#pragma once

class ComputeMax {
  public:
    int Compute(int a, int b, int c) {
        int max = (a > b ? a : b);
        return (max > c ? max : c);
    }
};