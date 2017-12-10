
class Input{
private:
    int N const;
    double x[N];
    double y[N];

public:
    Input Input();
    virtual Input ReadInput();
};


class ReadInput: public Input
{
private:

public:
    ReadInput();

};

class Func
{
private:
    int a;  // start of interval
    int b;  // end of interval
    int n;  // number of points to generate
    double (*p_function)(double x); // function pointer
public:

    double* GetFuncPointer();
};

double* Func::GetFuncPointer() {
    return reinterpret_cast<double *>(&p_function);
}

class GenerateInput: public Input
{
private:

    Func &p_func;       // points to function to generate data points with
public:


};
