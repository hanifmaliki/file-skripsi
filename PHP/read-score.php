<?php
	include_once('fungsi.php');

	$last_reading = getLastReadings();
    $last_reading_score = $last_reading["score"];
?>

<script>
    var value1 = <?php echo $last_reading_score; ?>;
    setScore(value1);

    function setScore(curVal){
    	var minScore = 0;
    	var maxScore = 4;

    	var newVal = scaleValue(curVal, [minScore, maxScore], [0, 180]);
    	$('.gauge--1 .semi-circle--mask').attr({
    		style: '-webkit-transform: rotate(' + newVal + 'deg);' +
    		'-moz-transform: rotate(' + newVal + 'deg);' +
    		'transform: rotate(' + newVal + 'deg);'
    	});
    	$("#scoreVal").text(curVal + '/4');
    }

    function scaleValue(value, from, to) {
        var scale = (to[1] - to[0]) / (from[1] - from[0]);
        var capped = Math.min(from[1], Math.max(from[0], value)) - from[0];
        return ~~(capped * scale + to[0]);
    }
</script>
<div class="mask">
	<div class="semi-circle"></div>
	<div class="semi-circle--mask"></div>
</div>
<p style="font-size: 30px; margin-bottom: 15px" id="scoreVal">--</p>

<?php
if ($last_reading_score>=4) {
	echo '<p style="font-size: 20px; color: #05b027; margin: 0">Good</p>';
}
else if ($last_reading_score==0) {
	echo '<p style="font-size: 20px; margin: 0">--</p>';
}
else {
	echo '<p style="font-size: 20px; color: #ff0000; margin: 0">Bad</p>';
}
?>