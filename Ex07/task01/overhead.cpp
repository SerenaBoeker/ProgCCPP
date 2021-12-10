#include "stopwatch.hpp"
#include <iostream>
#include <typeinfo>

class StaticBase {
    public:
        static int staticbase_var;
        static void myFunc() {
            StaticBase::staticbase_var++; 
            #ifdef VERBOSE
                std::cout << "Called " << "StaticBase" << "::"
                << __func__ << std::endl;
            #endif
        };
};

int StaticBase::staticbase_var = 0;

class PureBase {
    private:
        int purebase_var;
    public:
        PureBase(){};
        void myFunc() {
            purebase_var++; 
            #ifdef VERBOSE
                std::cout << "Called " << typeid(*this).name() << "::"
                << __func__ << std::endl;
            #endif
        };
};

class VirtBase {
    private:
        int virtbase_var;
    public:
        VirtBase(){};
        void nvFunct() {
            virtbase_var++; 
            #ifdef VERBOSE
                std::cout << "Called " << typeid(*this).name() << "::"
                << __func__ << std::endl;
            #endif
        };
        virtual void virtFunc() {
            virtbase_var++; 
            #ifdef VERBOSE
                std::cout << "Called " << typeid(*this).name() << "::"
                << __func__ << std::endl;
            #endif
        };
};

class VirtDer : public VirtBase {
    private:
        int virtder_var;
    public:
        void myFunc(){
            virtder_var++;
            #ifdef VERBOSE
                std::cout << "Called " << typeid(*this).name() << "::"
                << __func__ << std::endl;
            #endif
        };
        virtual void virtFunc() {
            virtder_var++;
            #ifdef VERBOSE
                std::cout << "Called " << typeid(*this).name() << "::"
                << __func__ << std::endl;
            #endif
        };
};

double duration;
StopWatch stopWatch;

/**
 * @brief Macro that measures the time in seconds the CPU needs to
 * perform the passed instructions for a given number of times.
 * 
 * @param description the description of the instructions
 * @param repetitions number of times the instructions are repeated
 * @param instructions2test the instructions to be executed
 */
#define MEASURETIME(description, repetitions, instructions2test) \
stopWatch.start(); \
for (int i = 0; i < repetitions; i++) { instructions2test; }; \
duration = stopWatch.stop(); \
std::cout << "My computer requires " << duration << " seconds to execute " \
<< description << " " << repetitions << " times" << std::endl;


int main() {
    PureBase pure;
    VirtBase vbase;
    VirtDer vder;
    PureBase *ppure = new PureBase();
    VirtBase *pvbase = new VirtBase();
    VirtDer *pvder = new VirtDer();
    VirtBase *pvbaseder = pvder;

    // calling a static member function
    StaticBase::myFunc();
    
    // each object calls its own member functions
    pure.myFunc();
    vbase.nvFunct();
    vbase.virtFunc();
    vder.myFunc();
    vder.virtFunc();
    vder.nvFunct();

    // the call of the member functions of the objects is done
    // over a pointer (need first to access object and then the function)
    ppure->myFunc();
    pvbase->nvFunct();
    pvder->myFunc();
    pvder->nvFunct();
    pvbaseder->nvFunct();
    
    // calling virtual function of the objects through indirect
    // access via vtable lookup over a pointer (access objects
    // over a pointer, then lookup vtable for the virtual function)
    pvbase->virtFunc();
    pvder->virtFunc();
    pvbaseder->virtFunc();
    
    // measures the time the cpu takes to run the functions 50.000.000 times
    #ifdef TASK02  
        MEASURETIME("StaticBase::myFunc()",  50000000, StaticBase::myFunc());
        MEASURETIME("pure.myFunc()",         50000000, pure.myFunc());
        MEASURETIME("vbase.nvFunct()",       50000000, vbase.nvFunct());
        MEASURETIME("vbase.virtFunc()",      50000000, vbase.virtFunc());
        MEASURETIME("vder.myFunc()",         50000000, vder.myFunc());
        MEASURETIME("vder.virtFunc()",       50000000, vder.virtFunc());
        MEASURETIME("vder.nvFunct()",        50000000, vder.nvFunct());
        MEASURETIME("ppure->myFunc()",       50000000, ppure->myFunc());
        MEASURETIME("pvbase->nvFunct()",     50000000, pvbase->nvFunct());
        MEASURETIME("pvbase->virtFunc()",    50000000, pvbase->virtFunc());
        MEASURETIME("pvder->myFunc()",       50000000, pvder->myFunc());
        MEASURETIME("pvder->nvFunct()",      50000000, pvder->nvFunct());
        MEASURETIME("pvder->virtFunc()",     50000000, pvder->virtFunc());
        MEASURETIME("pvbaseder->nvFunct()",  50000000, pvbaseder->nvFunct());
        MEASURETIME("pvbaseder->virtFunc()", 50000000, pvbaseder->virtFunc());
    #endif

    #ifdef TASK03
        std::cout << "pvbaseder is a " << typeid(pvbaseder).name() << std::endl;

        // static cast of the pvbaseder pointer to a VirtDer pointer, check if casting
        // succeeded before calling myFunc(); measure time needed to run myFunc(); 
        if(typeid(static_cast<VirtDer*> (pvbaseder)) == typeid(pvder)) {
            std::cout << "(static_cast<VirtDer*> (pvbaseder)) is a " << typeid((VirtDer*) pvbaseder).name() << std::endl;
            MEASURETIME("(static_cast<VirtDer*> (pvbaseder))->myFunc()", 50000000, (static_cast<VirtDer*> (pvbaseder))->myFunc());
        } else {
            std::cout << "typeid(static_cast<VirtDer*> (pvbaseder)) is not a VirtDer*" << std::endl;
        }

        // dynamic cast of the pvbaseder pointer to a VirtDer pointer, check if casting
        // succeeded before calling myFunc(); measure time needed to run myFunc(); 
        if(typeid(dynamic_cast<VirtDer*> (pvbaseder)) == typeid(pvder)) {
            std::cout << "(dynamic_cast<VirtDer*> (pvbaseder)) is a " << typeid(dynamic_cast<VirtDer*> (pvbaseder)).name() << std::endl;
            MEASURETIME("(dynamic_cast<VirtDer*> (pvbaseder))->myFunc()", 50000000, (dynamic_cast<VirtDer*> (pvbaseder) )->myFunc());
        } else {
            std::cout << "typeid(dynamic_cast<VirtDer*> (pvbaseder)) is not a VirtDer*" << std::endl;
        }
        
    #endif
}