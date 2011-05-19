<?php
	$imax = 0;
	$fp = fopen('/tmp/dhcp.leases', 'r');
	
	if($fp) {			
		while (!feof($fp)) {
		   $line = fgets($fp);
		   
		   $leases[] = preg_split("/\s+/", $line);
		   $imax++;
		}
		
		fclose($fp);
	}
	
	include("head.inc");
?>
<body link="#0000CC" vlink="#0000CC" alink="#0000CC">
<script src="javascript/sorttable.js"></script>
<?php
	include("fbegin.inc");
?>
<p class="pgtitle">状态: DHCP客户列表</p>

<p>

<table class="sortable" id="sortabletable" name="sortabletable" width="100%" border="0" cellpadding="0" cellspacing="0">
  <tr>
    <td class="listhdrr"><a href="diag_dhcp_leases.php@all=&amp;order=mac">MAC地址</a></td>
    <td class="listhdrr"><a href="diag_dhcp_leases.php@all=&amp;order=hostname">IP地址</a></td>
    <td class="listhdrr"><a href="diag_dhcp_leases.php@all=&amp;order=start">主机名</a></td>
    <td class="listhdrr"><a href="diag_dhcp_leases.php@all=&amp;order=ip">时长</a></td>
	</tr>
  <?php
	for($i = 0; $i < $imax; $i++) {
		echo '<tr>';
		echo '<td class="listlr">' . $leases[$i][1] .'</td>';
		echo '<td class="listlr">' . $leases[$i][2] .'</td>';
		echo '<td class="listlr">' . $leases[$i][3] .'</td>';
		echo '<td class="listlr">' . $leases[$i][0] .'</td>';
		echo '</tr>';
	}
  ?>
</table>
<p>
<form action="diag_dhcp_leases.php" method="GET">
<input type="hidden" name="order" value="">
<input type="hidden" name="all" value="1">
<input type="submit" class="formbtn" value="Show all configured leases">
</form>
<?php
	include("fend.inc");
?>
</body>
</html>
