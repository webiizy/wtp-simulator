<?php
include("core/global.inc");

function get_radio_status($radio)
{


}

	include("head.inc");
?>
<body link="#0000CC" vlink="#0000CC" alink="#0000CC">
<?php
	include("fbegin.inc");
?>
<p class="pgtitle">状态: 无线接口</p>

<table width="100%" border="0" cellspacing="0" cellpadding="0">
<form action="status_interfaces.php" method="post">
<input type="hidden" name="interface" value="wan">
<?php
	for($i = 0; $i<$radio_count; $i++) {
		$status = get_radio_status('wlan' . $i);
?>
	<tr>
		<td colspan="2" class="listtopic">
			无线接口 (radio<?php echo $i?>) &nbsp;&nbsp; <a href="status_graph.php?ifname=radio<?php echo $i?>">实时监测</a>
		</td>
	</tr>
	<tr>
		<td width="22%" class="vncellt">Status</td>
		<td width="78%" class="listr"><?php echo $status['status']?></td>
	</tr>
	<tr>
		<td width="22%" class="vncellt">MAC address</td>
		<td width="78%" class="listr"><?php echo $status['mac_addr']?></td>
	</tr>
	<tr>
		<td width="22%" class="vncellt">Media</td>
		<td width="78%" class="listr"><?php echo $status['media']?></td>
	</tr>
	
	<tr>
		<td width="22%" class="vncellt">In/out packets</td>
		<td width="78%" class="listr"><?php echo $status['in_packets']?>/<?php echo $status['out_packets']?> (244 KB/1.23 MB)</td>
	</tr>
	
	<tr>
		<td width="22%" class="vncellt">In/out errors</td>
		<td width="78%" class="listr"><?php echo $status['in_errors']?>/<?php echo $status['out_errors']?></td>
	</tr>              
	<tr>
		<td width="22%" class="vncellt">Collisions</td>
		<td width="78%" class="listr"><?php echo $status['collisions']?></td>
	</tr>
	<tr><td colspan="2">&nbsp;</td>
	</tr>
<?php
	}
?>
</table>
<?php
	include("fend.inc");
?>
</body>
</html>
