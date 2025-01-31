#include "main.h"
#include "pros/llemu.hpp"

#define front_left 19
#define back_left 11
#define front_right -20
#define back_right -12

#define belt_port -13
#define intake_port 18



double speed = 1;

/**
 * New code to set speed variable
 * Center button prints current speed var
 * 
 * Thanks LLEMU
 * 
 * commented out becuase it was not necessary to keep
 */

/*
void on_left_button() {
	speed = speed - 0.10;
	pros::lcd::print(0, "Speed down");
	// printf ("left");
}

void on_right_button() {
	speed = speed + 0.10;
	pros::lcd::print(0, "Speed up");
	// printf ("right");
}
void on_center_button(){
	std::string speedStr = "Speed: ";
	speedStr.append(std::to_string(speed));
	pros::lcd::set_text(0, speedStr);
	// printf ("middle");
	// pros::lcd::print(0, "middle");
	
}
*/

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();

	pros::lcd::print(0, "Init Done!");

	//pros::lcd::register_btn0_cb(on_left_button); // THIS THROWS AN ERORR BUT WORKS FINE :)
	//pros::lcd::register_btn2_cb(on_right_button); // THIS THROWS AN ERORR BUT WORKS FINE :)
	//pros::lcd::register_btn1_cb(on_center_button); // this one doesnt throw an error. all 3 work but i might change this later :3
	

	// Motor Group Initiliazation

	

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

	pros::adi::Pneumatics net_piston('h', true); 

	pros::MotorGroup left_mg ({front_left, back_left});    // Creates a motor group with forwards ports 10 and 20
	pros::MotorGroup right_mg ({front_right, back_right});  // Creates a motor group with forwards port 1 and 11

	pros::Motor belt (belt_port);
	pros::Motor intake (intake_port);

	pros::Controller master(pros::E_CONTROLLER_MASTER);	// Creates a controller object for the master controller
	
	intake.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	

	while (true) {

		//MOVE ALL OF THESE INTO FUNCTIONS LATER

		if (master.get_digital(DIGITAL_L2))
		{
			belt.move(85);
		}
		else if (master.get_digital(DIGITAL_L1))
		{
			belt.move(-85);
		}
		else
		{
			belt.brake();
		}


		if (master.get_digital(DIGITAL_R2))
		{
			intake.move(-127);
		}
		else if (master.get_digital(DIGITAL_R1))
		{
			intake.move(127);
		}
		else
		{
			intake.brake();
		}

		

		if (master.get_digital(DIGITAL_X))
		{
			net_piston.toggle();
		}


		// Tank Drive
		int left = speed * master.get_analog(ANALOG_LEFT_Y);    // Gets the left joystick data and drives the motors
		int right = speed * master.get_analog(ANALOG_RIGHT_Y);  // Gets the right joystick data and drives the motors
		left_mg.move(left);	// Sets left motor voltage
		right_mg.move(right);	// Sets right motor voltage
		pros::delay(20);	// Run for 20 ms then update
	}
	
}
