
// #include <iostream>
// #include <string>

// #include <math.h>

#include "gtest/gtest.h"

#include "PROPOSAL/crossection/factories/PhotonuclearFactory.h"
#include "PROPOSAL/crossection/parametrization/PhotoRealPhotonAssumption.h"
#include "PROPOSAL/crossection/parametrization/PhotoQ2Integration.h"
#include "PROPOSAL/crossection/PhotoIntegral.h"
#include "PROPOSAL/crossection/PhotoInterpolant.h"
#include "PROPOSAL/medium/Medium.h"
#include "PROPOSAL/medium/MediumFactory.h"
#include "PROPOSAL/math/RandomGenerator.h"
#include "PROPOSAL/Output.h"
#include "PROPOSAL/methods.h"
#include "PROPOSAL/Constants.h"

using namespace std;
using namespace PROPOSAL;

ParticleDef getParticleDef(const string& name)
{
    if (name == "MuMinus")
    {
        return MuMinusDef::Get();
    }
    else if (name == "TauMinus")
    {
        return TauMinusDef::Get();
    }
    else
    {
        return EMinusDef::Get();
    }
}

TEST(Comparison, Comparison_equal)
{
    ParticleDef particle_def = MuMinusDef::Get();
    Water medium;
    EnergyCutSettings ecuts;
    double multiplier = 1.;
    bool hard_component = true;
    ShadowButkevichMikhailov shadow;
    InterpolationDef InterpolDef;

    PhotoKokoulin* PhotoReal_A = new PhotoKokoulin(particle_def, medium, ecuts, hard_component, multiplier);
    Parametrization* PhotoReal_B = new PhotoKokoulin(particle_def, medium, ecuts, hard_component, multiplier);
    EXPECT_TRUE(*PhotoReal_A == *PhotoReal_B);

    PhotoKokoulin param_PhotoReal(particle_def, medium, ecuts, hard_component, multiplier);
    EXPECT_TRUE(param_PhotoReal == *PhotoReal_A);

    PhotoIntegral* Int_PhotoReal_A = new PhotoIntegral(param_PhotoReal);
    CrossSectionIntegral* Int_PhotoReal_B = new PhotoIntegral(param_PhotoReal);
    EXPECT_TRUE(*Int_PhotoReal_A == *Int_PhotoReal_B);

    PhotoInterpolant* Interpol_PhotoReal_A = new PhotoInterpolant(param_PhotoReal, InterpolDef);
    CrossSectionInterpolant* Interpol_PhotoReal_B = new PhotoInterpolant(param_PhotoReal, InterpolDef);
    EXPECT_TRUE(*Interpol_PhotoReal_A == *Interpol_PhotoReal_B);

    delete PhotoReal_A;
    delete PhotoReal_B;
    delete Int_PhotoReal_A;
    delete Int_PhotoReal_B;
    delete Interpol_PhotoReal_A;
    delete Interpol_PhotoReal_B;

    PhotoAbramowiczLevinLevyMaor97* PhotoQ2_A = new PhotoAbramowiczLevinLevyMaor97(particle_def, medium, ecuts, shadow, multiplier);
    Parametrization* PhotoQ2_B = new PhotoAbramowiczLevinLevyMaor97(particle_def, medium, ecuts, shadow, multiplier);
    EXPECT_TRUE(*PhotoQ2_A == *PhotoQ2_B);

    PhotoAbramowiczLevinLevyMaor97 param_Q2(particle_def, medium, ecuts, shadow, multiplier);
    EXPECT_TRUE(param_Q2 == *PhotoQ2_A);

    PhotoIntegral* Int_PhotoQ2_A = new PhotoIntegral(param_Q2);
    CrossSectionIntegral* Int_PhotoQ2_B = new PhotoIntegral(param_Q2);
    EXPECT_TRUE(*Int_PhotoQ2_A == *Int_PhotoQ2_B);

    PhotoInterpolant* Interpol_PhotoQ2_A = new PhotoInterpolant(param_Q2, InterpolDef);
    CrossSectionInterpolant* Interpol_PhotoQ2_B = new PhotoInterpolant(param_Q2, InterpolDef);
    EXPECT_TRUE(*Interpol_PhotoQ2_A == *Interpol_PhotoQ2_B);

    delete PhotoQ2_A;
    delete PhotoQ2_B;
    delete Int_PhotoQ2_A;
    delete Int_PhotoQ2_B;
    delete Interpol_PhotoQ2_A;
    delete Interpol_PhotoQ2_B;
}

TEST(Comparison, Comparison_not_equal)
{
    ParticleDef mu_def = MuMinusDef::Get();
    ParticleDef tau_def = TauMinusDef::Get();
    Water medium_1;
    Ice medium_2;
    EnergyCutSettings ecuts_1(500, 0.05);
    EnergyCutSettings ecuts_2(-1, 0.05);
    double multiplier_1 = 1.;
    double multiplier_2 = 2.;
    bool hard_component = true;
    ShadowButkevichMikhailov shadow_1;
    ShadowDuttaRenoSarcevicSeckel shadow_2;
    InterpolationDef InterpolDef;

    PhotoKokoulin PhotoReal_A(mu_def, medium_1, ecuts_1, hard_component, multiplier_1);
    PhotoKokoulin PhotoReal_B(tau_def, medium_1, ecuts_1, hard_component, multiplier_1);
    PhotoKokoulin PhotoReal_C(mu_def, medium_2, ecuts_1, hard_component, multiplier_1);
    PhotoKokoulin PhotoReal_D(mu_def, medium_1, ecuts_2, hard_component, multiplier_1);
    PhotoKokoulin PhotoReal_E(mu_def, medium_1, ecuts_1, !hard_component, multiplier_1);
    PhotoKokoulin PhotoReal_F(mu_def, medium_1, ecuts_1, hard_component, multiplier_2);
    EXPECT_TRUE(PhotoReal_A != PhotoReal_B);
    EXPECT_TRUE(PhotoReal_A != PhotoReal_C);
    EXPECT_TRUE(PhotoReal_A != PhotoReal_D);
    EXPECT_TRUE(PhotoReal_A != PhotoReal_E);
    EXPECT_TRUE(PhotoReal_A != PhotoReal_F);

    PhotoZeus param_Real_2(mu_def, medium_1, ecuts_1, hard_component, multiplier_1);
    PhotoBezrukovBugaev param_Real_3(mu_def, medium_1, ecuts_1, hard_component, multiplier_1);
    PhotoRhode param_Real_4(mu_def, medium_1, ecuts_1, hard_component, multiplier_1);
    EXPECT_TRUE(PhotoReal_A != param_Real_2);
    EXPECT_TRUE(PhotoReal_A != param_Real_3);
    EXPECT_TRUE(PhotoReal_A != param_Real_4);
    EXPECT_TRUE(param_Real_2 != param_Real_3);
    EXPECT_TRUE(param_Real_2 != param_Real_4);
    EXPECT_TRUE(param_Real_3 != param_Real_4);
    
    PhotoIntegral Int_PhotoReal_A(PhotoReal_A);
    PhotoIntegral Int_PhotoReal_B(PhotoReal_B);
    EXPECT_TRUE(Int_PhotoReal_A != Int_PhotoReal_B);
    
    PhotoInterpolant Interpol_PhotoReal_A(PhotoReal_A, InterpolDef);
    PhotoInterpolant Interpol_PhotoReal_B(PhotoReal_B, InterpolDef);
    EXPECT_TRUE(Interpol_PhotoReal_A != Interpol_PhotoReal_B);
    //
    PhotoAbramowiczLevinLevyMaor97 PhotoQ2_A(mu_def, medium_1, ecuts_1, shadow_1, multiplier_1);
    PhotoAbramowiczLevinLevyMaor97 PhotoQ2_B(tau_def, medium_1, ecuts_1, shadow_1, multiplier_1);
    PhotoAbramowiczLevinLevyMaor97 PhotoQ2_C(mu_def, medium_2, ecuts_1, shadow_1, multiplier_1);
    PhotoAbramowiczLevinLevyMaor97 PhotoQ2_D(mu_def, medium_1, ecuts_2, shadow_1, multiplier_1);
    PhotoAbramowiczLevinLevyMaor97 PhotoQ2_E(mu_def, medium_1, ecuts_1, shadow_2, multiplier_1);
    PhotoAbramowiczLevinLevyMaor97 PhotoQ2_F(mu_def, medium_1, ecuts_1, shadow_1, multiplier_2);
    EXPECT_TRUE(PhotoQ2_A != PhotoQ2_B);
    EXPECT_TRUE(PhotoQ2_A != PhotoQ2_C);
    EXPECT_TRUE(PhotoQ2_A != PhotoQ2_D);
    EXPECT_TRUE(PhotoQ2_A != PhotoQ2_E);
    EXPECT_TRUE(PhotoQ2_A != PhotoQ2_F);
    //
    EXPECT_TRUE(PhotoReal_A != PhotoQ2_A);
    
    PhotoAbramowiczLevinLevyMaor91 param_Q2_2(mu_def, medium_1, ecuts_1, shadow_1, multiplier_1);
    PhotoButkevichMikhailov param_Q2_3(mu_def, medium_1, ecuts_1, shadow_1, multiplier_1);
    PhotoRenoSarcevicSu param_Q2_4(mu_def, medium_1, ecuts_1, shadow_1, multiplier_1);
    EXPECT_TRUE(PhotoQ2_A != param_Q2_2);
    EXPECT_TRUE(PhotoQ2_A != param_Q2_3);
    EXPECT_TRUE(PhotoQ2_A != param_Q2_4);
    EXPECT_TRUE(param_Q2_2 != param_Q2_3);
    EXPECT_TRUE(param_Q2_2 != param_Q2_4);
    EXPECT_TRUE(param_Q2_3 != param_Q2_4);
    
    PhotoIntegral Int_PhotoQ2_A(PhotoQ2_A);
    PhotoIntegral Int_PhotoQ2_B(PhotoQ2_B);
    EXPECT_TRUE(Int_PhotoQ2_A != Int_PhotoQ2_B);
    
    PhotoInterpolant Interpol_PhotoQ2_A(PhotoQ2_A, InterpolDef);
    PhotoInterpolant Interpol_PhotoQ2_B(PhotoQ2_B, InterpolDef);
    EXPECT_TRUE(Interpol_PhotoQ2_A != Interpol_PhotoQ2_B);
}

TEST(Assignment, Copyconstructor)
{
    ParticleDef particle_def = MuMinusDef::Get();
    Water medium;
    EnergyCutSettings ecuts;
    double multiplier = 1.;
    bool hardbb = true;
    ShadowButkevichMikhailov shadow;
    InterpolationDef InterpolDef;

    PhotoKokoulin PhotoReal_A(particle_def, medium, ecuts, hardbb, multiplier);
    PhotoKokoulin PhotoReal_B = PhotoReal_A;
    EXPECT_TRUE(PhotoReal_A == PhotoReal_B);

    PhotoIntegral Int_PhotoReal_A(PhotoReal_A);
    PhotoIntegral Int_PhotoReal_B = Int_PhotoReal_A;
    EXPECT_TRUE(Int_PhotoReal_A == Int_PhotoReal_B);

    PhotoInterpolant Interpol_PhotoReal_A(PhotoReal_A, InterpolDef);
    PhotoInterpolant Interpol_PhotoReal_B = Interpol_PhotoReal_A;
    EXPECT_TRUE(Interpol_PhotoReal_A == Interpol_PhotoReal_B);

    PhotoAbramowiczLevinLevyMaor97 PhotoQ2_A(particle_def, medium, ecuts, shadow, multiplier);
    PhotoAbramowiczLevinLevyMaor97 PhotoQ2_B = PhotoQ2_A;
    EXPECT_TRUE(PhotoQ2_A == PhotoQ2_B);

    PhotoIntegral Int_PhotoQ2_A(PhotoQ2_A);
    PhotoIntegral Int_PhotoQ2_B = Int_PhotoQ2_A;
    EXPECT_TRUE(Int_PhotoQ2_A == Int_PhotoQ2_B);

    PhotoInterpolant Interpol_PhotoQ2_A(PhotoQ2_A, InterpolDef);
    PhotoInterpolant Interpol_PhotoQ2_B = Interpol_PhotoQ2_A;
    EXPECT_TRUE(Interpol_PhotoQ2_A == Interpol_PhotoQ2_B);
}

TEST(Assignment, Copyconstructor2)
{
    ParticleDef particle_def = MuMinusDef::Get();
    Water medium;
    EnergyCutSettings ecuts;
    double multiplier = 1.;
    bool hard_component = true;
    ShadowButkevichMikhailov shadow;
    InterpolationDef InterpolDef;

    PhotoKokoulin PhotoReal_A(particle_def, medium, ecuts, hard_component, multiplier);
    PhotoKokoulin PhotoReal_B(PhotoReal_A);
    EXPECT_TRUE(PhotoReal_A == PhotoReal_B);

    PhotoIntegral Int_PhotoReal_A(PhotoReal_A);
    PhotoIntegral Int_PhotoReal_B(Int_PhotoReal_A);
    EXPECT_TRUE(Int_PhotoReal_A == Int_PhotoReal_B);

    PhotoInterpolant Interpol_PhotoReal_A(PhotoReal_A, InterpolDef);
    PhotoInterpolant Interpol_PhotoReal_B(Interpol_PhotoReal_A);
    EXPECT_TRUE(Interpol_PhotoReal_A == Interpol_PhotoReal_B);

    PhotoAbramowiczLevinLevyMaor97 PhotoQ2_A(particle_def, medium, ecuts, shadow, multiplier);
    PhotoAbramowiczLevinLevyMaor97 PhotoQ2_B(PhotoQ2_A);
    EXPECT_TRUE(PhotoQ2_A == PhotoQ2_B);

    PhotoIntegral Int_PhotoQ2_A(PhotoQ2_A);
    PhotoIntegral Int_PhotoQ2_B(Int_PhotoQ2_A);
    EXPECT_TRUE(Int_PhotoQ2_A == Int_PhotoQ2_B);

    PhotoInterpolant Interpol_PhotoQ2_A(PhotoQ2_A, InterpolDef);
    PhotoInterpolant Interpol_PhotoQ2_B(Interpol_PhotoQ2_A);
    EXPECT_TRUE(Interpol_PhotoQ2_A == Interpol_PhotoQ2_B);
}

// in polymorphism an assignmant and swap operator doesn't make sense



TEST(PhotoRealPhotonAssumption, Test_of_dEdx)
{
    ifstream in;
    string filename = "testfiles/Photo_Real_dEdx.txt";
    in.open(filename.c_str());

    if (!in.good())
    {
        std::cerr << "File \"" << filename << "\" not found" << std::endl;
    }

    string particleName;
    string mediumName;
    double ecut;
    double vcut;
    double multiplier;
    string parametrization;
    bool hard_component;
    double energy;
    double dEdx_stored;
    double dEdx_new;

    cout.precision(16);

    while(in.good())
    {
        in >> particleName >> mediumName >> ecut >> vcut >> multiplier
            >> energy >> dEdx_stored >> parametrization >> hard_component;

        ParticleDef particle_def = getParticleDef(particleName);
        Medium* medium = MediumFactory::Get().CreateMedium(mediumName);
        EnergyCutSettings ecuts(ecut,vcut);

        PhotonuclearFactory::Definition photo_def;
        photo_def.multiplier = multiplier;
        photo_def.parametrization = PhotonuclearFactory::Get().GetEnumFromString(parametrization);
        photo_def.hard_component = hard_component;

        CrossSection* Photo = PhotonuclearFactory::Get().CreatePhotonuclear(
            particle_def,
            *medium,
            ecuts,
            photo_def);

        dEdx_new = Photo->CalculatedEdx(energy);

        ASSERT_NEAR(dEdx_new, dEdx_stored, 1e-3*dEdx_stored);

        delete medium;
        delete Photo;
    }
}

TEST(PhotoRealPhotonAssumption, Test_of_dNdx)
{
    ifstream in;
    string filename = "testfiles/Photo_Real_dNdx.txt";
    in.open(filename.c_str());

    if (!in.good())
    {
        std::cerr << "File \"" << filename << "\" not found" << std::endl;
    }

    string particleName;
    string mediumName;
    double ecut;
    double vcut;
    double multiplier;
    string parametrization;
    bool hard_component;
    double energy;
    double dNdx_stored;
    double dNdx_new;

    cout.precision(16);

    while(in.good())
    {
        in >> particleName >> mediumName >> ecut >> vcut >> multiplier
            >> energy >> dNdx_stored >> parametrization >> hard_component;

        ParticleDef particle_def = getParticleDef(particleName);
        Medium* medium = MediumFactory::Get().CreateMedium(mediumName);
        EnergyCutSettings ecuts(ecut,vcut);

        PhotonuclearFactory::Definition photo_def;
        photo_def.multiplier = multiplier;
        photo_def.parametrization = PhotonuclearFactory::Get().GetEnumFromString(parametrization);
        photo_def.hard_component = hard_component;

        CrossSection* Photo = PhotonuclearFactory::Get().CreatePhotonuclear(
            particle_def,
            *medium,
            ecuts,
            photo_def);

        dNdx_new = Photo->CalculatedNdx(energy);

        ASSERT_NEAR(dNdx_new, dNdx_stored, 1e-3*dNdx_stored);

        delete medium;
        delete Photo;
    }
}

TEST(PhotoRealPhotonAssumption, Test_of_dNdx_rnd)
{
    ifstream in;
    string filename = "testfiles/Photo_Real_dNdx_rnd.txt";
    in.open(filename.c_str());

    if (!in.good())
    {
        std::cerr << "File \"" << filename << "\" not found" << std::endl;
    }

    string particleName;
    string mediumName;
    double ecut;
    double vcut;
    double multiplier;
    string parametrization;
    bool hard_component;
    double energy;
    double rnd;
    double dNdx_stored;
    double dNdx_new;

    cout.precision(16);

    while(in.good())
    {
        in >> particleName >> mediumName >> ecut >> vcut >> multiplier
            >> energy >> rnd >> dNdx_stored >> parametrization >> hard_component;

        ParticleDef particle_def = getParticleDef(particleName);
        Medium* medium = MediumFactory::Get().CreateMedium(mediumName);
        EnergyCutSettings ecuts(ecut,vcut);

        PhotonuclearFactory::Definition photo_def;
        photo_def.multiplier = multiplier;
        photo_def.parametrization = PhotonuclearFactory::Get().GetEnumFromString(parametrization);
        photo_def.hard_component = hard_component;

        CrossSection* Photo = PhotonuclearFactory::Get().CreatePhotonuclear(
            particle_def,
            *medium,
            ecuts,
            photo_def);

        dNdx_new = Photo->CalculatedNdx(energy, rnd);

        ASSERT_NEAR(dNdx_new, dNdx_stored, 1e-3*dNdx_stored);

        delete medium;
        delete Photo;
    }
}

TEST(PhotoRealPhotonAssumption, Test_of_e)
{
    ifstream in;
    string filename = "testfiles/Photo_Real_e.txt";
    in.open(filename.c_str());

    if (!in.good())
    {
        std::cerr << "File \"" << filename << "\" not found" << std::endl;
    }

    string particleName;
    string mediumName;
    double ecut;
    double vcut;
    double multiplier;
    string parametrization;
    bool hard_component;
    double energy;
    double rnd1, rnd2;
    double stochastic_loss_stored;
    double stochastic_loss_new;

    cout.precision(16);

    while(in.good())
    {
        in >> particleName >> mediumName >> ecut >> vcut >> multiplier
            >> energy >> rnd1 >> rnd2 >> stochastic_loss_stored >> parametrization >> hard_component;

        ParticleDef particle_def = getParticleDef(particleName);
        Medium* medium = MediumFactory::Get().CreateMedium(mediumName);
        EnergyCutSettings ecuts(ecut,vcut);

        PhotonuclearFactory::Definition photo_def;
        photo_def.multiplier = multiplier;
        photo_def.parametrization = PhotonuclearFactory::Get().GetEnumFromString(parametrization);
        photo_def.hard_component = hard_component;

        CrossSection* Photo = PhotonuclearFactory::Get().CreatePhotonuclear(
            particle_def,
            *medium,
            ecuts,
            photo_def);

        stochastic_loss_new = Photo->CalculateStochasticLoss(energy, rnd1, rnd2);

        ASSERT_NEAR(stochastic_loss_new, stochastic_loss_stored, 1e-3*stochastic_loss_stored);

        delete medium;
        delete Photo;
    }
}

TEST(PhotoRealPhotonAssumption, Test_of_dEdx_Interpolant)
{
    ifstream in;
    string filename = "testfiles/Photo_Real_dEdx_interpol.txt";
    in.open(filename.c_str());

    if (!in.good())
    {
        std::cerr << "File \"" << filename << "\" not found" << std::endl;
    }

    string particleName;
    string mediumName;
    double ecut;
    double vcut;
    double multiplier;
    string parametrization;
    bool hard_component;
    double energy;
    double dEdx_stored;
    double dEdx_new;

    cout.precision(16);
    InterpolationDef InterpolDef;

    while(in.good())
    {
        in >> particleName >> mediumName >> ecut >> vcut >> multiplier
            >> energy >> dEdx_stored >> parametrization >> hard_component;

        ParticleDef particle_def = getParticleDef(particleName);
        Medium* medium = MediumFactory::Get().CreateMedium(mediumName);
        EnergyCutSettings ecuts(ecut,vcut);

        PhotonuclearFactory::Definition photo_def;
        photo_def.multiplier = multiplier;
        photo_def.parametrization = PhotonuclearFactory::Get().GetEnumFromString(parametrization);
        photo_def.hard_component = hard_component;

        CrossSection* Photo = PhotonuclearFactory::Get().CreatePhotonuclear(
            particle_def,
            *medium,
            ecuts,
            photo_def,
            InterpolDef);

        dEdx_new = Photo->CalculatedEdx(energy);

        ASSERT_NEAR(dEdx_new, dEdx_stored, 1e-3*dEdx_stored);

        delete medium;
        delete Photo;
    }
}

TEST(PhotoRealPhotonAssumption, Test_of_dNdx_Interpolant)
{
    ifstream in;
    string filename = "testfiles/Photo_Real_dNdx_interpol.txt";
    in.open(filename.c_str());

    if (!in.good())
    {
        std::cerr << "File \"" << filename << "\" not found" << std::endl;
    }

    string particleName;
    string mediumName;
    double ecut;
    double vcut;
    double multiplier;
    string parametrization;
    bool hard_component;
    double energy;
    double dNdx_stored;
    double dNdx_new;

    cout.precision(16);
    InterpolationDef InterpolDef;

    while(in.good())
    {
        in >> particleName >> mediumName >> ecut >> vcut >> multiplier
            >> energy >> dNdx_stored >> parametrization >> hard_component;

        ParticleDef particle_def = getParticleDef(particleName);
        Medium* medium = MediumFactory::Get().CreateMedium(mediumName);
        EnergyCutSettings ecuts(ecut,vcut);

        PhotonuclearFactory::Definition photo_def;
        photo_def.multiplier = multiplier;
        photo_def.parametrization = PhotonuclearFactory::Get().GetEnumFromString(parametrization);
        photo_def.hard_component = hard_component;

        CrossSection* Photo = PhotonuclearFactory::Get().CreatePhotonuclear(
            particle_def,
            *medium,
            ecuts,
            photo_def,
            InterpolDef);

        dNdx_new = Photo->CalculatedNdx(energy);

        ASSERT_NEAR(dNdx_new, dNdx_stored, 1e-3*dNdx_stored);

        delete medium;
        delete Photo;
    }
}

TEST(PhotoRealPhotonAssumption, Test_of_dNdx_rnd_Interpolant)
{
    ifstream in;
    string filename = "testfiles/Photo_Real_dNdx_rnd_interpol.txt";
    in.open(filename.c_str());

    if (!in.good())
    {
        std::cerr << "File \"" << filename << "\" not found" << std::endl;
    }

    string particleName;
    string mediumName;
    double ecut;
    double vcut;
    double multiplier;
    string parametrization;
    bool hard_component;
    double energy;
    double rnd;
    double dNdx_stored;
    double dNdx_new;

    cout.precision(16);
    InterpolationDef InterpolDef;

    while(in.good())
    {
        in >> particleName >> mediumName >> ecut >> vcut >> multiplier
            >> energy >> rnd >> dNdx_stored >> parametrization >> hard_component;

        ParticleDef particle_def = getParticleDef(particleName);
        Medium* medium = MediumFactory::Get().CreateMedium(mediumName);
        EnergyCutSettings ecuts(ecut,vcut);

        PhotonuclearFactory::Definition photo_def;
        photo_def.multiplier = multiplier;
        photo_def.parametrization = PhotonuclearFactory::Get().GetEnumFromString(parametrization);
        photo_def.hard_component = hard_component;

        CrossSection* Photo = PhotonuclearFactory::Get().CreatePhotonuclear(
            particle_def,
            *medium,
            ecuts,
            photo_def,
            InterpolDef);

        dNdx_new = Photo->CalculatedNdx(energy, rnd);

        ASSERT_NEAR(dNdx_new, dNdx_stored, 1e-3*dNdx_stored);

        delete medium;
        delete Photo;
    }
}

TEST(PhotoRealPhotonAssumption, Test_of_e_Interpolant)
{
    ifstream in;
    string filename = "testfiles/Photo_e_interpol.txt";
    in.open(filename.c_str());

    if (!in.good())
    {
        std::cerr << "File \"" << filename << "\" not found" << std::endl;
    }

    string particleName;
    string mediumName;
    double ecut;
    double vcut;
    double multiplier;
    string parametrization;
    bool hard_component;
    double energy;
    double rnd1, rnd2;
    double stochastic_loss_stored;
    double stochastic_loss_new;

    cout.precision(16);
    InterpolationDef InterpolDef;

    while(in.good())
    {
        in >> particleName >> mediumName >> ecut >> vcut >> multiplier
            >> energy >> rnd1 >> rnd2 >> stochastic_loss_stored >> parametrization >> hard_component;

        ParticleDef particle_def = getParticleDef(particleName);
        Medium* medium = MediumFactory::Get().CreateMedium(mediumName);
        EnergyCutSettings ecuts(ecut,vcut);

        PhotonuclearFactory::Definition photo_def;
        photo_def.multiplier = multiplier;
        photo_def.parametrization = PhotonuclearFactory::Get().GetEnumFromString(parametrization);
        photo_def.hard_component = hard_component;

        CrossSection* Photo = PhotonuclearFactory::Get().CreatePhotonuclear(
            particle_def,
            *medium,
            ecuts,
            photo_def,
            InterpolDef);

        stochastic_loss_new = Photo->CalculateStochasticLoss(energy, rnd1, rnd2);

        ASSERT_NEAR(stochastic_loss_new, stochastic_loss_stored, 1e-3*stochastic_loss_stored);

        delete medium;
        delete Photo;
    }
}

// Photonuclear parametrization with Q2 Integration

TEST(PhotoQ2Integration, Test_of_dEdx)
{
    ifstream in;
    string filename = "testfiles/Photo_Q2_dEdx.txt";
    in.open(filename.c_str());

    if (!in.good())
    {
        std::cerr << "File \"" << filename << "\" not found" << std::endl;
    }

    string particleName;
    string mediumName;
    double ecut;
    double vcut;
    double multiplier;
    string parametrization;
    string shadowing;
    double energy;
    double dEdx_stored;
    double dEdx_new;

    cout.precision(16);

    while(in.good())
    {
        in >> particleName >> mediumName >> ecut >> vcut >> multiplier
            >> energy >> dEdx_stored >> parametrization >> shadowing;

        ParticleDef particle_def = getParticleDef(particleName);
        Medium* medium = MediumFactory::Get().CreateMedium(mediumName);
        EnergyCutSettings ecuts(ecut,vcut);

        PhotonuclearFactory::Definition photo_def;
        photo_def.multiplier = multiplier;
        photo_def.parametrization = PhotonuclearFactory::Get().GetEnumFromString(parametrization);
        photo_def.shadow = PhotonuclearFactory::Get().GetShadowEnumFromString(shadowing);

        CrossSection* Photo = PhotonuclearFactory::Get().CreatePhotonuclear(
            particle_def,
            *medium,
            ecuts,
            photo_def);

        dEdx_new = Photo->CalculatedEdx(energy);

        ASSERT_NEAR(dEdx_new, dEdx_stored, 1e-3*dEdx_stored);

        delete medium;
        delete Photo;
    }
}

TEST(PhotoQ2Integration, Test_of_dNdx)
{
    ifstream in;
    string filename = "testfiles/Photo_Q2_dNdx.txt";
    in.open(filename.c_str());

    if (!in.good())
    {
        std::cerr << "File \"" << filename << "\" not found" << std::endl;
    }

    string particleName;
    string mediumName;
    double ecut;
    double vcut;
    double multiplier;
    string parametrization;
    string shadowing;
    double energy;
    double dNdx_stored;
    double dNdx_new;

    cout.precision(16);

    while(in.good())
    {
        in >> particleName >> mediumName >> ecut >> vcut >> multiplier
            >> energy >> dNdx_stored >> parametrization >> shadowing;

        ParticleDef particle_def = getParticleDef(particleName);
        Medium* medium = MediumFactory::Get().CreateMedium(mediumName);
        EnergyCutSettings ecuts(ecut,vcut);

        PhotonuclearFactory::Definition photo_def;
        photo_def.multiplier = multiplier;
        photo_def.parametrization = PhotonuclearFactory::Get().GetEnumFromString(parametrization);
        photo_def.shadow = PhotonuclearFactory::Get().GetShadowEnumFromString(shadowing);

        CrossSection* Photo = PhotonuclearFactory::Get().CreatePhotonuclear(
            particle_def,
            *medium,
            ecuts,
            photo_def);

        dNdx_new = Photo->CalculatedNdx(energy);

        ASSERT_NEAR(dNdx_new, dNdx_stored, 1e-3*dNdx_stored);

        delete medium;
        delete Photo;
    }
}

TEST(PhotoQ2Integration, Test_of_dNdx_rnd)
{
    ifstream in;
    string filename = "testfiles/Photo_Q2_dNdx_rnd.txt";
    in.open(filename.c_str());

    if (!in.good())
    {
        std::cerr << "File \"" << filename << "\" not found" << std::endl;
    }

    string particleName;
    string mediumName;
    double ecut;
    double vcut;
    double multiplier;
    string parametrization;
    string shadowing;
    double energy;
    double rnd;
    double dNdx_stored;
    double dNdx_new;

    cout.precision(16);

    while(in.good())
    {
        in >> particleName >> mediumName >> ecut >> vcut >> multiplier
            >> energy >> rnd >> dNdx_stored >> parametrization >> shadowing;

        ParticleDef particle_def = getParticleDef(particleName);
        Medium* medium = MediumFactory::Get().CreateMedium(mediumName);
        EnergyCutSettings ecuts(ecut,vcut);

        PhotonuclearFactory::Definition photo_def;
        photo_def.multiplier = multiplier;
        photo_def.parametrization = PhotonuclearFactory::Get().GetEnumFromString(parametrization);
        photo_def.shadow = PhotonuclearFactory::Get().GetShadowEnumFromString(shadowing);

        CrossSection* Photo = PhotonuclearFactory::Get().CreatePhotonuclear(
            particle_def,
            *medium,
            ecuts,
            photo_def);

        dNdx_new = Photo->CalculatedNdx(energy, rnd);

        ASSERT_NEAR(dNdx_new, dNdx_stored, 1e-3*dNdx_stored);

        delete medium;
        delete Photo;
    }
}

TEST(PhotoQ2Integration, Test_of_e)
{
    ifstream in;
    string filename = "testfiles/Photo_Q2_e.txt";
    in.open(filename.c_str());

    if (!in.good())
    {
        std::cerr << "File \"" << filename << "\" not found" << std::endl;
    }

    string particleName;
    string mediumName;
    double ecut;
    double vcut;
    double multiplier;
    string parametrization;
    string shadowing;
    double energy;
    double rnd1, rnd2;
    double stochastic_loss_stored;
    double stochastic_loss_new;

    cout.precision(16);

    while(in.good())
    {
        in >> particleName >> mediumName >> ecut >> vcut >> multiplier
            >> energy >> rnd1 >> rnd2 >> stochastic_loss_stored >> parametrization >> shadowing;

        ParticleDef particle_def = getParticleDef(particleName);
        Medium* medium = MediumFactory::Get().CreateMedium(mediumName);
        EnergyCutSettings ecuts(ecut,vcut);

        PhotonuclearFactory::Definition photo_def;
        photo_def.multiplier = multiplier;
        photo_def.parametrization = PhotonuclearFactory::Get().GetEnumFromString(parametrization);
        photo_def.shadow = PhotonuclearFactory::Get().GetShadowEnumFromString(shadowing);

        CrossSection* Photo = PhotonuclearFactory::Get().CreatePhotonuclear(
            particle_def,
            *medium,
            ecuts,
            photo_def);

        stochastic_loss_new = Photo->CalculateStochasticLoss(energy, rnd1, rnd2);

        ASSERT_NEAR(stochastic_loss_new, stochastic_loss_stored, 1e-3*stochastic_loss_stored);

        delete medium;
        delete Photo;
    }
}

TEST(PhotoQ2Integration, Test_of_dEdx_Interpolant)
{
    ifstream in;
    string filename = "testfiles/Photo_Q2_dEdx_interpol.txt";
    in.open(filename.c_str());

    if (!in.good())
    {
        std::cerr << "File \"" << filename << "\" not found" << std::endl;
    }

    string particleName;
    string mediumName;
    double ecut;
    double vcut;
    double multiplier;
    string parametrization;
    string shadowing;
    double energy;
    double dEdx_stored;
    double dEdx_new;

    cout.precision(16);
    InterpolationDef InterpolDef;

    while(in.good())
    {
        in >> particleName >> mediumName >> ecut >> vcut >> multiplier
            >> energy >> dEdx_stored >> parametrization >> shadowing;

        ParticleDef particle_def = getParticleDef(particleName);
        Medium* medium = MediumFactory::Get().CreateMedium(mediumName);
        EnergyCutSettings ecuts(ecut,vcut);

        PhotonuclearFactory::Definition photo_def;
        photo_def.multiplier = multiplier;
        photo_def.parametrization = PhotonuclearFactory::Get().GetEnumFromString(parametrization);
        photo_def.shadow = PhotonuclearFactory::Get().GetShadowEnumFromString(shadowing);

        CrossSection* Photo = PhotonuclearFactory::Get().CreatePhotonuclear(
            particle_def,
            *medium,
            ecuts,
            photo_def,
            InterpolDef);

        dEdx_new = Photo->CalculatedEdx(energy);

        ASSERT_NEAR(dEdx_new, dEdx_stored, 1e-3*dEdx_stored);

        delete medium;
        delete Photo;
    }
}

TEST(PhotoQ2Integration, Test_of_dNdx_Interpolant)
{
    ifstream in;
    string filename = "testfiles/Photo_Q2_dNdx_interpol.txt";
    in.open(filename.c_str());

    if (!in.good())
    {
        std::cerr << "File \"" << filename << "\" not found" << std::endl;
    }

    string particleName;
    string mediumName;
    double ecut;
    double vcut;
    double multiplier;
    string parametrization;
    string shadowing;
    double energy;
    double dNdx_stored;
    double dNdx_new;

    cout.precision(16);
    InterpolationDef InterpolDef;

    while(in.good())
    {
        in >> particleName >> mediumName >> ecut >> vcut >> multiplier
            >> energy >> dNdx_stored >> parametrization >> shadowing;

        ParticleDef particle_def = getParticleDef(particleName);
        Medium* medium = MediumFactory::Get().CreateMedium(mediumName);
        EnergyCutSettings ecuts(ecut,vcut);

        PhotonuclearFactory::Definition photo_def;
        photo_def.multiplier = multiplier;
        photo_def.parametrization = PhotonuclearFactory::Get().GetEnumFromString(parametrization);
        photo_def.shadow = PhotonuclearFactory::Get().GetShadowEnumFromString(shadowing);

        CrossSection* Photo = PhotonuclearFactory::Get().CreatePhotonuclear(
            particle_def,
            *medium,
            ecuts,
            photo_def,
            InterpolDef);

        dNdx_new = Photo->CalculatedNdx(energy);

        ASSERT_NEAR(dNdx_new, dNdx_stored, 1e-3*dNdx_stored);

        delete medium;
        delete Photo;
    }
}

TEST(PhotoQ2Integration, Test_of_dNdx_rnd_Interpolant)
{
    ifstream in;
    string filename = "testfiles/Photo_Q2_dNdx_rnd_interpol.txt";
    in.open(filename.c_str());

    if (!in.good())
    {
        std::cerr << "File \"" << filename << "\" not found" << std::endl;
    }

    string particleName;
    string mediumName;
    double ecut;
    double vcut;
    double multiplier;
    string parametrization;
    string shadowing;
    double energy;
    double rnd;
    double dNdx_stored;
    double dNdx_new;

    cout.precision(16);
    InterpolationDef InterpolDef;

    while(in.good())
    {
        in >> particleName >> mediumName >> ecut >> vcut >> multiplier
            >> energy >> rnd >> dNdx_stored >> parametrization >> shadowing;

        ParticleDef particle_def = getParticleDef(particleName);
        Medium* medium = MediumFactory::Get().CreateMedium(mediumName);
        EnergyCutSettings ecuts(ecut,vcut);

        PhotonuclearFactory::Definition photo_def;
        photo_def.multiplier = multiplier;
        photo_def.parametrization = PhotonuclearFactory::Get().GetEnumFromString(parametrization);
        photo_def.shadow = PhotonuclearFactory::Get().GetShadowEnumFromString(shadowing);

        CrossSection* Photo = PhotonuclearFactory::Get().CreatePhotonuclear(
            particle_def,
            *medium,
            ecuts,
            photo_def,
            InterpolDef);

        dNdx_new = Photo->CalculatedNdx(energy, rnd);

        ASSERT_NEAR(dNdx_new, dNdx_stored, 1e-3*dNdx_stored);

        delete medium;
        delete Photo;
    }
}

TEST(PhotoQ2Integration, Test_of_e_Interpolant)
{
    ifstream in;
    string filename = "testfiles/Photo_Q2_e_interpol.txt";
    in.open(filename.c_str());

    if (!in.good())
    {
        std::cerr << "File \"" << filename << "\" not found" << std::endl;
    }

    string particleName;
    string mediumName;
    double ecut;
    double vcut;
    double multiplier;
    string parametrization;
    string shadowing;
    double energy;
    double rnd1, rnd2;
    double stochastic_loss_stored;
    double stochastic_loss_new;

    cout.precision(16);
    InterpolationDef InterpolDef;

    while(in.good())
    {
        in >> particleName >> mediumName >> ecut >> vcut >> multiplier
            >> energy >> rnd1 >> rnd2 >> stochastic_loss_stored >> parametrization >> shadowing;

        ParticleDef particle_def = getParticleDef(particleName);
        Medium* medium = MediumFactory::Get().CreateMedium(mediumName);
        EnergyCutSettings ecuts(ecut,vcut);

        PhotonuclearFactory::Definition photo_def;
        photo_def.multiplier = multiplier;
        photo_def.parametrization = PhotonuclearFactory::Get().GetEnumFromString(parametrization);
        photo_def.shadow = PhotonuclearFactory::Get().GetShadowEnumFromString(shadowing);

        CrossSection* Photo = PhotonuclearFactory::Get().CreatePhotonuclear(
            particle_def,
            *medium,
            ecuts,
            photo_def,
            InterpolDef);

        stochastic_loss_new = Photo->CalculateStochasticLoss(energy, rnd1, rnd2);

        ASSERT_NEAR(stochastic_loss_new, stochastic_loss_stored, 1e-3*stochastic_loss_stored);

        delete medium;
        delete Photo;
    }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
