## heleShawFoam: 2D OpenFOAM code for simulating power-law fluids displacement in hele-shaw cells.

### Overview

This repository contains the 2D OpenFOAM code developed for simulating displacement flows of non-Newtonian power-law fluids in Hele-Shaw geometries. The code is based on the methodology outlined in the article titled "Numerical Modeling of Fluid Displacement in Hele-Shaw Cells: A Gap-Averaged Approach for Power-Law and Newtonian Fluids" and has been validated against 3D direct numerical simulations (DNS) and experimental data.

### Features

- 2D gap-averaged model implementation for power-law fluids.
- Ability to simulate various displacement configurations.
- Validated against experimental results for accurate interface morphology and dynamics.
- Computationally efficient, achieving significant speed improvements over 3D models.

### Installation

To use the code, you will need to have OpenFOAM installed on your system. Follow the instructions below to set up the environment:

1. Clone this repository:
   ```bash
   git clone https://github.com/feebsssz/heleShawFoam.git
2. Navigate to the directory:
   ```bash
   cd heleShawFoam
* Ensure that OpenFOAM is properly set up and source the OpenFOAM environment:
   ```bash
   source /path/to/openfoam/etc/bashrc
3. Compile the solver:
    ```bash
    wmake

### Post-Installation
After installing heleShawFoam and setting up the environment, navigate to the `testcase` directory where example cases are provided. You can modify the input parameters based on your simulation needs. For details of the cases and settings, please refer to the README file in the `testcase` directory.

### License
This project is licensed under the MIT License.

### Contact
For questions or comments, please reach out to:

Yao Zhang: yao.zhang@uis.no





