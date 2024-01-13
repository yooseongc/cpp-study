#include <iostream>

struct A
{
    virtual void f() {}
    virtual ~A() {}
    int ma;
};

#if 1

struct B : A
{
    int fb() { return 3; }
    float mb;
};

struct C : A {};

#else

struct B : virtual A
{
    int fb() { return 3; }
    float mb;
};

struct C : virtual A {};

#endif

struct D : B, C {};

struct F {};

void f(A a) { }
// void g(A& a) { }
void h(A* a) { }

void g(A& a)
{
    B& bref = static_cast<B&>(a);
    std::cout << "fb returns " << bref.fb() << std::endl;
}

int main(int argc, char* argv[])
{
    B b;
    f(b);
    g(b);
    h(&b);

    D d;
#if 0
    A ad(d);  // ambigious (D -> B -> A or D -> C -> A)
#else
    A ad(B(d));  // D -> B -> A
#endif

    B *bbp = new B, *bdp = new D;
    B *bxp = argc > 1 ? new B : new D;

    D* dbp = dynamic_cast<D*>(bbp);  // Error: cannot downcast to D
    D* ddp = dynamic_cast<D*>(bdp);  // OK: bdp points to a D object
    D& dref1 = dynamic_cast<D&>(*bdp);  
    // D& dref2 = dynamic_cast<D&>(b);  // Throws bad_cast

    std::cout << "Dynamic downcast of bbp should fail and pointer should be 0, it is: " << dbp << std::endl;
    std::cout << "Dynamic downcast of bdp should succeed and pointer should not be 0, it is: " << ddp << std::endl;

    dbp = static_cast<D*>(bbp);  // erroneous downcast performed
    ddp = static_cast<D*>(bdp);  // correct downcast but not checked by the system
    // D dobj = static_cast<D>(b);  // Error: can only cast references or pointers

    std::cout << "Erroneous downcast of bbp will not return 0, it is: " << dbp << std::endl;
    std::cout << "Correct downcast of bdp but not checked at run-time, it is: " << ddp << std::endl;

    C* cdp = dynamic_cast<C*>(bdp);  // cross-cast from B to C ok: bdp points to an object of type D
    std::cout << "Dynamic cross-cast of bdp should succeed and pointer should not be 0, it is: " << cdp << std::endl;

    // cdp = static_cast<C*>(bdp);  // error: cross-cast from B to C does not compile
    cdp = static_cast<C*>(static_cast<D*>(bdp));  // error: cross-cast from B to C via D

    F* fdp = dynamic_cast<F*>(bdp);  // cast from B to F, already clear at compile time that it is nonsense but not blamed

    return 0;
}
