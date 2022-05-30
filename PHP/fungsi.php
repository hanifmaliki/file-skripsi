<?php
$servername = "localhost";
$username = "hanipm97";
$password = "hanifmaliki";
$dbname = "skripsi";

function getAllLogs($limit) {
	global $servername, $username, $password, $dbname;

    $conn = new mysqli($servername, $username, $password, $dbname);
    if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
    }

    $sql = "SELECT id, pga, botanglepeak, topanglepeak, height, displacepeak, driftpeak, pgadr1, score, time FROM datalogger ORDER BY ID DESC limit " . $limit;

	if ($result = $conn->query($sql)) {
		return $result;
    }
    else {
		return false;
    }
    $conn->close();
}

function getLastReadings() {
    global $servername, $username, $password, $dbname;

    $conn = new mysqli($servername, $username, $password, $dbname);
    if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
    }

    $sql = "SELECT id, gndacc, angle, drift, pga, anglepeak, height, displacepeak, driftpeak, pgadr1, score, time FROM botdata ORDER BY ID DESC limit 1";

	if ($result = $conn->query($sql)) {
		return $result->fetch_assoc();
    }
    else {
		return false;
    }
    $conn->close();
}

function getLastReadings2() {
    global $servername, $username, $password, $dbname;

    $conn = new mysqli($servername, $username, $password, $dbname);
    if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
    }

    $sql = "SELECT id, angle, anglepeak, time FROM topdata ORDER BY ID DESC limit 1";

	if ($result = $conn->query($sql)) {
		return $result->fetch_assoc();
    }
    else {
		return false;
    }
    $conn->close();
}

function getLastCommand() {
    global $servername, $username, $password, $dbname;

    $conn = new mysqli($servername, $username, $password, $dbname);
    if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
    }

    $sql = "SELECT command FROM botcommand ORDER BY ID DESC limit 1";

	if ($result = $conn->query($sql)) {
		return $result->fetch_assoc();
    }
    else {
		return false;
    }
    $conn->close();
}

function getLastCommand2() {
    global $servername, $username, $password, $dbname;

    $conn = new mysqli($servername, $username, $password, $dbname);
    if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
    }

    $sql = "SELECT command FROM topcommand ORDER BY ID DESC limit 1";

	if ($result = $conn->query($sql)) {
		return $result->fetch_assoc();
    }
    else {
		return false;
    }
    $conn->close();
}

function writeCommand($command) {
    global $servername, $username, $password, $dbname;

    $conn = new mysqli($servername, $username, $password, $dbname);
    if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
    }

	$sql = "INSERT INTO botcommand (command)
	VALUES ('" . $command . "')";

	$conn->query($sql);
	
	$sql = "INSERT INTO topcommand (command)
	VALUES ('" . $command . "')";

	$conn->query($sql);

	$conn->close();
}

function writeLog() {
	$last_reading = getLastReadings();
	$pga = $last_reading["pga"];
	$anglepeak = $last_reading["anglepeak"];
	$height = $last_reading["height"];
	$displacepeak = $last_reading["displacepeak"];
	$driftpeak = $last_reading["driftpeak"];
	$pgadr1 = $last_reading["pgadr1"];
	$score = $last_reading["score"];
	
	$last_reading = getLastReadings2();
	$anglepeak2	= $last_reading["anglepeak"];
	
    global $servername, $username, $password, $dbname;

    $conn = new mysqli($servername, $username, $password, $dbname);
    if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
    }

	$sql = "INSERT INTO datalogger (pga, botanglepeak, topanglepeak, height, displacepeak, driftpeak, pgadr1, score)
		    VALUES ('" . $pga . "', '" . $anglepeak . "', '" . $anglepeak2 . "', '" . $height . "', '" . $displacepeak . "',
				    '" . $driftpeak . "', '" . $pgadr1 . "', '" . $score . "')";

	$conn->query($sql);
	$conn->close();
}