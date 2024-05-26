# Problem statement
- Modify a shape, a 3D geometry, so that it can be "formed" using Dual Sided Incremental Forming (DSIF) process.
- Given a non-self intersercting projectable surface, create a skirt so that the part can be manufactured using Dual Sided Incremental Forming (DSIF) process.. 

# Test case 1
- Input is a flat surface with two faces (shown in yellow). 
- Output is a skirted geometry that is smoothly attached to surface.

![197202176-8a861227-9371-49c5-9716-56cb05386655](https://github.com/paragpathak2006/Add_skirt_soln/assets/31978917/fd30cf87-c511-4703-b8a4-6716b845aafb)

# Test case 2
- Input is a complex geometry surface with 20,000 vertices. 
- Output is a skirted geometry that is smoothly attached to surface.

![1 -part-stl](https://user-images.githubusercontent.com/31978917/197202121-11ca0a4e-2b65-402b-9267-af730f192f7e.png)

## Parameters
To edit parameters, go to parameters.h in IO/ and set the following values.
-         step = 10: 1/2/4/5/10/20/25/50 factors of 100
-         slope = 4: For tangents of the Hermite curves
-         min_angle = 10: Minimum difference between two consecutive skirt boundary segments to split the node into multiple nodes
-         sprawl = 4- Increases the spread of the skirt 
-         tolerance = 1e-5: Tolenrece for point equivalency.

## Space map implementation
The space map implementation reduces the time complexity of the problem from O(n2) to O(n) enabling a fast topology generation from a point cloud into a fully connected watertight tessellation.

See [Header/IO/Finder.h](https://github.com/paragpathak2006/Add_skirt_soln/blob/main/Header/IO/Finder.h)

![space map](https://github.com/paragpathak2006/pmc/assets/31978917/9ec036a2-e23f-4409-a18d-8e86bcf129be)

## Running
- Two sample input parts (Parts.STL and Parts.txt) are in the Parts/ folder.
- Two sample outputs -stl-out (1 & 2) in the root folder provided.
- Run Debug/MachinaLabs.exe
- When prompted, please enter 1/2 to pick the sample input.
- Set the parameters in the parameters.h header


## Visualization project 
visit the following page for the visualization window project
[https://github.com/paragpathak2006/Add_skirt_soln_gui](https://github.com/paragpathak2006/Add_skirt_soln_gui)


 
