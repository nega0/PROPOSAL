
/******************************************************************************
 *                                                                            *
 * This file is part of the simulation tool PROPOSAL.                         *
 *                                                                            *
 * Copyright (C) 2017 TU Dortmund University, Department of Physics,          *
 *                    Chair Experimental Physics 5b                           *
 *                                                                            *
 * This software may be modified and distributed under the terms of a         *
 * modified GNU Lesser General Public Licence version 3 (LGPL),               *
 * copied verbatim in the file "LICENSE".                                     *
 *                                                                            *
 * Modifcations to the LGPL License:                                          *
 *                                                                            *
 *      1. The user shall acknowledge the use of PROPOSAL by citing the       *
 *         following reference:                                               *
 *                                                                            *
 *         J.H. Koehne et al.  Comput.Phys.Commun. 184 (2013) 2070-2090 DOI:  *
 *         10.1016/j.cpc.2013.04.001                                          *
 *                                                                            *
 *      2. The user should report any bugs/errors or improvments to the       *
 *         current maintainer of PROPOSAL or open an issue on the             *
 *         GitHub webpage                                                     *
 *                                                                            *
 *         "https://github.com/tudo-astroparticlephysics/PROPOSAL"            *
 *                                                                            *
 ******************************************************************************/


#pragma once
#include <utility>
#include <memory>
#include "PROPOSAL/math/Vector3D.h"
#include "PROPOSAL/particle/Particle.h"

namespace PROPOSAL {

struct ParticleDef;
class PropagationUtility;

class Scattering
{
public:
    Scattering() = default;
    Scattering(const ParticleDef&);
    Scattering(const Scattering&);
    virtual ~Scattering() = default;

    bool operator==(const Scattering& scattering) const;
    bool operator!=(const Scattering& scattering) const;
    friend std::ostream& operator<<(std::ostream&, Scattering const&);


    std::tuple<Vector3D, Vector3D> Scatter(double grammage, double ei, double ef, const Vector3D& old_direction, const std::array<double, 4>& rnd);

protected:
    Scattering& operator=(const Scattering&); // Undefined & not allowed

    // Implemented in child classes to be able to use equality operator
    virtual bool compare(const Scattering&) const = 0;
    virtual void print(std::ostream&) const     = 0;

    struct RandomAngles
    {
        double sx, sy, tx, ty;
    };

    virtual RandomAngles CalculateRandomAngle(double grammage,
                                              double ei,
                                              double ef,
                                              const std::array<double, 4>& rnd) = 0;

    double mass;
};

} // namespace PROPOSAL
