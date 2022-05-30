<?php
	echo '<tr>
			<th>ID</th>
			<th>Peak Ground Acc</th>
			<th>Peak Bottom Inc. Angle</th>
			<th>Peak Top Inc. Angle</th>
			<th>Height</th>
			<th>Peak Displacement</th>
			<th>Peak Drift Ratio</th>
			<th>PGA at DR = 1%</th>
			<th>Score</th>
			<th>Timestamp</th>
		  </tr>';

	include_once('fungsi.php');

	$result = getAllLogs(20);
	while ($row = $result->fetch_assoc()) {
		$row_id = $row["id"];
		$row_pga = $row["pga"];
		$row_botanglepeak = $row["botanglepeak"];
		$row_topanglepeak = $row["topanglepeak"];
		$row_height = $row["height"];
		$row_displacepeak = $row["displacepeak"];
		$row_driftpeak = $row["driftpeak"];
		$row_pgadr1 = $row["pgadr1"];
		$row_score = $row["score"];
		$row_time = $row["time"];

		echo '<tr>
				<td>' . $row_id . '</td>
                <td>' . $row_pga . 'g</td>
                <td>' . $row_botanglepeak . '°</td>
				<td>' . $row_topanglepeak . '°</td>
				<td>' . $row_height . ' cm</td>
                <td>' . $row_displacepeak . ' cm</td>
                <td>' . $row_driftpeak . '%</td>
                <td>' . $row_pgadr1 . 'g</td>
                <td>' . $row_score . '</td>
				<td>' . $row_time . '</td>
              </tr>';
    }