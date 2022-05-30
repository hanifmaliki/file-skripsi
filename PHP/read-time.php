<?php
	include_once('fungsi.php');

	$last_reading = getLastReadings();
    $last_reading_time = $last_reading["time"];

	echo "Last reading: ";
	echo $last_reading_time;