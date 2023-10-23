# Asteroids

![Asteroids! Pew pew!](https://github.com/RaduHaulica/asteroids/blob/20a36842d815196270465a7a787661e595ff7f6b/asteroids/assets/asteroids%20main.gif)

Classic game, fight inertia and shoot all the space boulders to win.

Boulders are almost randomly generated (factory), when you shoot one it breaks into two smaller ones with some special effects (particle systems). Game events (shooting, making rocks, explosions) are handled through a message queue.

Collisions are calculated using the Minkowski difference of the convex hulls of the entities being checked. If the Minkowski difference of two convex polygons contains the origin then the polygons overlap. Since that can get computationally intensive when the screen grows cluttered, i do a wide phase check based on distance between entities and only get into the more intensive stuff where it makes sense.

When you clear the entire screen the high score (time elapsed since start) is saved to a file if it beats the previous best time.

I also created a debug mode to better highlight collision processing by rendering the collider components (green color) on game entities and the minkowski differences (blue color) for narrow phase collision tests.

![Asteroids debug mode highlighting collider components](https://github.com/RaduHaulica/asteroids/blob/20a36842d815196270465a7a787661e595ff7f6b/asteroids/assets/asteroids%20debug.gif)

## How to use

Steer the ship with the arrow keys, press Space to shoot lasers at the boulders to destroy them. 

ESC restarts the game, and holding ESC quits the game.

Press F1 to enter debug mode and show colliders.
