The subsytems class contains all of the other moving and mechanical parts other than the drivetrain. This includes the hoist system, intake, and the intake helper allowing the intake to expand diameter. Debugging solutions have been added to make sure you know what's going wrong when something's going wrong.

The intake is made up by two 5.5 VEX V5 Smart Motors set at 200RPM. The helper intake is made up by 2 pistons, a 50mm and a 75mm. Both pistons exert enough force (calculations are in CAD) to move the intake outside. 

The Hoist system is made up by 4 VEX V5 Smart Motors tuned at 200RPM with a total wattage of 22W (may have to edit later) with a PID proportion set of 4.1 and integral point disabled due to the derivative actually leveling most of the work.

The flap system that raises the flap to redirect blocks out or in the hogger is powered by a 100mm 2 stroke PSI tuner, due to the amount of force needed to push the object. 

The Intake and the Chain Hoist are connected to run on one button, meaning that both systems will activate as long as the button is held. The controller assignments for the scoring methods are as follows:

- L2 set as top Rack (long goal)
- R2 set as bottom Rack (center goal lower)
- L1 set as Middle Rack (center goal)
- R1 set as hoarding (basket)

Pneumatic Stroke controls are also as follows:
- Button B set as intake pneumatics toggle (on or off, both controlled at the same time)
- Button X set as button to toggle Flap pneumatic (on or off toggle)

