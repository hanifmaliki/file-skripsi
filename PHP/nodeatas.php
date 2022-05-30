<?php
include_once('fungsi.php');

if($_GET['pidCal'] != '' and
   $_GET['axOff'] != '' and $_GET['ayOff'] != '' and $_GET['azOff'] != '' and
   $_GET['gxOff'] != '' and $_GET['gyOff'] != '' and $_GET['gzOff'] != '') {
	$pidCal = $_GET['pidCal'];
	$axOff = $_GET['axOff'];
	$ayOff = $_GET['ayOff'];
	$azOff = $_GET['azOff'];
	$gxOff = $_GET['gxOff'];
	$gyOff = $_GET['gyOff'];
	$gzOff = $_GET['gzOff'];
	
	if ($pidCal=='1') {
		$conn = new mysqli($servername, $username, $password, $dbname);
		if ($conn->connect_error) {
			die("Connection failed: " . $conn->connect_error);
		}

		$sql = "INSERT INTO topcalib (pidCal, axOff, ayOff, azOff, gxOff, gyOff, gzOff)
		VALUES ('" . $pidCal . "', '" . $axOff . "', '" . $ayOff . "', '" . $azOff . "',
				'" . $gxOff . "', '" . $gyOff . "', '" . $gzOff . "')";

		$conn->query($sql);
	
		$conn->close();
	}
}

if($_GET['angle'] != '' and $_GET['anglepeak'] != '' and $_GET['command'] != '') {
	$angle = $_GET['angle'];
	$anglepeak = $_GET['anglepeak'];
	$command = $_GET['command'];

	$conn = new mysqli($servername, $username, $password, $dbname);
	if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	}

	//--------------Tulis data ke topdata
	$sql = "INSERT INTO topdata (angle, anglepeak)
	VALUES ('" . $angle . "', '" . $anglepeak . "')";

	if ($conn->query($sql) === TRUE) {
		echo "New record created successfully";
	} else {
		echo "Error: " . $sql . "<br>" . $conn->error;
	}
	//------------------------------------

	//------------------Ambil data command
	$last_reading = getLastCommand2();
    $last_reading_command = $last_reading["command"];
	
	if ($last_reading_command!='x') {
		if ($command=='x') {
			$sql = "INSERT INTO topcommand (command)
			VALUES ('" . $command . "')";

			$conn->query($sql);
			$last_reading_command='x';
		}
	}
	//------------------------------------

	//---------------------Ambil data time
	$last_reading = getLastReadings2();
    $last_reading_time = $last_reading["time"];
	//------------------------------------

	echo "<br>Command&Time: *";
	echo $last_reading_command;
	echo "*";
	echo $last_reading_time;
	echo "#";

	$conn->close();
}
else {
	echo "Datas sensor kurang!";
}