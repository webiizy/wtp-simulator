<?php
	$imax = 0;
	$fp = popen('route', 'r');
	
	$line = fgets($fp);
	$route[] = preg_split("/\s+/", $line);
		
	while (!feof($fp)) {
	   $line = fgets($fp);
	   
	   $route[] = preg_split("/\s+/", $line);
	   $imax++;
	}
	
	pclose($fp);
	
	include("head.inc");
?>
<body link="#0000CC" vlink="#0000CC" alink="#0000CC">
<?php
	include("fbegin.inc");
?>
<p class="pgtitle">诊断: 路由表</p>
<table width="100%" cellspacing="0" cellpadding="6" border="0">
<tr><td class="listbg" colspan="8"><font color="white"><strong>IPv4</strong></font></td></tr>
<tr>
<td class="listhdrr">Destination</td>
<td class="listhdrr">Gateway</td>
<td class="listhdrr">Genmask</td>
<td class="listhdrr">Flags</td>
<td class="listhdrr">Metric</td>
<td class="listhdrr">Ref</td>
<td class="listhdrr">Use</td>
<td class="listhdrr">Iface</td>
</tr>

  <?php
	for($i = 2; $i < $imax; $i++) {
		echo '<tr>';
		echo '<td class="listlr">' . $route[$i][0] .'</td>';
		echo '<td class="listlr">' . $route[$i][1] .'</td>';
		echo '<td class="listlr">' . $route[$i][2] .'</td>';
		echo '<td class="listlr">' . $route[$i][3] .'</td>';
		echo '<td class="listlr">' . $route[$i][4] .'</td>';
		echo '<td class="listlr">' . $route[$i][5] .'</td>';
		echo '<td class="listlr">' . $route[$i][6] .'</td>';
		echo '<td class="listlr">' . $route[$i][7] .'</td>';
		echo '</tr>';
	}
  ?>
</table>

<?php
	include("fend.inc");
?>
</body>
</html>
