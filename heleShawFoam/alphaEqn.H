{
    // Updating alpha1
    #include "alphaSuSp.H"
    advector.advect(Sp, Su);

    #include "rhofs.H"
    rhoPhi = advector.getRhoPhi(rho1f, rho2f);

    alpha2 = 1.0 - alpha1;
    mixture.correct();
}

scalar domainFraction = 0;

domainFraction = alpha1.weightedAverage(mesh.Vsc()).value();

Info<< "Phase-1 volume fraction = "
    << domainFraction
    << "  Min(" << alpha1.name() << ") = " << min(alpha1).value()
    << "  Max(" << alpha1.name() << ") = " << max(alpha1).value()
    << endl;
