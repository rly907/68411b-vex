#include "main.h"

int speed = 1;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_left_button() {
	speed = speed - 0.10;
	pros::lcd::print(0, "Speed down");
}

void on_right_button() {
	speed = speed + 0.10;
	pros::lcd::print(0, "Speed up");
}
void on_center_button(){
	std::string speedStr = "Speed: ";
	speedStr.append(std::to_string(speed));
	// pros::lcd::print(0, std::to_string(speed));
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();

	pros::lcd::print(0, "Init Done!");

	pros::lcd::register_btn0_cb(on_left_button);
	pros::lcd::register_btn2_cb(on_right_button);
	pros::lcd::register_btn1_cb(on_center_button);
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
void autonomous() {}

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
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	/*
	pros::Motor front_left (10);
	pros::Motor back_left (20);
	pros::Motor front_right (1);
	pros::Motor back_right (11);
	*/

	pros::MotorGroup left_mg ({10, 20});    // Creates a motor group with forwards ports 10 and 20
	pros::MotorGroup right_mg ({1, 11});  // Creates a motor group with forwards port 1 and 11
	

	while (true) {
	

		// Motor Temperature Warning
		/*
		if (front_left.is_over_temp() || back_left.is_over_temp()){
			master.print(0,0,"Left motor overheat");
		}
		if (front_right.is_over_temp() || back_right.is_over_temp()){
			master.print(0,0,"Right motor overheat");
		}
		*/
		

		// Tank Drive
		int left = speed * master.get_analog(ANALOG_LEFT_Y);    // Gets the left joystick data and drives the motors
		int right = -1 * speed * master.get_analog(ANALOG_RIGHT_Y);  // Gets the right joystick data and drives the motors
		left_mg.move(left);	// Sets left motor voltage
		right_mg.move(right);	// Sets right motor voltage
		pros::delay(20);	// Run for 20 ms then update
	}
	
}