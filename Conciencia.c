// Code by Polilla - github.com/ReyPolilla17
#pragma config(Sensor, S1,     			Distance,      sensorEV3_Ultrasonic)
#pragma config(Sensor, S2,   			Gyro,          sensorEV3_Gyro)
#pragma config(Motor,  motorB,          Lmotor,        tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          Rmotor,        tmotorEV3_Large, PIDControl, driveRight, encoder)
#pragma config(Motor,  motorD,          Amotor,        tmotorEV3_Medium, PIDControl, encoder)

task main() {
	bool firstTime = true;
	int turn = 1;

	while(true) {
		resetGyro(S2);
		sleep(200);

		moveMotorTarget(motorD, 90, 50);
		waitUntilMotorStop(motorD);

		repeatUntil(getUSDistance(S1) <= 16) {
			setMotorSpeed(motorB, 50);
			setMotorSpeed(motorC, 50);
		}

		setMotorSpeed(motorB, 0);
		setMotorSpeed(motorC, 0);

		moveMotorTarget(motorD, -90, -50);
		waitUntilMotorStop(motorD);

		resetGyro(S2);
		sleep(200);


		if(turn == 1) {
			repeatUntil(getGyroDegrees(S2) >= 90) {
				setMotorSpeed(motorB, 50);
				setMotorSpeed(motorC, 0);
			}
		} else {
			repeatUntil(getGyroDegrees(S2) <= -90) {
				setMotorSpeed(motorB, 0);
				setMotorSpeed(motorC, 50);
			}
		}

		setMotorSpeed(motorB, 0);
		setMotorSpeed(motorC, 0);

		resetGyro(S2);
		sleep(200);

		if(firstTime == true && getUSDistance(S1) < 10) {
			repeatUntil(getGyroDegrees(S2) <= -90) {
				setMotorSpeed(motorC, 0);
				setMotorSpeed(motorB, -50);
			}

			setMotorSpeed(motorB, 0);
			setMotorSpeed(motorC, 0);

			resetGyro(S2);
			sleep(200);

			repeatUntil(getGyroDegrees(S2) <= -90) {
				setMotorSpeed(motorC, 50);
				setMotorSpeed(motorB, 0);
			}

			setMotorSpeed(motorB, 0);
			setMotorSpeed(motorC, 0);

			resetGyro(S2);
			sleep(200);

			turn = turn * -1;
			firstTime = false;
		}

		if(getUSDistance(S1) < 10 && firstTime == false) return;

		if(turn == 1) {
			repeatUntil(getGyroDegrees(S2) >= 90) {
				setMotorSpeed(motorB, 50);
				setMotorSpeed(motorC, 0);
			}
		} else {
			repeatUntil(getGyroDegrees(S2) <= -90) {
				setMotorSpeed(motorB, 0);
				setMotorSpeed(motorC, 50);
			}
		}

		setMotorSpeed(motorB, 0);
		setMotorSpeed(motorC, 0);

		firstTime = false;
		turn = turn * -1;
	}
}
