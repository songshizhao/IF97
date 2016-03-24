// if97_wtp stub - Interfaces CoolProp IF97 function to Mathcad
//

// this code executes the user function if97_wtp(P), which is a wrapper for
// the CoolProp-IF97 function, speed_sound_Tp(T,P).
LRESULT  if97_WTP(
    LPCOMPLEXSCALAR c,  // pointer to the result
    LPCCOMPLEXSCALAR a,
    LPCCOMPLEXSCALAR b) // pointer to the parameter received from Mathcad
{  
    // first check to make sure "a" and "b" have no imaginary component
    if ( a->imag != 0.0 )
        return MAKELRESULT(MUST_BE_REAL,1);
    if ( b->imag != 0.0 )
        return MAKELRESULT(MUST_BE_REAL,2);

    //otherwise, all is well, evaluate function
    try {
        c->real = IF97::speed_sound_Tp(a->real,b->real);
    }
    catch (const std::out_of_range& e) { 
        if (e.what()[0] == 'T') 
            return MAKELRESULT(T_OUT_OF_RANGE,1);
        else // (e.what == "P")
            return MAKELRESULT(P_OUT_OF_RANGE,2);
    }
    catch (const std::logic_error&) {
        return MAKELRESULT(NO_SOLUTION_FOUND,1);
    }
    // normal return
    return 0;
}

FUNCTIONINFO    if97_wtp = 
{
    "if97_wtp",                      // name by which Mathcad will recognize the function
    "T,p",                           // if97_wtp will be called as if97_wtp(T,p)
    // description of if97_wtp(p)
    "Obtains the speed of sound [m/s] as a function of T [K] and p [Pa].",
    (LPCFUNCTION)if97_WTP,           // pointer to executable code
    COMPLEX_SCALAR,                  // the return type is a complex scalar
    2,                               // there are two input parameters
    { COMPLEX_SCALAR, COMPLEX_SCALAR }               //    that are both complex scalars
};