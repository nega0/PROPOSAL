#pragma once

#include <memory>
#include <spdlog/fwd.h>

namespace PROPOSAL {
class EnergyCutSettings;
class ParticleDef;
class Medium;
class Component;
namespace crosssection {
    template <typename T> class Parametrization;
} // namespace crosssection
} // namespace PROPOSAL

namespace PROPOSAL {
class CrossSectionDEDX {
protected:
    size_t hash;
    std::shared_ptr<spdlog::logger> logger;

    CrossSectionDEDX(size_t _hash);

public:
    CrossSectionDEDX(crosssection::Parametrization<Medium> const&,
        ParticleDef const&, Medium const&, EnergyCutSettings const&,
        size_t hash = 0);

    CrossSectionDEDX(crosssection::Parametrization<Component> const&,
        ParticleDef const&, Component const&, EnergyCutSettings const&,
        size_t hash = 0);

    virtual ~CrossSectionDEDX() = default;

    virtual double Calculate(double energy) const = 0;

    size_t GetHash() const noexcept { return hash; }
};
} // namespace PROPOSAL
