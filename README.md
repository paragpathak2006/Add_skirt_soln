# CompGeo_Add_Skirt
## Objective
Modify a shape, a 3D geometry, so that it can be "formed" using our Dual Sided Incremental Forming (DSIF) process. 
![part](https://user-images.githubusercontent.com/91622575/174192157-156584d2-d93a-4f78-82be-a0dac1bf1511.jpg)
## Context
At Machina Labs, we use our robots to push, stretch, bend and fold flat sheets of metal into various shapes. This "forming" process results in the originally flat sheet of metal, now having a 3D shape protruding out of it. Typically, the desired "part" is only a portion of the protruding shape, and which eventually gets cut out of it. 
![shell](https://user-images.githubusercontent.com/91622575/174192225-2b79b4db-ca1a-49fd-8f09-474ac96e5fb6.jpg)


To be "formable" or manufacturable using our DSIF process, the geometry must resemble a protrusion off a flat surface - meaning, all its edges must end in a single plane. Typically however, the parts required by our clients do not satisfy this requirement! So, in order to make it manufacturable, the "part" geometry provided to us by clients must be adapted. The process of adapting the given geometry is to first, reorient the geometry to be optimal for the following steps. Next, project edges of the geometry onto a flat surface. This creates extension surfaces with edges ending in a single plane. The edges thus extended with the new surfaces, fulfil the criteria of being a protrusion. However, this surface will need additional modifications as explained below. Such an extension surface is what we call a "skirt" - for obvious reasons.


In addition to ending in a single plane, an ideal manufacturable surface typically has a draft, or is slanted less than 90 degrees towards the bottom. Typically the transition from part surface to extended surface, over the original edge, causes a change in direction. For manufacturability, it is best for the newly added skirt surface to extend smoothly beyond the edge of the orignal part. Often this can be achieved by orienting the part optimally before extending its edges. As such, to be manufacturable, there are several other requirements and constraints - but those are beyond the scope of this assignment.
## Task
Create a program that...
- Takes in a 3D geometry in form of a .STL file. Use provided file - part.STL.
- Programmatically adds a "skirt" to the provided 3D geometry.
- Outputs a new .STL file - part_skirted.STL.
## Requirements
- The program can be a simple command line script, or optionally include a user-friendly GUI.
- Develop using your language of choice (we prefer Python).
- Constraint: The newly added surfaces will have a slant no greater than 70 degrees to the horizontal.
- Challenge: Keep the change in direction, from part surface to extension surface, as close to 0 degrees as possible.
- If necessary, the provided geometry (part.STL) may be re-oriented, using other available tools, before being used as input to your program.
- The deliverables must include documentation and all artifacts necessary to setup and run the program.
- To enable review, deliverables must include code - not just executables. And per good programming practices, must be sufficiently documented for ease of understanding.
## Optional Challenge (any or all of the features for bonus points)
- Update your program to accept any .STL file and output a skirted geometry.
- Create a GUI that includes display windows to visualize the input and output geometries.
- Make the visualization window interactive, allowing user to manipulate the displayed image in the window.
- Allow user to re-orient and update the input geometry.
- Add user controls so the constraints can be adjusted and applied to update output geometry.
## Submission
In order to submit the assignment, do the following:

1. Navigate to GitHub's project import page: [https://github.com/new/import](https://github.com/new/import)

2. In the box titled "Your old repository's clone URL", paste the homework repository's link: [https://github.com/Machina-Labs/network_com_hw](https://github.com/Machina-Labs/network_com_hw)

3. In the box titled "Repository Name", add a name for your local homework (ex. `network_com_soln`)

4. Set privacy level to "Public", then click "Begin Import" button at bottom of the page.

5. Develop your homework solution in the cloned repository and push it to Github when you're done. Extra points for good Git hygiene.

6. Send us the link to your repository.
