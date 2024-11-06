"""
Script to generate structured mesh for a cylinder, with grading towards the wall.
Edit the input parameters, then run:
        python rectangular_duct.py > system/blockMeshDict
"""
from string import Template
from math import sin,cos,radians,pi,sqrt

def create_dict(*args):
  return dict({i:eval(i) for i in args})


# ---- Input parameters ----
# Geometry
a = 0.12       # Width 
b = 0.0007     # Gap
H = 0.75       # Length

# Mesh size
NPA = 40    # Number of cells in the tangential direction for each block
# 2D!
NPB = 1     # Number of cells from square to perimeter in radial direction
NPZ = 40     # Number of cells from top to bottom

a2=a/2
b2=b/2

d=create_dict('H','NPA','NPZ','NPB','a','b','a2','b2')

t = Template("""
/*--------------------------------*- C++ -*----------------------------------*\
| =========                 |                                                 |
| \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |
|  \\    /   O peration     | Version:  8                                     |
|   \\  /    A nd           | Web:      www.OpenFOAM.org                      |
|    \\/     M anipulation  |                                                 |
\*---------------------------------------------------------------------------*/
FoamFile
{
    version     8;
    format      ascii;
    class       dictionary;
    object      blockMeshDict;
}

convertToMeters 1.0;

vertices
(
 ( $a2 -$b2 0)  // 0
 (-$a2 -$b2 0)  // 1
 (-$a2  $b2 0)  // 2
 ( $a2  $b2 0)  // 3

 ( $a2 -$b2 $H)  // 4
 (-$a2 -$b2 $H)  // 5
 (-$a2  $b2 $H)  // 6
 ( $a2  $b2 $H)  // 7

 
);				

blocks
(

 hex ( 1 0 3 2 5 4 7 6) ($NPA $NPB $NPZ) simpleGrading ( 
    (   (0.2 0.25 4)
        (0.6 0.5  1)
        (0.2 0.25 0.25))
    1 1)


);

edges
(

);

patches
(

 patch top
 (
  (4 5 6 7)
 )

 empty frontAndBack
 (
  (0 1 5 4)
  (2 3 7 6)
 )

 wall side
 (

  (1 2 6 5)
  (3 0 7 4)
 )

 patch inlo
 (
  (0 1 2 3)
 )
 
 

);

"""
)

print(t.substitute(d))
