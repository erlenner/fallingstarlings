#include<iostream>
#include <cmath>

struct vec
{
    float x;
    float y;

    vec(): x(0),y(0){}
    vec(float x, float y): x(x),y(y){}
    vec(const vec& rhs): x(rhs.x),y(rhs.y){}
    vec(const float* rhs): x(rhs[0]),y(rhs[1]){}

    vec operator=(const vec& rhs){ x=rhs.x; y=rhs.y; return *this; }
    float operator*(const vec& rhs)const{ return x*rhs.x+y*rhs.y; }
    vec operator*(float rhs)const{ return vec(x*rhs,y*rhs); }
    vec operator*=(float rhs){ x*=rhs; y*=rhs; return *this; }
    vec operator/(float rhs)const{ return vec(x/rhs,y/rhs); }
    vec operator/=(float rhs){ x/=rhs; y/=rhs; return *this; }
    vec operator+(const vec& rhs)const{ return vec(x+rhs.x,y+rhs.y); }
    vec operator+=(const vec& rhs){ x+=rhs.x; y+=rhs.y; return *this; }
    vec operator-(const vec& rhs)const{ return vec(x-rhs.x,y-rhs.y); }
    vec operator-=(const vec& rhs){ x-=rhs.x; y-=rhs.y; return *this; }
    friend float abs2(const vec& vecc){ return vecc.x*vecc.x+vecc.y*vecc.y; }
    friend float abs(const vec& vecc){ return sqrt(vecc.x*vecc.x+vecc.y*vecc.y); }
    friend vec norm(const vec& vecc){ return    vec((vecc.x==0) ? 0 : vecc.x/sqrt(vecc.x*vecc.x+vecc.y*vecc.y),
                                                    (vecc.y==0) ? 0 : vecc.y/sqrt(vecc.x*vecc.x+vecc.y*vecc.y)); }
    friend float maxDim(const vec& vecc){ return vecc.x*vecc.x > vecc.y*vecc.y ? vecc.x : vecc.y; }
    bool operator==(const vec& rhs)const{ return (x==rhs.x)&&(y==rhs.y); }
    bool operator<(const vec& rhs)const{ return abs2(*this)<abs2(rhs); }
    bool operator>(const vec& rhs)const{ return abs2(*this)>abs2(rhs); }
    friend vec operator^(const vec& lhs, const vec& rhs){ return vec(lhs.x*rhs.x, lhs.y*rhs.y); }
    friend vec operator*(float lhs, const vec& rhs){ return rhs*lhs; }
    friend std::ostream& operator<<(std::ostream& os, const vec& vecc){ os << vecc.x << "," << vecc.y; return os; }
};
