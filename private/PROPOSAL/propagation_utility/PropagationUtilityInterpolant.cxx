
#include <cmath>
#include <cassert>
#include <functional>

#include "PROPOSAL/math/Interpolant.h"
#include "PROPOSAL/propagation_utility/PropagationUtilityInterpolant.h"

#include "PROPOSAL/Constants.h"
#include "PROPOSAL/Logging.h"
#include "PROPOSAL/methods.h"

#include "PROPOSAL/crossection/CrossSection.h"

#include "PROPOSAL/math/InterpolantBuilder.h"
#include "PROPOSAL/math/MathMethods.h"

using namespace PROPOSAL;
using Helper::InitializeInterpolation;
/******************************************************************************
 *                              PropagationUtility Integral                              *
 ******************************************************************************/

UtilityInterpolant::UtilityInterpolant(
    std::function<double(double)> func, double lower_lim)
    : UtilityIntegral(func, lower_lim)
    , interpolant_(nullptr)
{
}

void UtilityInterpolant::BuildTables(std::string name, size_t hash,
    Interpolant1DBuilder::Definition interpol_def)
{
    interpol_def.xmin = lower_lim;
    Interpolant1DBuilder interpolant_builder(interpol_def);
    interpolant_ = InitializeInterpolation(
        name, interpolant_builder, hash, InterpolationDef());
}

double UtilityInterpolant::Calculate(
    double energy_initial, double energy_final, double rnd)
{
    (void)rnd;
    std::cout << "E_i, E_f: " << energy_initial << ", " << energy_final << std::endl; //DEBUG
    assert(energy_initial >= energy_final);
    assert(energy_final >= lower_lim);

    upper_limit = std::make_pair(
        interpolant_->Interpolate(energy_initial), energy_initial);

    if (energy_initial - energy_final < energy_initial * IPREC)
        return FunctionToIntegral((energy_initial+energy_initial)/2) * (energy_final - energy_initial);

    return upper_limit.first - interpolant_->Interpolate(energy_final);
}

// ------------------------------------------------------------------------- //
double UtilityInterpolant::GetUpperLimit(double energy_initial, double rnd)
{
    assert(rnd >= 0);
    if (energy_initial != upper_limit.second)
        Calculate(energy_initial, lower_lim, rnd);

    auto lower_limit = interpolant_->FindLimit(upper_limit.first - rnd);

    if (energy_initial - lower_limit > energy_initial * IPREC)
        return lower_limit;

    auto initial_step
        = energy_initial + 0.5 * rnd / FunctionToIntegral(energy_initial);

    return energy_initial + rnd / FunctionToIntegral(initial_step);
}
