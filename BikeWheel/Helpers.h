#pragma once

#ifdef SIMULATION
#define OPTIMIZE
#else
#define OPTIMIZE __attribute__((optimize("O3")))
#endif