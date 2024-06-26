#include "main.h"
#include <iostream>
using namespace std;


bool override = false;

bool isSkills = false;
bool isQuals = true;
bool isElims = false;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	pros::lcd::set_text(0, "Skills Run");
	isSkills = true;
	isElims = false;
	isQuals = false;	
}

void on_left_button() {
	pros::lcd::set_text(0, "Elims Run");
	isSkills = false;
	isElims = true;
	isQuals = false;	
}

void on_right_button() {
	pros::lcd::set_text(0, "Quals Run");
	isSkills = false;
	isElims = false;
	isQuals = true;	
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	drivetrainInitialize();
	// wingsInitialize();
	// armInit();
	// intakeInit();
	pros::lcd::register_btn1_cb(on_center_button);
	// pros::lcd::register_btn0_cb(on_left_button);
	// pros::lcd::register_btn2_cb(on_right_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	setChassisPose(0,0,0);
	// chassisMoveTo(0, 40, 5000);
	// chassisMoveTo(0, -40, 5000);
	// chassisMoveTo(0, 40, 5000);
	chassisTurnTo(20, 20, 100000, true);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off. lol
 */
void opcontrol() {
	while (true) {
		if (coachController.get_digital(pros::E_CONTROLLER_DIGITAL_L2) &&
			coachController.get_digital(pros::E_CONTROLLER_DIGITAL_R2) &&
			coachController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
				override = !override;
			}
		
		drivetrainPeriodic(override);
		// puncherPeriodic(override);
		// intakePeriodic(override);
		// wingsPeriodic(override);
		// armPeriodic(override);

		if (driverController.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
			autonomous();
		}
		

		pros::delay(10);
	}
	// pros::delay(20);
}



