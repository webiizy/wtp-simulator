<?php
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
    <td class="listhdrr"><a href="diag_dhcp_leases.php@all=&amp;order=ip">IP address</a></td>
    <td class="listhdrr"><a href="diag_dhcp_leases.php@all=&amp;order=mac">MAC address</a></td>
    <td class="listhdrr"><a href="diag_dhcp_leases.php@all=&amp;order=hostname">Hostname</a></td>
    <td class="listhdrr"><a href="diag_dhcp_leases.php@all=&amp;order=start">Start</a></td>
    <td class="listhdrr"><a href="diag_dhcp_leases.php@all=&amp;order=end">End</a></td>
    <td class="listhdr"><a href="diag_dhcp_leases.php@all=&amp;order=online">Online</a></td>
    <td class="listhdr"><a href="diag_dhcp_leases.php@all=&amp;order=act">Lease Type</a></td>
	</tr>
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
