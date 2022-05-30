<?php
	include_once('fungsi.php');

	$last_reading = getLastReadings();
    $last_reading_accpeak = $last_reading["pga"];
	$last_reading_anglepeak = $last_reading["anglepeak"];
    $last_reading_driftpeak = $last_reading["driftpeak"];
	
	$last_reading = getLastReadings2();
	$last_reading_anglepeak2 = $last_reading["anglepeak"];

	echo '<td>' . $last_reading_accpeak . 'g</td>
		  <td>' . $last_reading_anglepeak . '°</td>
		  <td>' . $last_reading_anglepeak2 . '°</td>
          <td>' . $last_reading_driftpeak . '%</td>';