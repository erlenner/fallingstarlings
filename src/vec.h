#pragma once
#include<iostream>

class vec
{
public:
    double x;
    double y;

    vec(): x(0),y(0){}
    vec(double x, double y): x(x),y(y){}
    vec(const vec& rhs): x(rhs.x),y(rhs.y){}

    vec operator=(const vec& rhs){ x=rhs.x; y=rhs.y; return *this; }
    double operator*(const vec& rhs)const{ return x*rhs.x+y*rhs.y; }
    vec operator*(double rhs)const{ return vec(x*rhs,y*rhs); }
    vec operator*=(double rhs){ x*=rhs; y*=rhs; return *this; }
    vec operator/(double rhs)const{ return vec(x/rhs,y/rhs); }
    vec operator/=(double rhs){ x/=rhs; y/=rhs; return *this; }
    vec operator+(const vec& rhs)const{ return vec(x+rhs.x,y+rhs.y); }
    vec operator+=(const vec& rhs){ x+=rhs.x; y+=rhs.y; return *this; }
    vec operator-(const vec& rhs)const{ return vec(x-rhs.x,y-rhs.y); }
    vec operator-=(const vec& rhs){ x-=rhs.x; y-=rhs.y; return *this; }
    friend double abs2(const vec&);
    friend double abs(const vec&);
    friend vec norm(const vec&);
    bool operator==(const vec& rhs)const{ return (x==rhs.x)&&(y==rhs.y); }
    bool operator<(const vec& rhs)const{ return abs2(*this)<abs2(rhs); }
    bool operator>(const vec& rhs)const{ return abs2(*this)>abs2(rhs); }
    friend vec operator^(const vec& lhs, const vec& rhs);
    friend std::ostream& operator<<(std::ostream& os, const vec& vecc);
};

double abs2(const vec& vecc){ return vecc.x*vecc.x+vecc.y*vecc.y; }
double abs(const vec& vecc){ return sqrt(vecc.x*vecc.x+vecc.y*vecc.y); }
vec norm(const vec& vecc){ return vec((vecc.x==0) ? 0 : vecc.x/sqrt(vecc.x*vecc.x+vecc.y*vecc.y),
                                      (vecc.y==0) ? 0 : vecc.y/sqrt(vecc.x*vecc.x+vecc.y*vecc.y)); }
vec operator^(const vec& lhs, const vec& rhs){ return vec(lhs.x*rhs.x, lhs.y*rhs.y); }

std::ostream& operator<<(std::ostream& os, const vec& vecc){ os << vecc.x << "," << vecc.y; return os; }
