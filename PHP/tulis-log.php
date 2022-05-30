<?php
include_once('fungsi.php');

if($_GET['accpeak'] != '' and $_GET['anglepeak'] != '' and
   $_GET['anglepeaktop'] != '' and $_GET['height'] != '' and $_GET['displace'] != '' and
   $_GET['driftpeak'] != '' and $_GET['acc1'] != '' and $_GET['score'] != '') {
	$accpeak = $_GET['accpeak'];
	$anglepeak = $_GET['anglepeak'];
	$anglepeaktop = $_GET['anglepeaktop'];
	$height = $_GET['height'];
	$displace = $_GET['displace'];
	$driftpeak = $_GET['driftpeak'];
	$acc1 = $_GET['acc1'];
	$score = $_GET['score'];

	// Create connection
	$conn = new mysqli($servername, $username, $password, $dbname);
	// Check connection
	if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	}

	$sql = "INSERT INTO datalogger (pga, botanglepeak, topanglepeak, height, displacepeak, driftpeak, pgadr1, score)
	VALUES ('" . $accpeak . "', '" . $anglepeak . "', '" . $anglepeaktop . "', '" . $height . "',
			'" . $displace . "', '" . $driftpeak . "', '" . $acc1 . "', '" . $score . "')";

	if ($conn->query($sql) === TRUE) {
		echo "New record created successfully";
	} else {
		echo "Error: " . $sql . "<br>" . $conn->error;
	}

	$conn->close();
}
else {
	echo "Data ra mlebu cuk!";
}