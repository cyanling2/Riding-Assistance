# Riding-Assistance


 
  
AUTOBRAKING SYSTEM 
By 
Gary Gong 
Taiqing Ling 
Weichen Qi 
Final Report for ECE 445, Senior Design, Spring 2021 
TA: Xihang Wu 
01 May 2021 
Project No. 50 
ii 
Abstract 
We designed and built a system that could automatically detect the STOP signs ahead the bicycle and 
alert the rider to stop the bicycle. If no action is taken by the rider, our system will smoothly and safely 
auto-trigger the bicycle’s brake system and force it to halt. We hope our project could help bicycle riders 
to be more aware of the importance of STOP signs in the street and protect the safety of themselves 
and other vehicle drivers. In this paper, the detailed design ideas, block diagrams, function of each 
modules, future modifications and the general cost of the device will be presented. 
  
iii 
Contents 
1. Introduction .............................................................................................................................................. 1 
1.1 Visual Aid ............................................................................................................................................. 1 
2 Design ......................................................................................................................................................... 3 
2.1 High Level Requirements .................................................................................................................... 3 
2.2 Block Diagram ..................................................................................................................................... 3 
2.3 Subsystems and Modules ................................................................................................................... 4 
2.3.1 Power Supply Module .................................................................................................................. 4 
2.3.2 Microcontroller and Raspberry Pi Module .................................................................................. 5 
2.3.3 Electromagnet Auto-Brake Module ............................................................................................. 5 
2.3.4 XBEE Module ................................................................................................................................ 6 
2.3.5 Helmet Module ............................................................................................................................ 7 
2.3.6 Hall Effect Sensor ......................................................................................................................... 7 
2.3.7 Final PCB Designs ......................................................................................................................... 8 
2.4 Template Match Algorithm ................................................................................................................. 8 
2.4.1 Selection of Templates ............................................................................................................... 8 
2.4.2 Pseudo Codes .............................................................................................................................. 9 
3. Design Verification .................................................................................................................................. 10 
4. Costs ........................................................................................................................................................ 11 
4.1 Parts .................................................................................................................................................. 11 
5. Conclusion ............................................................................................................................................... 12 
5.1 Accomplishments .............................................................................................................................. 12 
5.2 Uncertainties ..................................................................................................................................... 12 
5.3 Ethical considerations ....................................................................................................................... 13 
5.4 Future work ....................................................................................................................................... 13 
Références .................................................................................................................................................. 15 
Appendix A Requirement and Verification Table ................................................................................... 16 
 
 
 
1 
1. Introduction 
The purpose of our project is to improve the safety of bicyclists and, at the same time, reduce the STOP 
sign violation rate in the traffic laws. Currently, the traffic laws for bicycles are relatively not 
comprehensive enough, which leaves potentially unsafety for bicyclists. In 2018, 857 people in the 
United States died in bicycle accidents. That number was the highest since 1990 [1]. In 2016, about 71% 
of deaths due to bicycle accidents occurred in urban areas and 30% occurred at intersections [2]. It was 
recommended that all bicyclists should wear a helmet but no state has so far announced such a law to 
rule that, which caused the tragedies.  
Furthermore, as one of the important methods of transportation in the world, the bicycle has never 
acquired equal attention to its development as other vehicles, like the car and the motorcycle. While 
autonomous driving has become a mainstream in the development of vehicles, many cars have installed 
intelligent driving assistance like lane-keeping, blind-spot detector, auto-parking. Motorcycles also have 
riding assistance products. All these products help avoid traffic accidents and therefore protect drivers 
and riders. However, similar kinds of products are barely seen on bicycles. 
Our solution was to create a riding assist for bicycles and thus lower the risk of a bicycle accident at 
crossing roads. In this project, we plan to build an autobrake system that will force the bicycle to stop at 
STOP signs. The STOP sign is such an important traffic signal that anyone who learns to drive will be 
taught about rules relevant to it. However, bicyclists in most countries do not need a license to ride 
legally and thus may lack such kind of safety awareness. Therefore, this project will help solving this 
problem in two directions in general: first, reminding the bicyclists about the STOP sign; second, forcing 
the brake if no action is taken, which means the bicyclists does not take any action to slow down. Finally, 
the product should be easy to install and have an affordable price. 
1.1 Visual Aid 
The basic design of our project is presented in a simple drawing below. To make the design capable of all 
our intended functions, we must use two separate parts individually: a bicycle part that contains most of 
the system, and a helmet part which will only be used to alert the bicyclists about STOP sign. 
We will install a camera module as an ‘eye’ on the bicycle to capture frontier images as well as a hall-
effect sensor on the wheel for speed measurement. These two sensors are wired and will be wireless 
connected to the speaker on the helmet. Once the camera detects a STOP sign, the speaker will 
generate warning sounds as a reminder. Then, when the STOP sign is closed enough, if still no action has 
been taken by the bicyclist, in which case the speed of the bicycle is not slowing down, the autobrake 
device will be triggered to force the bicycle to stop. An electromagnet will be used to clamp the 
handlebar of the bicycle. There will also be a button whose execution is of the highest priority to turn 
on/off the autobrake system. This is especially designed to prevent accidents due to false positives, so 
that if the autobrake is triggered under inappropriate conditions, the bicyclist can turn it off manually 
and keep riding forward. This button will be installed on the PCB and thus can be easily accessed by the 
bicyclist. 
 
2 
 
Figure 1 Simple Visual Aid for the design 
  
 
3 
2 Design 
2.1 High Level Requirements 
Based on our design intention, the project time scale, and the budget given, we listed three high level 
requirements as the accomplishment sign of the project: 
1. The speaker must ring for three seconds to remind the bicyclist when a STOP sign shows up within 
15 meters in the front. 
2. While the STOP sign is within 5 meters, the autobrake must be triggered if and only if the speed of 
the bicycle is above 10km/h. 
3. The false-alarm rate must be no more than 15% and the autobrake can be disabled with one-click to 
avoid accidents due to false-alarms. 
2.2 Block Diagram 
 
Figure 2 Block Diagram 
