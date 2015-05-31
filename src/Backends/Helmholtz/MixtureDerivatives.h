/**
 * This file contains derivatives needed in the mixture model.  The derivatives are quite nasty, and there 
 * are a lot of them, so they are put in this file for cleanness.  The MixtureDerivatives class is a friend class
 * of the HelmholtzEOSMixtureBackend, so it can access all the private members of the HelmholtzEOSMixtureBackend
 * class
*/

// ***************************************************************
// ***************************************************************
// *****************  MIXTURE DERIVATIVES  ***********************
// ***************************************************************
// ***************************************************************
    
#ifndef MIXTURE_DERIVATIVES_H
#define MIXTURE_DERIVATIVES_H

#include "HelmholtzEOSMixtureBackend.h"

namespace CoolProp{

/**
This class is a friend class of HelmholtzEOSMixtureBackend, therefore the 
static methods contained in it have access to the private and
protected variables in the HelmholtzEOSMixtureBackend instance.

In this way the derivative routines can be kept in their own separate file
and not pollute the HelmholtzEOSMixtureBackend namespace
*/
class MixtureDerivatives{
    public:
    
    /** \brief GERG 2004 Monograph equation 7.62
     * 
     * The derivative term
     * \f[
     * n\left(\frac{\partial p}{\partial V} \right)_{T,\bar n} = -\rho^2 RT(1+2\delta \alpha_{\delta}^r+\delta^2\alpha^r_{\delta\delta})
     * \f]
     * @param HEOS The HelmholtzEOSMixtureBackend to be used
     */
    static CoolPropDbl ndpdV__constT_n(HelmholtzEOSMixtureBackend &HEOS);
    
    /** \brief GERG 2004 Monograph equation 7.61
     * 
     * The derivative term
     * \f[
     * \left(\frac{\partial p}{\partial T} \right)_{V,\bar n} = \rho R(1+\delta \alpha_{\delta}^r-\delta \tau \alpha^r_{\delta\tau})
     * \f]
     * @param HEOS The HelmholtzEOSMixtureBackend to be used
     */
    static CoolPropDbl dpdT__constV_n(HelmholtzEOSMixtureBackend &HEOS);

    static CoolPropDbl dpdrho__constT_n(HelmholtzEOSMixtureBackend &HEOS);
    
    static CoolPropDbl dalphar_dxi(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag);
    static CoolPropDbl d2alphar_dxi_dTau(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag);
    static CoolPropDbl d2alphar_dxi_dDelta(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag);
    static CoolPropDbl d2alphardxidxj(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, std::size_t j, x_N_dependency_flag xN_flag);

    static CoolPropDbl d3alphar_dxi_dDelta2(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag); 
    static CoolPropDbl d3alphar_dxi_dDelta_dTau(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag); 
    static CoolPropDbl d3alphar_dxi_dTau2(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag);
    static CoolPropDbl d3alphar_dxi_dxj_dDelta(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, std::size_t j, x_N_dependency_flag xN_flag);
    static CoolPropDbl d3alphar_dxi_dxj_dTau(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, std::size_t j, x_N_dependency_flag xN_flag);
    static CoolPropDbl d3alphardxidxjdxk(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, std::size_t j, std::size_t k, x_N_dependency_flag xN_flag);

    

    /** \brief GERG 2004 Monograph equation 7.63
     * 
     * The derivative term
     * \f[
     * n\left(\frac{\partial p}{\partial n_i} \right)_{T,V,n_j} = \rho RT\left[1+\delta\alpha_{\delta}^r\left[2- \frac{1}{\rho_r}\cdot n\left( \frac{\partial \rho_r}{\partial n_i}\right)_{n_j}\right] +\delta\cdot n\left(\frac{\partial\alpha_{\delta}^r}{\partial n_i}\right)_{T,V,n_j}\right]
     * \f]
     * @param HEOS The HelmholtzEOSMixtureBackend to be used
     * @param i The index of interest
     * @param xN_flag A flag specifying whether the all mole fractions are independent or only the first N-1
     */
    static CoolPropDbl ndpdni__constT_V_nj(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag);

    /** \brief GERG 2004 monograph Eqn. 7.32
     * 
     * The partial molar volume
     * \f[
     * \hat v_i = \left( \frac{\partial V}{\partial n_i}\right)_{T,p,n_j} = \frac{-\left(\dfrac{\partial p}{\partial n_i}\right)_{T,V,n_j}}{\left(\dfrac{\partial p}{\partial V}\right)_{T,\bar n}}
     * \f]
     * @param HEOS The HelmholtzEOSMixtureBackend to be used
     * @param i The index of interest
     * @param xN_flag A flag specifying whether the all mole fractions are independent or only the first N-1
     */
    static CoolPropDbl partial_molar_volume(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag);

    /** \brief Fugacity of the i-th component
     * 
     * Given by the equation
     * \f[
     * f_i(\delta, \tau, \bar x) = x_i\rho R T \exp\left(\frac{\partial n\alpha^r}{\partial n_i}\right)_{T,V,n_{j \neq i}}
     * \f]
     */
    static CoolPropDbl fugacity_i(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag);
      
    /** \brief Natural logarithm of the fugacity coefficient
     * 
     * @param HEOS The HelmholtzEOSMixtureBackend to be used
     * @param i The index of interest
     * @param xN_flag A flag specifying whether the all mole fractions are independent or only the first N-1
     */
    static CoolPropDbl ln_fugacity_coefficient(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag);

    /** \brief Derivative of the natural logarithm of the fugacity with respect to T
     * 
     * From Witzke, Eqn. 3.14
     * \f[
     *  \left(\frac{\partial \ln(f_i)}{\partial T} \right)_{\rho,x} = -\frac{1}{T}\left(1-\tau\alpha^r_{\tau}-\tau n\left(\frac{\partial\left(\frac{\partial \alpha^r}{\partial n_i}\right)_{T,V,n_j}}{\partial \tau}\right)_{\delta,\bar x}    \right)
     * \f]
     * @param HEOS The HelmholtzEOSMixtureBackend to be used
     * @param i The index of interest
     * @param xN_flag A flag specifying whether the all mole fractions are independent or only the first N-1
     */
    static CoolPropDbl dln_fugacity_i_dT__constrho_n(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag);

    /**    \brief Derivative of the natural logarithm of the fugacity with respect to T
     * 
     * From Witzke, Eqn. 3.15
     * \f[
     *  \left(\frac{\partial \ln(f_i)}{\partial \rho} \right)_{T, x} = \frac{1}{\rho}\left(1+\delta\alpha^r_{\delta}+\delta n\left(\frac{\partial\left(\frac{\partial \alpha^r}{\partial n_i}\right)_{T,V,n_j}}{\partial \delta}\right)_{\tau,\bar x}    \right)
     * \f]
     * @param HEOS The HelmholtzEOSMixtureBackend to be used
     * @param i The index of interest
     * @param xN_flag A flag specifying whether the all mole fractions are independent or only the first N-1
     */
    static CoolPropDbl dln_fugacity_i_drho__constT_n(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag);

    /** \brief GERG 2004 Monograph Eqn. 7.29
     * 
     * The derivative term
     * 
     * \f[
     * \left(\frac{\partial \ln \phi_i}{\partial T} \right)_{p,\bar n} = \left(\frac{\partial^2n\alpha^r}{\partial T\partial n_i} \right)_{V,n_j} + \frac{1}{T}-\frac{\hat v}{RT}\left(\frac{\partial p}{\partial T}\right)_{V,\bar n}
     * \f]
     * @param HEOS The HelmholtzEOSMixtureBackend to be used
     * @param i The index of interest
     * @param xN_flag A flag specifying whether the all mole fractions are independent or only the first N-1
     */
    static CoolPropDbl dln_fugacity_coefficient_dT__constp_n(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag);

    static CoolPropDbl dln_fugacity_i_dT__constp_n(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag);
    static CoolPropDbl dln_fugacity_i_dp__constT_n(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag);
    static CoolPropDbl dln_fugacity_dxj__constT_p_xi(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, std::size_t j, x_N_dependency_flag xN_flag);
    static CoolPropDbl dln_fugacity_i_dtau__constdelta_x(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag);
    static CoolPropDbl dln_fugacity_i_ddelta__consttau_x(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag);
    static CoolPropDbl dln_fugacity_dxj__constT_rho_xi(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, std::size_t j, x_N_dependency_flag xN_flag);

    static CoolPropDbl ndln_fugacity_i_dnj__constT_V_xi(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, std::size_t j, x_N_dependency_flag xN_flag);
    static CoolPropDbl d_ndln_fugacity_i_dnj_dtau__constdelta_x(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, std::size_t j, x_N_dependency_flag xN_flag);
    static CoolPropDbl d_ndln_fugacity_i_dnj_ddelta__consttau_x(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, std::size_t j, x_N_dependency_flag xN_flag);
    static CoolPropDbl d_ndln_fugacity_i_dnj_ddxk__consttau_delta(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, std::size_t j, std::size_t k, x_N_dependency_flag xN_flag);

    static CoolPropDbl nd_ndln_fugacity_i_dnj_dnk__constT_V_xi(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, std::size_t j, std::size_t k, x_N_dependency_flag xN_flag);
    
    static CoolPropDbl nAij(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, std::size_t j, x_N_dependency_flag xN_flag){
        CoolPropDbl RT = HEOS.gas_constant()*HEOS.T();
        return 1/RT*ndln_fugacity_i_dnj__constT_V_xi(HEOS, i, j, xN_flag);
    }
    static CoolPropDbl n2Aijk(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, std::size_t j, std::size_t k, x_N_dependency_flag xN_flag){
        CoolPropDbl RT = HEOS.gas_constant()*HEOS.T();
        return 1/RT*nd_ndln_fugacity_i_dnj_dnk__constT_V_xi(HEOS, i, j, k, xN_flag);
    }
    static CoolPropDbl L1_star(HelmholtzEOSMixtureBackend &HEOS, x_N_dependency_flag xN_flag){
        Eigen::Matrix2d L1;
        CoolPropDbl RT = HEOS.gas_constant()*HEOS.T();
        L1(0, 0) = nAij(HEOS, 0, 0, xN_flag);
        L1(1, 0) = nAij(HEOS, 1, 0, xN_flag);
        L1(0, 1) = L1(1,0);
        L1(1, 1) = nAij(HEOS, 1, 1, xN_flag);
        return L1.determinant();
    }
    static CoolPropDbl M1_star(HelmholtzEOSMixtureBackend &HEOS, x_N_dependency_flag xN_flag){
        Eigen::Matrix2d M1;
        CoolPropDbl RT = HEOS.gas_constant()*HEOS.T();
        M1(0, 0) = nAij(HEOS, 0, 0, xN_flag);
        M1(0, 1) = nAij(HEOS, 0, 1, xN_flag);
        double dL1_dn0 = nAij(HEOS, 0, 0, xN_flag)*n2Aijk(HEOS, 0, 1, 1, xN_flag) + nAij(HEOS, 1, 1, xN_flag)*n2Aijk(HEOS, 0, 0, 0, xN_flag) - 2*nAij(HEOS, 0, 1, xN_flag)*n2Aijk(HEOS, 0, 0, 1, xN_flag);
        double dL1_dn1 = nAij(HEOS, 0, 0, xN_flag)*n2Aijk(HEOS, 1, 1, 1, xN_flag) + nAij(HEOS, 1, 1, xN_flag)*n2Aijk(HEOS, 0, 0, 1, xN_flag) - 2*nAij(HEOS, 0, 1, xN_flag)*n2Aijk(HEOS, 0, 1, 1, xN_flag);
        M1(1, 0) = dL1_dn0;
        M1(1, 1) = dL1_dn1;
        return M1.determinant();
    }
    
    /** \brief Table B4, Kunz, JCED, 2012 for the original term and the subsequent substitutions
     * 
     * The derivative term
     * \f[
     * n\left(\frac{\partial \alpha^r}{\partial n_i} \right)_{T,V,n_j}
     * \f]
     * which is equal to
     * \f{eqnarray*}{
     * n\left(\frac{\partial \alpha^r}{\partial n_i} \right)_{T,V,n_j} &=& \delta \alpha^r_{\delta}\left[ 1-\frac{1}{\rho_r}\left[\left(\frac{\partial \rho_r}{\partial x_i}\right)_{x_j} - \sum_{k=1}^N x_k\left(\frac{\partial \rho_r}{\partial x_k}\right)_{x_j}  \right]\right]\\
     * && +\tau \alpha^r_{\tau}\frac{1}{T_r}\left[\left(\frac{\partial T_r}{\partial x_i}\right)_{x_j} - \sum_{k=1}^N x_k\left(\frac{\partial T_r}{\partial x_k}\right)_{x_j}  \right]\\
     * && +\alpha^r_{x_i}-\sum_{k=1}^{N}x_k\alpha^r_{x_k}
     * \f}
     * @param HEOS The HelmholtzEOSMixtureBackend to be used
     * @param i The index of interest
     * @param xN_flag A flag specifying whether the all mole fractions are independent or only the first N-1
     */
    static CoolPropDbl ndalphar_dni__constT_V_nj(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag);

    /// GERG Equation 7.42
    static CoolPropDbl dnalphar_dni__constT_V_nj(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag);

    /** \brief GERG 2004 Monograph Eqn. 7.30
     * 
     * The derivative term
     * \f[
     * \left(\frac{\partial \ln \phi_i}{\partial p} \right)_{T,\bar n} = \frac{\hat v_i}{RT}-\frac{1}{p}
     * \f]
     * @param HEOS The HelmholtzEOSMixtureBackend to be used
     * @param i The index of interest
     * @param xN_flag A flag specifying whether the all mole fractions are independent or only the first N-1
    */
    static CoolPropDbl dln_fugacity_coefficient_dp__constT_n(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag);

    /** \brief GERG 2004 Monograph Equation 7.31
     * 
     * The derivative term
     * \f[
     * n\left(\frac{\partial \ln \phi_i}{\partial n_j}\right)_{T,p} = n\left(\frac{\partial^2n\alpha^r}{\partial n_j \partial n_i} \right)_{T,V}+1+\frac{n}{RT}\frac{\left(\frac{\partial p}{\partial n_j}\right)_{T,V,n_i}\left(\frac{\partial p}{\partial n_i}\right)_{T,V,n_j}}{\left(\frac{\partial p}{\partial V}\right)_{T,\bar n}}
     * \f]
     * which is also equal to
     * \f[
     * n\left(\frac{\partial \ln \phi_i}{\partial n_j}\right)_{T,p} = n\left(\frac{\partial^2n\alpha^r}{\partial n_j \partial n_i} \right)_{T,V}+1-\frac{\hat v_i}{RT}\left[n\left(\frac{\partial p}{\partial n_j}\right)_{T,V,n_i}\right]
     * \f]
     * @param HEOS The HelmholtzEOSMixtureBackend to be used
     * @param i The index of interest
     * @param j The second index of interest
     * @param xN_flag A flag specifying whether the all mole fractions are independent or only the first N-1
    */
    static CoolPropDbl ndln_fugacity_coefficient_dnj__constT_p(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, std::size_t j, x_N_dependency_flag xN_flag);

    /** \brief Gernert Equation 3.115
     * 
     * The derivative term
     * \f[
     * \left(\frac{\partial \ln \phi_i}{\partial x_j}\right)_{T,p,x_{k\neq j}} = \left(\frac{\partial^2n\alpha^r}{\partial x_j \partial n_i} \right)_{T,V}+\frac{1}{RT}\frac{\left(\frac{\partial p}{\partial n_i}\right)_{T,V,n_{k\neq i}}\left(\frac{\partial p}{\partial x_j}\right)_{T,V,x_{k\neq j}}}{\left(\frac{\partial p}{\partial V}\right)_{T,\bar n}}
     * \f]
     * @param HEOS The HelmholtzEOSMixtureBackend to be used
     * @param i The first index of interest
     * @param j The second index of interest
     * @param xN_flag A flag specifying whether the all mole fractions are independent or only the first N-1
     * 
    */
    static CoolPropDbl dln_fugacity_coefficient_dxj__constT_p_xi(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, std::size_t j, x_N_dependency_flag xN_flag);

    /** \brief Gernert Equation 3.130
     * 
     * The derivative term
     * \f[
     * \left(\frac{\partial p}{\partial x_j} \right)_{T,V,x_{k\neq j}} = \rho RT\left(-\frac{1}{\rho_r}\left(\frac{\partial \rho_r}{\partial x_j}\right)_{x_{k\neq j}} \delta\alpha_{\delta}^r + \delta\left(\frac{\partial}{\partial x_j}\left(\left( \frac{\partial \alpha^r}{\partial \delta}\right)_{\tau,\bar x}\right)\right)_{T,V,x_{k\neq j}}\right)
     * \f]
     * @param HEOS The HelmholtzEOSMixtureBackend to be used
     * @param j The index of interest
     * @param xN_flag A flag specifying whether the all mole fractions are independent or only the first N-1
     */
    static CoolPropDbl dpdxj__constT_V_xi(HelmholtzEOSMixtureBackend &HEOS, std::size_t j, x_N_dependency_flag xN_flag);

    /** \brief Gernert Equation 3.117
     * 
     * The derivative term
     * \f[
     * \left(\frac{\partial^2n\alpha^r}{\partial x_j\partial n_i} \right)_{T,V} = \left(\frac{\partial}{\partial x_j}\left(n\left(\frac{\partial \alpha^r}{\partial n_i}\right)_{T,V,n_{j\neq i}}\right)\right)_{T,V,x_{k\neq j}} +\left(\frac{\partial \alpha^r}{\partial x_j}\right)_{T,V,x_{k\neq j}}
     * \f]
     * @param HEOS The HelmholtzEOSMixtureBackend to be used
     * @param j The first index of interest
     * @param i The second index of interest
     * @param xN_flag A flag specifying whether the all mole fractions are independent or only the first N-1
     */
    static CoolPropDbl d2nalphar_dxj_dni__constT_V(HelmholtzEOSMixtureBackend &HEOS, std::size_t j, std::size_t i, x_N_dependency_flag xN_flag){ return MixtureDerivatives::d_ndalphardni_dxj__constT_V_xi(HEOS, i, j, xN_flag) + MixtureDerivatives::dalphar_dxj__constT_V_xi(HEOS, j, xN_flag);};

    /// Gernert Equation 3.119
    /// Catch test provided
    static CoolPropDbl dalphar_dxj__constT_V_xi(HelmholtzEOSMixtureBackend &HEOS, std::size_t j, x_N_dependency_flag xN_flag);

    /// Gernert Equation 3.118
    /// Catch test provided
    static CoolPropDbl d_ndalphardni_dxj__constT_V_xi(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, std::size_t j, x_N_dependency_flag xN_flag);

    /// Gernert Equation 3.134
    /// Catch test provided
    static CoolPropDbl d_dalpharddelta_dxj__constT_V_xi(HelmholtzEOSMixtureBackend &HEOS, std::size_t j, x_N_dependency_flag xN_flag);

    /// Gernert Equation 3.121
    /// Catch test provided
    static CoolPropDbl ddelta_dxj__constT_V_xi(HelmholtzEOSMixtureBackend &HEOS, std::size_t j, x_N_dependency_flag xN_flag);

    /// Gernert Equation 3.122
    /// Catch test provided
    static CoolPropDbl dtau_dxj__constT_V_xi(HelmholtzEOSMixtureBackend &HEOS, std::size_t j, x_N_dependency_flag xN_flag);

    /** \brief GERG 2004 Monograph, equations 7.44 and 7.51
     * 
     * The derivative term
     * \f[
     * \left(\frac{\partial^2n\alpha^r}{\partial T\partial n_i} \right)_{V,n_j} = \left( \frac{\partial}{\partial T}\left(\frac{\partial n \alpha^r}{\partial n_i}\right)_{T,V,n_j} \right)_{V,\bar n}
     * \f]
     * \f[
     * \left(\frac{\partial^2n\alpha^r}{\partial T\partial n_i} \right)_{V,n_j} = -\frac{\tau}{T}\left[\alpha_{\tau}^r +\left( \frac{\partial}{\partial \tau}\left(n\left(\frac{\partial \alpha^r}{\partial n_i}\right)_{T,V,n_j}\right)\right)_{\delta,\bar x}\right]
     * \f]
     * @param HEOS The HelmholtzEOSMixtureBackend to be used
     * @param i The second index of interest
     * @param xN_flag A flag specifying whether the all mole fractions are independent or only the first N-1
    */
    static CoolPropDbl d2nalphar_dni_dT(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag);

    /** \brief GERG 2004 Monograph Equation 7.51 and Table B4, Kunz, JCED, 2012
     * 
     * The derivative term
     * \f{eqnarray*}{
     * \frac{\partial }{\partial \tau} \left( n\left(\frac{\partial \alpha^r}{\partial n_i} \right)_{T,V,n_j} \right) &=& \delta \alpha^r_{\delta\tau}\left[ 1-\frac{1}{\rho_r}\left[\left(\frac{\partial \rho_r}{\partial x_i}\right)_{x_j} - \sum_{k=1}^N x_k\left(\frac{\partial \rho_r}{\partial x_k}\right)_{x_j}  \right]\right]\\
     * && +(\tau \alpha^r_{\tau\tau}+\alpha^r_{\tau})\frac{1}{T_r}\left[\left(\frac{\partial T_r}{\partial x_i}\right)_{x_j} - \sum_{k=1}^N x_k\left(\frac{\partial T_r}{\partial x_k}\right)_{x_j}  \right]\\
     * && +\alpha^r_{x_i\tau}-\sum_{k=1}^{N}x_k\alpha^r_{x_k\tau}
     * \f}
     * @param HEOS The HelmholtzEOSMixtureBackend to be used
     * @param i The index of interest
     * @param xN_flag A flag specifying whether the all mole fractions are independent or only the first N-1
     */
    static CoolPropDbl d_ndalphardni_dTau(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag);

    /** \brief \f$\tau\f$ derivartive of GERG 2004 Monograph Equation 7.51
     *
     * The derivative term
     * \f[
     * \dfrac{\partial^2 }{\partial \tau^2} \left( n\left(\dfrac{\partial \alpha^r}{\partial n_i} \right)_{T,V,n_j} \right) = \delta \alpha^r_{\delta\tau\tau}\Psi_{\rho}+ (2\alpha^r_{\tau\tau}+\tau\alpha^r_{\tau\tau\tau})\Psi_T+\alpha^r_{x_i\tau\tau}-\sum_{k=1}^{N}x_k\alpha^r_{x_k\tau\tau}
     * \f]
     * @param HEOS The HelmholtzEOSMixtureBackend to be used
     * @param i The index of interest
     * @param xN_flag A flag specifying whether the all mole fractions are independent or only the first N-1
     */
    static CoolPropDbl d2_ndalphardni_dTau2(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag);

    /** \brief GERG 2004 Monograph Equation 7.50 and Table B4, Kunz, JCED, 2012
     * 
     * The derivative term
     * \f{eqnarray*}{
     * \left(\frac{\partial }{\partial \delta} \left( n\left(\frac{\partial \alpha^r}{\partial n_i} \right)_{T,V,n_j} \right)\right)_{\tau,\bar x} &=& (\alpha_{\delta}^r+\delta\alpha_{\delta\delta}^r)\left[1-\frac{1}{\rho_r}\cdot n\left(\frac{\partial \rho_r}{\partial n_i}\right)_{n_j} \right] \\
     * &+&\tau\alpha^r_{\delta\tau}\frac{1}{T_r}\cdot n\left(\frac{\partial T_r}{\partial n_i}\right)_{n_j}\\
     * &+&\alpha^r_{\delta x_i}-\sum_{k=1}^{N}x_k\alpha^r_{\delta x_k}
     * \f}
     * @param HEOS The HelmholtzEOSMixtureBackend to be used
     * @param i The index of interest
     * @param xN_flag A flag specifying whether the all mole fractions are independent or only the first N-1
     */
    static CoolPropDbl d_ndalphardni_dDelta(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag);

    /** \brief \f$\delta\f$ derivative of GERG 2004 Monograph Equation 7.50
    *
    * The derivative term
    * \f[
    * \begin{array}{ccl} 
    * \left(\dfrac{\partial^2 }{\partial \delta^2} \left( n\left(\dfrac{\partial \alpha^r}{\partial n_i} \right)_{T,V,n_j} \right)\right)_{\tau,\bar x} &=& (2\alpha_{\delta\delta}^r+\delta\alpha_{\delta\delta\delta}^r)\Psi_{\rho} +\tau\alpha^r_{\delta\delta\tau}\Psi_T+\alpha^r_{\delta\delta x_i}-\sum_{k=1}^{N}x_k\alpha^r_{\delta\delta x_k} 
    * \end{array}
    * \f]
    * @param HEOS The HelmholtzEOSMixtureBackend to be used
    * @param i The index of interest
    * @param xN_flag A flag specifying whether the all mole fractions are independent or only the first N-1
    */
    static CoolPropDbl d2_ndalphardni_dDelta2(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag);

    /** \brief \f$\tau\f$ derivative of GERG 2004 Monograph Equation 7.50
    *
    * The derivative term
    * \f[
    * \begin{array}{ccl}
    * \left(\dfrac{\partial^2 }{\partial \delta\partial \tau} \left( n\left(\dfrac{\partial \alpha^r}{\partial n_i} \right)_{T,V,n_j} \right)\right)_{\bar x} &=& (\alpha_{\delta\tau}^r+\delta\alpha_{\delta\delta\tau}^r)\Psi_{\rho} +(\tau\alpha^r_{\delta\tau\tau} + \alpha^r_{\delta\tau})\Psi_T 
+\alpha^r_{\delta\tau x_i}-\sum_{k=1}^{N}x_k\alpha^r_{\delta\tau x_k} 
    * \end{array}
    * \f]
    * @param HEOS The HelmholtzEOSMixtureBackend to be used
    * @param i The index of interest
    * @param xN_flag A flag specifying whether the all mole fractions are independent or only the first N-1
    */
    static CoolPropDbl d2_ndalphardni_dDelta_dTau(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag);

    /** \brief \f$x_j\f$ derivative of GERG 2004 Monograph Equation 7.50
    *
    * The derivative term
    * \f[
    * \begin{array}{ccl}
    * \dfrac{\partial}{\partial x_j}\left(\dfrac{\partial }{\partial \delta} \left( n\left(\dfrac{\partial \alpha^r}{\partial n_i} \right)_{T,V,n_j} \right)_{\tau,\bar x}\right)_{\tau, \delta, x_i} &=& (\alpha_{\delta}^r+\delta\alpha_{\delta\delta}^r)\dfrac{\partial\Psi_{\rho}}{\partial x_j} + (\alpha_{\delta x_j}^r+\delta\alpha_{\delta\delta x_j}^r)\Psi_{\rho}\\
    * &+&\tau\alpha^r_{\delta\tau}\dfrac{\partial\Psi_{T}}{\partial x_j} + \tau\alpha^r_{\delta\tau x_j}\Psi_T\\
    * &+&\alpha^r_{\delta x_i x_j}-\sum_{k=1}^{N}\left[x_k\alpha^r_{\delta x_k x_j} + \dfrac{d x_k}{d x_j}\alpha^r_{\delta x_k}\right]
    * \end{array}
    * \f]
    * @param HEOS The HelmholtzEOSMixtureBackend to be used
    * @param i The index of interest
    * @param xN_flag A flag specifying whether the all mole fractions are independent or only the first N-1
    */
    static CoolPropDbl d2_ndalphardni_dxj_dDelta__consttau_xi(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, std::size_t j, x_N_dependency_flag xN_flag);

    /** \brief \f$x_j\f$ derivative of GERG 2004 Monograph Equation 7.51
    *
    * The derivative term
    * \f[
    * \begin{array}{ccl}
    * \dfrac{\partial}{\partial x_j}\left(\dfrac{\partial }{\partial \tau} \left( n\left(\dfrac{\partial \alpha^r}{\partial n_i} \right)_{T,V,n_j} \right)\right)_{\tau,\delta,x_i} &=& \delta \alpha^r_{\delta\tau}\dfrac{\partial \Psi_{\rho}}{\partial x_j} + \delta \alpha^r_{\delta\tau x_j}\Psi_{\rho}\\
    * &+& (\tau \alpha^r_{\tau\tau}+\alpha^r_{\tau})\dfrac{\partial \Psi_T}{\partial x_j}+ \left(\tau \alpha^r_{\tau\tau x_j} +\alpha^r_{\tau x_j}\right)\Psi_T\\
    * &+&\alpha^r_{\tau x_i x_j}-\sum_{k=1}^{N}\left[x_k\alpha^r_{\tau x_k x_j} + \dfrac{d x_k}{d x_j}\alpha^r_{\tau x_k}\right]
    * \end{array}
    * \f]
    * @param HEOS The HelmholtzEOSMixtureBackend to be used
    * @param i The index of interest
    * @param xN_flag A flag specifying whether the all mole fractions are independent or only the first N-1
    */
    static CoolPropDbl d2_ndalphardni_dxj_dTau__constdelta_xi(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, std::size_t j, x_N_dependency_flag xN_flag);

    /** \brief GERG 2004 Monograph equation 7.41
     * 
     * The derivative term
     * \f[
     * n\left(\frac{\partial^2n\alpha^r}{\partial n_i \partial n_j} \right)_{T,V} = n\left( \frac{\partial}{\partial n_j}\left(\frac{\partial n\alpha^r}{\partial n_i}\right)_{T,V,n_j}\right)_{T,V,n_i}
     * \f]
     * and
     * GERG 2004 Monograph equation 7.46:
     * \f[
     * n\left( \frac{\partial}{\partial n_j}\left(\frac{\partial n\alpha^r}{\partial n_i}\right)_{T,V,n_j}\right)_{T,V,n_i} = n\left( \frac{\partial \alpha^r}{\partial n_j}\right)_{T,V,n_i} + n\left( \frac{\partial}{\partial n_j}\left(n\left(\frac{\partial \alpha^r}{\partial n_i}\right)_{T,V,n_j} \right) \right)_{T,V,n_i}
     * \f]
     * GERG 2004 Monograph equation 7.47:
     * \f{eqnarray*}{
     * n\left( \frac{\partial}{\partial n_j}\left(n\left(\frac{\partial \alpha^r}{\partial n_i}\right)_{T,V,n_j} \right) \right)_{T,V,n_i} &=& \left( \frac{\partial}{\partial \delta}\left(n\left(\frac{\partial\alpha^r}{\partial n_i}\right)_{T,V,n_j}\right)\right)_{\tau,\bar x}\cdot n\left(\frac{\partial\delta}{\partial n_j}\right)_{T,V,n_i}\\
     * &+& \left( \frac{\partial}{\partial \tau}\left(n\left(\frac{\partial\alpha^r}{\partial n_i}\right)_{T,V,n_j}\right)\right)_{\tau,\bar x}\cdot n\left(\frac{\partial\tau}{\partial n_j}\right)_{T,V,n_i}\\
     * &+& \left( \frac{\partial}{\partial x_j}\left(n\left(\frac{\partial\alpha^r}{\partial n_i}\right)_{T,V,n_j}\right)\right)_{\delta,\tau,x_i}-\sum_{k=1}^{N}x_k \left( \frac{\partial}{\partial x_k}\left(n\left(\frac{\partial\alpha^r}{\partial n_i}\right)_{T,V,n_j}\right)\right)_{\delta,\tau,x_i}\\
     * \f}
     * @param HEOS The HelmholtzEOSMixtureBackend to be used
     * @param i The index of interest
     * @param j The second index of interest
     * @param xN_flag A flag specifying whether the all mole fractions are independent or only the first N-1
     */
    static CoolPropDbl nd2nalphardnidnj__constT_V(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, std::size_t j, x_N_dependency_flag xN_flag);

    /* \brief GERG 2004 Eqn. 7.47
     * \f{eqnarray*}{
     * n\left( \frac{\partial}{\partial n_j}\left(n\left(\frac{\partial \alpha^r}{\partial n_i}\right)_{T,V,n_j} \right) \right)_{T,V,n_i} &=& \left( \frac{\partial}{\partial \delta}\left(n\left(\frac{\partial\alpha^r}{\partial n_i}\right)_{T,V,n_j}\right)\right)_{\tau,\bar x}\cdot n\left(\frac{\partial\delta}{\partial n_j}\right)_{T,V,n_i}\\
     * &+& \left( \frac{\partial}{\partial \tau}\left(n\left(\frac{\partial\alpha^r}{\partial n_i}\right)_{T,V,n_j}\right)\right)_{\tau,\bar x}\cdot n\left(\frac{\partial\tau}{\partial n_j}\right)_{T,V,n_i}\\
     * &+& \left( \frac{\partial}{\partial x_j}\left(n\left(\frac{\partial\alpha^r}{\partial n_i}\right)_{T,V,n_j}\right)\right)_{\delta,\tau,x_i}-\sum_{k=1}^{N}x_k \left( \frac{\partial}{\partial x_k}\left(n\left(\frac{\partial\alpha^r}{\partial n_i}\right)_{T,V,n_j}\right)\right)_{\delta,\tau,x_i}\\
     * \f}
     * @param HEOS The HelmholtzEOSMixtureBackend to be used
     * @param i The index of interest
     * @param j The second index of interest
     * @param xN_flag A flag specifying whether the all mole fractions are independent or only the first N-1
     */
    static CoolPropDbl nd_ndalphardni_dnj__constT_V(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, std::size_t j, x_N_dependency_flag xN_flag);

    /* \brief \f$\tau\f$ derivative of GERG 2004 7.47
     *  
     */
    static CoolPropDbl d_nd_ndalphardni_dnj_dTau__constdelta_x(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, std::size_t j, x_N_dependency_flag xN_flag);

    /* \brief \f$\delta\f$ derivative of GERG 2004 7.47
     *
     */
    static CoolPropDbl d_nd_ndalphardni_dnj_dDelta__consttau_x(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, std::size_t j, x_N_dependency_flag xN_flag);

    /* \brief \f$x_k\f$ derivative of GERG 2004 7.47
    *
    */
    static CoolPropDbl d_nd_ndalphardni_dnj_dxk__consttau_delta(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, std::size_t j, std::size_t k, x_N_dependency_flag xN_flag);

    /** \brief GERG 2004 Monograph equation 7.48
     * 
     * The derivative term
     * \f[
     * n\left(\frac{\partial \delta}{\partial n_i} \right)_{T,V,n_j} = \delta - \frac{\delta}{\rho_r}\cdot n\left(\frac{\partial \rho_r}{\partial n_i} \right)_{n_j}
     * \f]
     * @param HEOS The HelmholtzEOSMixtureBackend to be used
     * @param i The index of interest
     * @param xN_flag A flag specifying whether the all mole fractions are independent or only the first N-1
     */ 
    static CoolPropDbl nddeltadni__constT_V_nj(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag);

    static CoolPropDbl d_nddeltadni_dDelta(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag);

    static CoolPropDbl d_nddeltadni_dxj__constdelta_tau(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, std::size_t j, x_N_dependency_flag xN_flag);

    /** \brief GERG 2004 Monograph equation 7.49
     * 
     * The derivative term
     * \f[
     * n\left(\frac{\partial \tau}{\partial n_i} \right)_{T,V,n_j} = \frac{\tau}{T_r}\cdot n\left(\frac{\partial T_r}{\partial n_i} \right)_{n_j}
     * \f]
     * @param HEOS The HelmholtzEOSMixtureBackend to be used
     * @param i The index of interest
     * @param xN_flag A flag specifying whether the all mole fractions are independent or only the first N-1
     */
    static CoolPropDbl ndtaudni__constT_V_nj(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag);

    static CoolPropDbl d_ndtaudni_dTau(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, x_N_dependency_flag xN_flag);
    
    static CoolPropDbl d_ndtaudni_dxj__constdelta_tau(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, std::size_t j, x_N_dependency_flag xN_flag);

    /** \brief GERG 2004 Monograph equation 7.52
     * 
     * The derivative term
     * \f{eqnarray*}{
     * \left( \frac{\partial}{\partial x_j}\left(n\left(\frac{\partial\alpha^r}{\partial n_i}\right)_{T,V,n_j}\right)\right)_{\delta,\tau,x_i} &=& \delta\alpha_{\delta x_j}^{r}\left[ 1-\frac{1}{\rho_r}\cdot n\left(\frac{\partial \rho_r}{\partial n_i}\right)_{n_j}\right] \\
     * &-& \delta\alpha_{\delta}^{r}\frac{1}{\rho_r}\left[ \left(\frac{\partial}{\partial x_j}\left(n\left(\frac{\partial \rho_r}{\partial n_i}\right)_{n_j}\right)\right)_{x_i}-\frac{1}{\rho_r}\left(\frac{\partial \rho_r}{\partial x_j}\right)_{x_i}\cdot n\left(\frac{\partial \rho_r}{\partial n_i}\right)_{n_j}\right] \\
     * &+& \tau\alpha_{\tau x_j}^r\frac{1}{T_r}\cdot n\left(\frac{\partial T_r}{\partial n_i}\right)_{n_j}\\
     * &+& \tau\alpha_{\tau}^{r}\frac{1}{T_r}\left[ \left(\frac{\partial}{\partial x_j}\left(n\left(\frac{\partial T_r}{\partial n_i}\right)_{n_j}\right)\right)_{x_i}-\frac{1}{T_r}\left(\frac{\partial T_r}{\partial x_j}\right)_{x_i}\cdot n\left(\frac{\partial T_r}{\partial n_i}\right)_{n_j}\right] \\
     * &+& \alpha_{x_ix_j}^r-\alpha_{x_j}^r-\sum_{m=1}^Nx_m\alpha_{x_jx_m}^r
     * \f}
     * @param HEOS The HelmholtzEOSMixtureBackend to be used
     * @param i The index of interest
     * @param j The second index of interest
     * @param xN_flag A flag specifying whether the all mole fractions are independent or only the first N-1
     */
    static CoolPropDbl d_ndalphardni_dxj__constdelta_tau_xi(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, std::size_t j, x_N_dependency_flag xN_flag);

    /* \brief \f$x_k\f$ derivative of GERG 2004 7.52
    *
    */
    static CoolPropDbl d2_ndalphardni_dxj_dxk__constdelta_tau_xi(HelmholtzEOSMixtureBackend &HEOS, std::size_t i, std::size_t j, std::size_t k, x_N_dependency_flag xN_flag);

}; /* class MixtureDerivatives */

} /* namepsace CoolProp*/
#endif