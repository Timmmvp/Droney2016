#pragma once

/**
* Increase the score of found targets and mark the current location with the symbol for a found target
*/
void MarkTargetFoundRule();

/**
* contains the rule which alows the drone to return home when all targets are found
*/
void DroneAtHomeRule();

/**
* Contains the rule which gives the gamer a timepenalty when hitting a tree
*/
void DelayOnTreeHitRule();

/**
* Contains the rule which opens an crashdialog when the gamer hits a rock
*/
void RockCrashRule();

/**
* contains a rule which give the gamer an time bonus of 10 seconds
*/
void EnergyTargetRule();

/**
* contains the reset values 
*/
void ResetRule();

/**
* contains the rule which opens a dialog when the gamer is out of time
*/
void OutOfTimeRule();