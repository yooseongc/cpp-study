#include <iostream>
#include <string>

using namespace std;

class person
{
public:
    person() = default;
    explicit person(const string& name) : name(name) {}
    virtual ~person() = default;
    void set_name(const string& n) { name = n; }
    string get_name() const { return name; }
    virtual void all_info() const
    {
        cout << "[person] My name is " << name << endl;
    }
protected:
    string name;
};

class student
    : public virtual person
{
public:
    student(const string& name, const string& passed)
        : person(name), passed(passed)
    {}

protected:
    student(const string& passed) : passed(passed) {}

    void my_info() const
    {
        cout << " I passed the following grades: " << passed << endl;
    }

public:
    virtual void all_info() const override
    {
        person::all_info();
        my_info();
    }

private:
    string passed;
};

class mathematician
    : public virtual person
{
public:
    mathematician(const string& name, const string& proved)
        : person(name), proved(proved)
    {}

protected:
    mathematician(const string& proved) : proved(proved) {}

    void my_info() const
    {
        cout << " I proved: " << proved << endl;
    }

public:
    virtual void all_info() const override
    {
        person::all_info();
        my_info();
    }

private:
    string proved;
};

class math_student
    : public student, public mathematician
{
public: 
    math_student(const string& name, const string& passed, const string& proved)
        : person(name), student(passed), mathematician(proved)
    {}

    virtual void all_info() const override
    {
        person::all_info();
        student::my_info();
        mathematician::my_info();
    }
};

int main()
{
    math_student bob("Robert Robson", "Algebra", "Fermat's Last Theorem");
    bob.all_info();

    math_student* bp = &bob;
    cout << hex
         << "bp            = " << bp << endl
         << "math          = " << static_cast<mathematician*>(bp) << endl
         << "person math   = " << static_cast<person*>(static_cast<mathematician*>(bp)) << endl
         << "studi         = " << static_cast<student*>(bp) << endl
         << "person studi  = " << static_cast<person*>(static_cast<student*>(bp)) << endl;

    return 0;
}
