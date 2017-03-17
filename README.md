# AnimationAndSimulationProgramming2015-2016

##Bloke Rides Badger
You are to write a C++ application to display and animate the Badger entity as it moves around a
small, flat ground plane. The application must be written using the given framework available via
Blackboard. You should:
*Modify the given Badger class so that it displays the geometry at the correct locations, with the
correct hierarchical relationships, and with the given texture image (see table below). It should
be possible to move the entire Badger via the SetTransformation on its primary actor.
*Modify the BadgerRails class so that it directs the movement of the scene’s Badger instance to
move along the path using the given timings (see table below).
*Modify the Badger and BadgerRails classes so that the Badger’s subcomponents (e.g. wheels)
animate (e.g. spin, turn) appropriately in response to the motion.
*Modify the Badger class and/or create a Bloke class to represent the rider of the Badger. All the
Bloke’s subcomponents should be displayed using the correct hierarchical relationships (see
given data file). The Bloke should smoothly animate between poses as the Badger moves and
turns. The sitting posture is required but supporting the standing posture in addition is a bonus.
*Refactor your code to the highest quality you can.
*Document (in block code comments) which animation techniques are being used, how, and
explain the choices made to satisfy and implement the above requirements.


##Badger Sim
You are to complete a C++ application to simulate the interaction of Badger entities with their
environment as detailed below. The application must be written using the given framework
available via Blackboard. You should:
*Modify the MyPhysicsSystem and/or ToyDrone classes so that the drones move in response to
the forces applied to their physics representations (they should be projected up into the air with
a spiral motion) and are affected by gravity, drag and a wind vector.
*Modify the ToyDrone class so that the drones provide a fire / smoke trail when in motion.
*Modify the MyPhysicsSystem, and/or ToyDrone classes so that the Badger pushes the drones
when it collides with them.
*Refactor your code to the highest quality you can.
*Document (in block code comments) which simulation techniques are being used, how, and
explain the choices made to satisfy and implement the above requirements.
