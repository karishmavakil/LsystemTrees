# Using L-systems to Model Trees

A project based on procedural methods in computer graphics, which are commonly used to replicate entities like cities and landscapes for virtual environments. 
Procedural methods describe these entities using semantic sequences of instructions which generate visually complex images on demand, as opposed to the conventional method of saving images as pieces of data and recalling them from memory when required 
This application uses the procedural methods of L-systems, a type of formal grammar, to create complex 3D models of botanical trees.
L-systems, or Lindenmayer systems are similar to conventional formal grammars, except all the rules are applied simultaneously in every iteration.
The L-system is used as the basis for creating branching patterns. The user inputs an L-system in a text file in JSON format along with various geometric parameters and texture images for leaves and wood, which is transformed into a 3D model.
The 3D model can be viewed from all directions and zoomed in/out using arrow keys.

Different types of L-systems for eg. Bracketed, Parametric, Conditional, Stochastic and Context-sensitive L-systems have their own connections with plant modelling.
The application supports L-systems with any mix of these features. An input file with ~40 lines is transformed to a 3D model with ~2 million vertices, thus showcasing the paradigm of data amplification - creating large entities with small input.

## Example Input
```javascript
{
    "branchRadius" : 0.2,
    "branchStep" : 0.75,
    "branchAngle" : 0.4,
    "branchThicknessRatio" : 0.8,
    "branchStepRatio" : 0.9,
    "minRadius" : 0.00,
    "maxLeafRadius" : 0.12,
    "leafLength" : 0.4,
    "leafWidth" : 0.4,
    "leafDensity" : 8,
    "leafTextureFile" : "m.bmp",
    "woodTextureFile" : "woodtexture.bmp",
    "Turtle": {
        "x": 0,
        "y": -6,
        "z": 0
    },
    "LSystem": {
        "Start": "F{5}",
        "Rules" : [{
                   "Input" : "F{x}",
                   "Output" : "B{x / 2}[&{1.5}/B{x / 4}^{1.5}B{x / 4}]B{x / 2}[+{1.2}B{x / 5}-{1.5}B{x / 5}]&{0.5}B{x / 2}[&{2}/F{x - 0.1}^{1.5}F{x - 0.1}]^[++{1.2}F{x - 0.1}-{1.5}F{x - 0.1}][--F{x - 0.1}+F{x - 0.1}]B{x / 2}[^{1.5}/F{x - 1}&\\F{x - 0.1}]^+{1.5}B{x / 2}[^F{x - 0.1}-/F{x - 0.1}]\\[&{4}F{x - 0.1}-/F{x - 0.1}]",
                   "Condition" : "x >= 4.9"
                   },
                   {
                   "Input" : "F{x}",
                   "Output" : "/+{0.9}\\F{x - 0.1}-{0.9}F{x - 0.1}",
                   "Condition" : "x == 4.8",
                   "Probability" : 0.6
                   },                   {
                   "Input" : "F{x}",
                   "Output" : "/F{x - 0.1}&{0.9}\\F{x - 0.1}^{0.9}F{x - 0.1}",
                   "Condition" : "x == 4.8",
                   "Probability" : 0.4
                   },
                   {
                   "Input" : "F{x}",
                   "Output" : "F{x - 1}[/+F{x - 1}\\&{0.9}F{x - 1}][\\&F{x - 1}^F{x}]",
                   "Condition" : "x < 4.8"
                   }]
    },
    "iterations" : 5
}
```

## Example Screenshots of Models

### Birch Tree Model: Recreation from Photo

<img src="https://github.com/karishmavakil/LsystemTrees/blob/master/LsystemTrees/treemodels/birchRecreation.png" alt="birch" width="700"/>

### Pine Tree Model: Recreation from Photo
<img src="https://github.com/karishmavakil/LsystemTrees/blob/master/LsystemTrees/treemodels/pineRecreation.png" alt="p" width="700"/>

### Birch Tree Model: Recreation from Photo
<img src="https://github.com/karishmavakil/LsystemTrees/blob/master/LsystemTrees/treemodels/mapleRecreation.png" alt="m" width="700"/>

### Models created by varying Geometric Parameters for a fixed L-system 
<img src="https://github.com/karishmavakil/LsystemTrees/blob/master/LsystemTrees/treemodels/changingGeometricParameters1.png" alt="g" width="700"/>
<img src="https://github.com/karishmavakil/LsystemTrees/blob/master/LsystemTrees/treemodels/changingGeometricParameters2.png" alt="g" width="700"/>

### Stochastic Models created using Multiple Executions of fixed Stochastic L-system
<img src="https://github.com/karishmavakil/LsystemTrees/blob/master/LsystemTrees/treemodels/stochasticLsystem.png" alt="s" width="700"/>

### Miscellaneous Models
<img src="https://github.com/karishmavakil/LsystemTrees/blob/master/LsystemTrees/treemodels/canopy.png" alt="c" width="700"/>
<img src="https://github.com/karishmavakil/LsystemTrees/blob/master/LsystemTrees/treemodels/windswept.png" alt="w" width="700"/>

