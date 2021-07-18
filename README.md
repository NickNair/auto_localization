# Auto Localization

With the use of the ROS framework the basic functionalities of mapping,localization and navigation shallbe achieved for an Autonomous Mobile Robots (AMR).In the real world scenario,there are a number of issues which are not completely handled in the widely available open source modules.The following scenariois an example for the same.Whenever an AMR is powered on within a known environment(with map), the first step is localization.That is informing the AMR it’s current location with reference to the existing map.Basedonhow good the initial localization estimation is,thefurther navigational performance varies.Hence thisis avery important step for any AMR .But doing a manual localization every time could bea tedious task.So why don’t we think of a better alternative? Which could auto localize itself fromthe last known position.

## What does this package do ?

This is a C++ based software module that shall be having the following functionalities
- Updating the last known position of the AMR into a local text file.
- Whenever the navigation modules are re-launched ,the localization should happen from the last known position.That’s the last known coordinates shouldbe read from the local text file and usethat for initialization of AMR.
