#include<iostream>
#include <cmath>

struct mat
{
    float m00, m01;
    float m10, m11;

    mat(): m00(0),m01(0), m10(0), m11(0){}
    mat(float m00, float m01, float m10, float m11): m00(m00),m01(m01),m10(m10),m11(m11){}
    mat(const mat& rhs): m00(rhs.m00),m01(rhs.m01),m10(rhs.m10),m11(rhs.m11){}
    mat(float* rhs): m00(rhs[0]),m01(rhs[1]), m10(rhs[2]),m11(rhs[3]){}
    mat(float angle): m00(cos(angle)), m01(-sin(angle)),
                                    m10(sin(angle)), m11(cos(angle)){}
    mat operator=(const mat& rhs){ m00=rhs.m00; m01=rhs.m01; m10=rhs.m10; m11=rhs.m11; return *this; }
    mat operator*(const mat& rhs)const{ return mat( m00*rhs.m00+m01*rhs.m10,    m00*rhs.m01+m01*rhs.m11,
                                                    m10*rhs.m00+m11*rhs.m10,    m10*rhs.m01+m11*rhs.m11); }
    mat operator*(float rhs)const{ return mat(m00*rhs,m01*rhs,m10*rhs,m11*rhs); }
    mat operator*=(float rhs){ m00*=rhs; m01*=rhs; m10*=rhs; m11*=rhs; return *this; }
    mat operator/(float rhs)const{ return mat(m00/rhs,m01/rhs,m10/rhs,m11/rhs); }
    mat operator/=(float rhs){ m00/=rhs; m01/=rhs; m10/=rhs; m11/=rhs; return *this; }
    mat operator+(const mat& rhs)const{ return mat(m00+rhs.m00,m01+rhs.m01,m10+rhs.m10,m11+rhs.m11); }
    mat operator+=(const mat& rhs){ m00+=rhs.m00; m01+=rhs.m01, m10+=rhs.m10; m11+=rhs.m11; return *this; }
    mat operator-(const mat& rhs)const{ return mat(m00-rhs.m00,m01-rhs.m01,m10-rhs.m10,m11-rhs.m11); }
    mat operator-=(const mat& rhs){ m00-=rhs.m00; m01-=rhs.m01; m10-=rhs.m10; m11-=rhs.m11; return *this; }

    vec operator*(const vec& rhs)const{ return vec(m00*rhs.x+m01*rhs.y, m10*rhs.x+m11*rhs.y); }


    friend std::ostream& operator<<(std::ostream& os, const mat& matt){ os << matt.m00 << "," << matt.m01 << "," << matt.m10 << "," << matt.m11; return os; }
};
