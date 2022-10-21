# Add_skirt_soln

- Two sample input parts (Parts.STL and Parts.txt) are in Parts/ folder.
- Two sample outputs -stl-out (1 & 2) in root folder provided.
- When promted, please enter 1/2 to pick the sample input. 
## Parameters
-         step = 10: 1/2/4/5/10/20/25/50 factors of 100
-         slope = 4: For tangents of the hermite curves
-         min_angle = 10: Minimum difference between two consecutive skirt boundary segments to split the node into multiple nodes
-         sprawl = 4- Increases the spread of the skirt 
-         tolerence = 1e-5: Tolenrece for point equivalency.


- Part.txt: a simple 2 faces tessalation 
![2 -part-txt-stl](https://user-images.githubusercontent.com/31978917/197202176-8a861227-9371-49c5-9716-56cb05386655.png)
- Part.STL: The given sample part to tessalate
- ![1 -part-stl](https://user-images.githubusercontent.com/31978917/197202121-11ca0a4e-2b65-402b-9267-af730f192f7e.png)

