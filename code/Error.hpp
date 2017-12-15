/*
 * This is the error class. It gives error message when common mistakes
 */

#ifndef SRC_ERROR_HPP_
#define SRC_ERROR_HPP_

#include <exception>
#include <iostream>
#include <sstream>
#include <string>

// Error if the degree is greater than the number of points
class ErrorHighDegreeType : public std::exception
{
private:
    std::string mphrase;
public:
    ErrorHighDegreeType() throw()
    {
        mphrase="ERROR: The degree is too high for the number of points\n";
    }

    virtual const char* what() const throw()
    {
        return mphrase.c_str();
    }
    virtual ~ErrorHighDegreeType() throw()
    {}
};

// Error if the degree is negative
class ErrorNegDegreeType : public std::exception
{
private:
    std::string mphrase;
public:
    ErrorNegDegreeType() throw()
    {
        mphrase="ERROR: The degree is negative\n";
    }

    virtual const char* what() const throw()
    {
        return mphrase.c_str();
    }
    virtual ~ErrorNegDegreeType() throw()
    {}
};

// Error if the data.csv file is empty
class ErrorDataType : public std::exception
{
private:
    std::string mphrase;
public:
    ErrorDataType() throw()
    {
        mphrase="ERROR: The data file is empty or has only one point\n";
    }

    virtual const char* what() const throw()
    {
        return mphrase.c_str();
    }
    virtual ~ErrorDataType() throw()
    {}
};

// Error if the type doesn't exist
class ErrorInterpolationType : public std::exception
{
private:
    std::string mphrase;
public:
    ErrorInterpolationType() throw()
    {
        mphrase="ERROR: The type of interpolation is not accepted by the program\n";
    }

    virtual const char* what() const throw()
    {
        return mphrase.c_str();
    }
    virtual ~ErrorInterpolationType() throw()
    {}
};

// Error if the type and the degree are not compatible
class ErrorDegreeTypeType : public std::exception
{
private:
    std::string mphrase;
public:
    ErrorDegreeTypeType() throw()
    {
        mphrase="ERROR: The degree and the type are not compatible\n";
    }

    virtual const char* what() const throw()
    {
        return mphrase.c_str();
    }
    virtual ~ErrorDegreeTypeType() throw()
    {}
};

// Error with the interpolation points ==> matrix badly condition
class ErrorPointsType : public std::exception
{
private:
    std::string mphrase;
public:
    ErrorPointsType() throw()
    {
        mphrase="ERROR: The interpolation was not found: The polynomial is badly conditioned. A piecewise interpolation is recommended \n";
    }

    virtual const char* what() const throw()
    {
        return mphrase.c_str();
    }
    virtual ~ErrorPointsType() throw()
    {}
};

// Error if not enough argument in the configuration file
class ErrorComaType : public std::exception
{
private:
    std::string mphrase;
public:
    ErrorComaType() throw()
    {
        mphrase="ERROR: Not enough argument in the configuration file \n";
    }

    virtual const char* what() const throw()
    {
        return mphrase.c_str();
    }
    virtual ~ErrorComaType() throw()
    {}
};

#endif /* SRC_ERROR_HPP_ */