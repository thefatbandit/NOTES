The main motive of tracking is to make the bot follow the discrete pose list, determined by 
a planning algorithm as efficiently as possible. Pure pursuit is a simple approach based on tracing 
all points by connecting them with arcs of appropriate radii. A look ahead distance is defined, which 
basically determines which discrete point in the pose list plays the role of the goal, i.e the other 
end of the arc apart from the current pose. The look ahead distance is chosen as proportional to 
velocity, and the proportionality constant is a parameter to be tuned. The value of k if very small 
leads to oscillatory behaviour but accurate following , whereas higher value of k causes smooth 
but inaccurate tracking that cuts corners. 
