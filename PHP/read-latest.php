<?php
	include_once('fungsi.php');

	$last_reading = getLastReadings();
    $last_reading_acc = $last_reading["gndacc"];
	$last_reading_angle = $last_reading["angle"];
    $last_reading_drift = $last_reading["drift"];
	
	$last_reading = getLastReadings2();
    $last_reading_angle2 = $last_reading["angle"];

	echo '<td>' . $last_reading_acc . 'g</td>
		  <td>' . $last_reading_angle . '°</td>
		  <td>' . $last_reading_angle2 . '°</td>
          <td>' . $last_reading_drift . '%</td>';