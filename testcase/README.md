## Test Cases for heleShawFoam Solver

### Overview
This directory contains a test case for the `heleShawFoam` solver, designed for simulating displacement flows of non-Newtonian power-law fluids in Hele-Shaw geometries.

### Mesh Generation
To generate the mesh, use the provided Python script `rectangular_duct.py`:

1. Run the following command to create the `blockMeshDict` file:
   ```bash
   python rectangular_duct.py > system/blockMeshDict
   ```

2. Once the mesh file is generated, execute the following commands to build the mesh and initialize the simulation:
   ```bash
   blockMesh
   setFields
   heleShawFoam
   ```

### Modifying Simulation Parameters

#### Flow and Boundary Conditions
Flow and boundary conditions can be modified by editing the files located in the `0/` directory. Each file corresponds to different fields.

#### Fluid Properties
Fluid properties, such as viscosity and density, can be adjusted in the `transportProperties` file located in the `constant/` directory.

#### Simulation Control
Simulation settings, including start time, end time, and time step size, can be modified in the `controlDict` file located in the `system/` directory.

#### Field Information
Field information used by `setFields` can be modified in the `setFieldsDict` file to specify the initial conditions and other field settings.

### Parallel Computing
The `heleShawFoam` solver can be executed with parallel computing capabilities. Additional features for parallel execution have been integrated. While this feature is not included in the test case, it can be easily implemented. To run the simulation in parallel, ensure that the domain is decomposed using `decomposePar` before running the solver.

#### Example Command for Parallel Execution
To run the solver in parallel, use the following commands:
```bash
decomposePar
mpirun -np <number_of_processes> heleShawFoam
```
Replace `<number_of_processes>` with the number of parallel processes.


