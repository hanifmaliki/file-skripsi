<?php
include_once('fungsi.php');

if($_GET['gndacc'] != '' and $_GET['angle'] != '' and $_GET['drift'] != '' and
   $_GET['pga'] != '' and $_GET['anglepeak'] != '' and $_GET['height'] != '' and
   $_GET['displacepeak'] != '' and $_GET['driftpeak'] != '' and
   $_GET['pgadr1'] != '' and $_GET['score'] != '' and $_GET['command'] != '') {
	$gndacc = $_GET['gndacc'];
	$angle = $_GET['angle'];
	$drift = $_GET['drift'];
	$pga = $_GET['pga'];
	$anglepeak = $_GET['anglepeak'];
	$height = $_GET['height'];
	$displacepeak = $_GET['displacepeak'];
	$driftpeak = $_GET['driftpeak'];
	$pgadr1 = $_GET['pgadr1'];
	$score = $_GET['score'];
	$command = $_GET['command'];

	// Create connection
	$conn = new mysqli($servername, $username, $password, $dbname);
	// Check connection
	if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	}

	//-------------Tulis data ke botdata
	$sql = "INSERT INTO botdata (gndacc, angle, drift, pga, anglepeak, height, displacepeak, driftpeak, pgadr1, score)
	VALUES ('" . $gndacc . "', '" . $angle . "', '" . $drift . "', '" . $pga . "', '" . $anglepeak . "',
			'" . $height . "', '" . $displacepeak . "', '" . $driftpeak . "', '" . $pgadr1 . "', '" . $score . "')";

	if ($conn->query($sql) === TRUE) {
		echo "New record created successfully";
	} else {
		echo "Error: " . $sql . "<br>" . $conn->error;
	}
	//------------------------------------

	//------------------Ambil data command
	$last_reading = getLastCommand();
    $last_reading_command = $last_reading["command"];
	
	if ($last_reading_command!='x') {
		if ($command=='x') {
			$sql = "INSERT INTO botcommand (command)
			VALUES ('" . $command . "')";

			$conn->query($sql);
			$last_reading_command='x';
		}
	}
	//------------------------------------

	//---------------------Ambil data time
	$last_reading = getLastReadings();
    $last_reading_time = $last_reading["time"];
	//------------------------------------
	
	//----------------Ambil data top angle
	$last_reading = getLastReadings2();
    $last_reading_anglepeak2 = $last_reading["anglepeak"];
	//------------------------------------

	echo "<br>Command&Time&TopAngle: *";
	echo $last_reading_command;
	echo "*";
	echo $last_reading_time;
	echo "*";
	echo $last_reading_anglepeak2;
	echo "#";

	$conn->close();
}
else {
	echo "Data sensor kurang!";
}