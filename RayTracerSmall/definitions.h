#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

#if defined __linux__ || defined __APPLE__
#else
#define M_PI 3.141592653589793
#define INFINITY 1e8
#endif
#define MAX_RAY_DEPTH 10
#endif