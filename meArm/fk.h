#ifndef FK_H_INCLUDED
#define FK_H_INCLUDED
/*
Comments starting with J are ade by Job Ramirez
*/

void polar2cart(float r, float theta, float& a, float& b);           //  The inputs are r and theta with outputs a b (a vector in cartesian)

void unsolve(float a0, float a1, float a2, float& x, float& y, float& z);        // 

float distance(float x1, float y1, float z1, float x2, float y2, float z2);          //

#endif // FK_H_INCLUDED
