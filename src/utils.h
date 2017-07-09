#pragma once
#include<iostream>

class vec
{
public:
    float x;
    float y;

    vec(): x(0),y(0){}
    vec(float x, float y): x(x),y(y){}
    vec(const vec& rhs): x(rhs.x),y(rhs.y){}

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
    friend float abs2(const vec&);
    friend float abs(const vec&);
    friend vec norm(const vec&);
    bool operator==(const vec& rhs)const{ return (x==rhs.x)&&(y==rhs.y); }
    bool operator<(const vec& rhs)const{ return abs2(*this)<abs2(rhs); }
    bool operator>(const vec& rhs)const{ return abs2(*this)>abs2(rhs); }
    friend std::ostream& operator<<(std::ostream& os, const vec& vecc);
};

float abs2(const vec& vecc){ return vecc.x*vecc.x+vecc.y*vecc.y; }
float abs(const vec& vecc){ return sqrt(vecc.x*vecc.x+vecc.y*vecc.y); }
vec norm(const vec& vecc){ return vec((vecc.x==0) ? 0 : vecc.x/sqrt(vecc.x*vecc.x+vecc.y*vecc.y),
                                      (vecc.y==0) ? 0 : vecc.y/sqrt(vecc.x*vecc.x+vecc.y*vecc.y)); }
std::ostream& operator<<(std::ostream& os, const vec& vecc){ os << vecc.x << "," << vecc.y; return os; }