#pragma once
class InterpolateStrategy
{
public:
	InterpolateStrategy(void);
	~InterpolateStrategy(void);

	virtual double interpolate( double a, double b, double f );
	virtual float interpolate( float a, float b, float f);
};

