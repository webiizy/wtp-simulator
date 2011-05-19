<?php
	$imax = 0;
	$fp = fopen('/proc/net/arp', 'r');
	
	$line = fgets($fp);
	$arp[] = preg_split("/\s+/", $line);
		
	while (!feof($fp)) {
	   $line = fgets($fp);
	   
	   $arp[] = preg_split("/\s+/", $line);
	   $imax++;
	}
	
	fclose($fp);

	include("head.inc");
?>
<body link="#000000" vlink="#000000" alink="#000000">
<?php
	include("fbegin.inc");
?>
<p class="pgtitle">诊断: ARP表</p>
<table width="100%" border="0" cellpadding="0" cellspacing="0">
        <tr>
                <td>
<table class="sortable" name="sortabletable" id="sortabletable" width="100%" border="0" cellpadding="0" cellspacing="0">
  <tr>
    <td class="listhdrr">IP address</td>
	<td class="listhdrr">HW type</td>
    <td class="listhdrr">Flags</td>
    <td class="listhdrr">MAC address</td>
	<td class="listhdrr">Mask</td>
    <td class="listhdr">Interface</td>
    <td class="list"></td>
  </tr>
  <?php
	for($i = 2; $i < $imax; $i++) {
		echo '<tr>';
		echo '<td class="listlr">' . $arp[$i][0] .'</td>';
		echo '<td class="listlr">' . $arp[$i][1] .'</td>';
		echo '<td class="listlr">' . $arp[$i][2] .'</td>';
		echo '<td class="listlr">' . $arp[$i][3] .'</td>';
		echo '<td class="listlr">' . $arp[$i][4] .'</td>';
		echo '<td class="listlr">' . $arp[$i][5] .'</td>';
		echo '</tr>';
	}
  ?>
</table>
</td></tr></table>
<?php
	include("fend.inc");
?>
</body>
</html>

