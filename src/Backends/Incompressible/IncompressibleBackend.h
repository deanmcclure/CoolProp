
#ifndef INCOMPRESSIBLEBACKEND_H_
#define INCOMPRESSIBLEBACKEND_H_

#include "AbstractState.h"
#include "Exceptions.h"

#include <vector>

namespace CoolProp {

class IncompressibleBackend : public AbstractState  {
protected:
    int Ncomp;
    bool _mole_fractions_set;
    static bool _REFPROP_supported;
    std::vector<long double> mass_fractions;
public:
    IncompressibleBackend(){};
    virtual ~IncompressibleBackend(){};

    /// The instantiator
    /// @param fluid_name the string with the fluid name
    IncompressibleBackend(const std::string &fluid_name);
    /// The instantiator
	/// @param fluid_names The vector of strings of the fluid components, without file ending
	IncompressibleBackend(const std::vector<std::string> &component_names);

    // Incompressible backend uses mole fractions
    bool using_mole_fractions();

    /// Updating function for incompressible fluid
    /** 
    In this function we take a pair of thermodynamic states, those defined in the input_pairs
    enumeration and update all the internal variables that we can.

    @param input_pair Integer key from CoolProp::input_pairs to the two inputs that will be passed to the function
    @param value1 First input value
    @param value2 Second input value
    */
    void update(long input_pair, double value1, double value2);

    /// Set the mole fractions
    /** 
    @param mole_fractions The vector of mole fractions of the components
    */
    void set_mole_fractions(const std::vector<long double> &mole_fractions);
    
    /// Set the mass fractions
    /** 
    @param mass_fractions The vector of mass fractions of the components
    */
    void set_mass_fractions(const std::vector<long double> &mass_fractions);

    /// Check if the mole fractions have been set, etc.
    void check_status();

    /// Get the viscosity [Pa-s]
    long double calc_viscosity(void);
    /// Get the thermal conductivity [W/m/K] (based on the temperature and density in the state class)
    long double calc_conductivity(void);
};

} /* namespace CoolProp */
#endif /* INCOMPRESSIBLEBACKEND_H_ */
