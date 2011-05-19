<?php
	include("head.inc");
?>
<body link="#000000" vlink="#000000" alink="#000000">
<script src="javascript/sorttable.js"></script>
<?php
	include("fbegin.inc");
	
	$ifname = "radio0";
	$status = "checked";
	$txpower = 20;
	$distance = "300";
	
?>
<p class="pgtitle">无线设置: 无线网络设置</p>
<form action="vap_edit.php" method="post" enctype="multipart/form-data">
<input type="hidden" name="ifname" value="<?php echo $ifname?>"/>
<table width="100%" border="0" cellpadding="0" cellspacing="0">
	<tr>
		<td width="22%"></td>
		<td width="78%" class="vncellt">
			<?php echo $ifname;?>
		</td>
	</tr>	
	<tr>
		<td colspan="2" class="listtopic">
			<?php echo $ifname?> 接口配置
		</td>
	</tr>
	
	<tr>
		<td width="22%" class="vncellt">无线网络名</td>
		<td width="78%" class="listr">
			<input type="text" name="distance" value="<?php echo $distance?>">
		</td>
	</tr>
	<tr>
		<td width="22%" class="vncellt">网络模式</td>
		<td width="78%" class="listr">
			<select>
				<option value="ap">Access Point</option>
				<option value="">Client</option>
				<option value="">WDS AP</option>
				<option value="">WDS Client</option>
			</select>
		</td>
	</tr>
	
	<tr>
		<td width="22%" class="vncellt">是否隐藏</td>
		<td width="78%" class="listr">
			<select>
				<option value="ap">是</option>
				<option value="">否</option>
			</select>
		</td>
	</tr>

	<tr>
		<td width="22%" class="vncellt">客户独立</td>
		<td width="78%" class="listr">
			<select>
				<option value="ap">是</option>
				<option value="">否</option>
			</select>
		</td>
	</tr>

	<tr>
		<td width="22%" class="vncellt">启用WMM</td>
		<td width="78%" class="listr">
			<select>
				<option value="ap">是</option>
				<option value="">否</option>
			</select>
		</td>
	</tr>
	
	<tr>
		<td width="22%" class="vncellt">加密方式</td>
		<td width="78%" class="listr">
			<select>
				<option value="none">None</option>
				<option value="wep">WEP</option>
				<option value="wpa">WPA</option>
			</select>
		</td>
	</tr>
	<tr>
		<td colspan="2">&nbsp;</td>
	</tr>
	<tr>
		<td width="22%" valign="top">&nbsp;</td>
		<td width="78%">
			<input name="if" type="hidden" value="lan">
			<input name="Submit" type="submit" class="formbtn" value="确定" onclick="">
		</td>
	</tr>
</table>
</form>
<?php
	include("fend.inc");
?>
</body>
</html>

