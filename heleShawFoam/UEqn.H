
    tmp<surfaceScalarField> A = fvc::interpolate(alpha1*A1 + alpha2*A2);

    tmp<volScalarField> B1 = dimN1*rho1*k1*pow(2/gapWidth, n1 + 1) * pow(m1 + 2, n1) * pow(mag(U) +  smallU, n1 - 1);
    tmp<volScalarField> B2 = dimN2*rho2*k2*pow(2/gapWidth, n2 + 1) * pow(m2 + 2, n2) * pow(mag(U) +  smallU, n2 - 1);
    tmp<volScalarField> B = alpha1*B1 + alpha2*B2;

    fvVectorMatrix UEqn
    (
        fvm::ddt(rho, U) + fvm::div(A*rhoPhi, U)
      + turbulence->divDevRhoReff(rho, U)
     ==
        fvOptions(rho, U)
      - fvm::Sp(B,U)
    );

    UEqn.relax();

    fvOptions.constrain(UEqn);

    if (pimple.momentumPredictor())
    {
        solve
        (
            UEqn
         ==
            fvc::reconstruct
            (
                (
                    mixture.surfaceTensionForce()
                  - ghf*fvc::snGrad(rho)
                  - fvc::snGrad(p_rgh)
                ) * mesh.magSf()
            )
        );

        fvOptions.correct(U);
    }
