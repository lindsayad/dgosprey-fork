DGOSPREY
=====
Discontinuous Galerkin Off-gas SeParation and REcoverY model

Cloned from: [https://github.com/aladshaw3/dgosprey](https://github.com/aladshaw3/dgosprey/)

This is a MOOSE application designed to simulate mass and energy transport of gases through a packed-bed column reactor. It uses DG kernels to ensure conservation of mass and energy for problems that are highly advectively dominant, but does not currently employ any form of slope limiters to correct the over-shoot under-shoot problems that are notorious in finite element methods. As a consequence, the solutions tend to be oscillatory around the wave fronts as the various concentration profiles move through the bed. 

This is an unfinished application. Use with caution.

"Fork Dgosprey" to create a new MOOSE-based application.

For more information see: [http://mooseframework.org/create-an-app/](http://mooseframework.org/create-an-app/)
