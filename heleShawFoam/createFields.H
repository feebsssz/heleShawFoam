#include "createRDeltaT.H"

Info<< "Reading field p_rgh\n" << endl;
volScalarField p_rgh
(
    IOobject
    (
        "p_rgh",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field U\n" << endl;
volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

#include "createPhi.H"


Info<< "Reading transportProperties\n" << endl;

IOdictionary transportProperties
(
    IOobject
    (
        "transportProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ_IF_MODIFIED,
        IOobject::NO_WRITE
    )
);

dimensionedScalar gapWidth
(
    "gapWidth",
    dimLength,
    transportProperties
);


immiscibleIncompressibleTwoPhaseMixture mixture(U, phi);

const dimensionedScalar& rho1 = mixture.rho1();
const dimensionedScalar& rho2 = mixture.rho2();

const word phase1 = mixture.phase1Name();
const word phase2 = mixture.phase2Name();
const auto coeffs1 = transportProperties.subDict(phase1).subDict("powerLawCoeffs");
const auto coeffs2 = transportProperties.subDict(phase2).subDict("powerLawCoeffs");

const dimensionedScalar k1("k1", dimViscosity, coeffs1, "k");
const dimensionedScalar k2("k2", dimViscosity, coeffs2, "k");
const dimensionedScalar n1("n1", dimless, coeffs1, "n");
const dimensionedScalar n2("n2", dimless, coeffs2, "n");

const scalar m1 = 1/n1.value();
const scalar m2 = 1/n2.value();
const scalar A1 = 2*(m1+2)/(2*m1+3);
const scalar A2 = 2*(m2+2)/(2*m2+3);

const dimensionedScalar dimN1("dimN1", dimensionSet(0,0,n1.value()-1,0,0,0,0), 1.0);
const dimensionedScalar dimN2("dimN2", dimensionSet(0,0,n2.value()-1,0,0,0,0), 1.0);

const dimensionedScalar smallU("smallU", dimVelocity, SMALL);

volScalarField& alpha1(mixture.alpha1());
volScalarField& alpha2(mixture.alpha2());

// Need to store rho for ddt(rho, U)
volScalarField rho
(
    IOobject
    (
        "rho",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT
    ),
    alpha1*rho1 + alpha2*rho2
);
rho.oldTime();


// Mass flux
surfaceScalarField rhoPhi
(
    IOobject
    (
        "rhoPhi",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    fvc::interpolate(rho)*phi
);

typedef incompressibleInterPhaseTransportModel
    <
        immiscibleIncompressibleTwoPhaseMixture
    > transportModelType;

autoPtr<transportModelType> turbulence
(
    new transportModelType
    (
        rho, U, phi, rhoPhi, mixture
    )
);


#include "readGravitationalAcceleration.H"
#include "readhRef.H"
#include "gh.H"


volScalarField p
(
    IOobject
    (
        "p",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    p_rgh + rho*gh
);

label pRefCell = 0;
scalar pRefValue = 0.0;
setRefCell
(
    p,
    p_rgh,
    pimple.dict(),
    pRefCell,
    pRefValue
);

if (p_rgh.needReference())
{
    p += dimensionedScalar
    (
        "p",
        p.dimensions(),
        pRefValue - getRefCellValue(p, pRefCell)
    );
    p_rgh = p - rho*gh;
}

mesh.setFluxRequired(p_rgh.name());
mesh.setFluxRequired(alpha1.name());

#include "createFvOptions.H"

isoAdvection advector(alpha1, phi, U);
