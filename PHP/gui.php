<?php
	include_once('fungsi.php');

	$command="x";

	if (isset($_GET["command"])){$command = $_GET["command"];}
	if ($command!="x"){writeCommand($command);}
	if ($command=="a"){writeLog();}
?>

<!DOCTYPE html>
<html>
    <head><meta http-equiv="Content-Type" content="text/html; charset=utf-8">
        <link rel="stylesheet" type="text/css" href="style.css">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <script src="jquery.min.js"></script>
		<script>
			setInterval(function (){$('#latest-time').load('read-time.php');}, 100);
			setInterval(function (){$('#latest-data').load('read-latest.php');}, 100);
			setInterval(function (){$('#peak-data').load('read-peak.php');}, 100);
			setInterval(function (){$('#score-gauge').load('read-score.php');}, 100);
			setInterval(function (){$('#logs-table').load('read-logs.php');}, 100);
		</script>
    </head>
    <header class="header">
        <h1>📊 WALL STIFFNESS</h1>
        <form method="get" style="margin-bottom: 13px">
            <input type="text" name="command" placeholder="Node command">
            <input type="submit" value="Send">
        </form>
		<form class="button" method="get">
            <input type="hidden" name="command" value="q">
            <input type="submit" class="buttonGreen" value="Start">
        </form>
		<form class="button" method="get">
            <input type="hidden" name="command" value="a">
            <input type="submit" class="buttonGreen" value="Stop">
        </form>
		<form class="button" method="get">
            <input type="hidden" name="command" value="w">
            <input type="submit" class="buttonGreen" value="Reset">
        </form>
    </header>
<body>
    <p id="latest-time">
	    <div class="box gauge--1">
			<h3>SCORE</h3>
			<center id="score-gauge">
		</div>
			<section class="content">
		    <table cellspacing="5" cellpadding="5">
		        <tr>
		            <th colspan="4">Latest reading</th>
	            </tr>
		        <tr>
		            <td>Ground<br>Acc</td>
					<td>Bot. Inc.<br>Angle</td>
                    <td>Top Inc.<br>Angle</td>
					<td>Drift<br>Ratio</td>
                </tr>
                <tr id="latest-data">
            </table>
			<table cellspacing="5" cellpadding="5">
		        <tr>
		            <th colspan="4">Peak Data</th>
	            </tr>
		        <tr>
		            <td>Ground<br>Acc</td>
					<td>Bot. Inc.<br>Angle</td>
                    <td>Top Inc.<br>Angle</td>
					<td>Drift<br>Ratio</td>
                </tr>
                <tr id="peak-data">
            </table>
			</section>
<?php
    echo   '<h2>View Recent Data Logs</h2>
            <table cellspacing="5" cellpadding="5" id="logs-table">';
?>
</body>
</html>