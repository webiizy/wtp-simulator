<?php
include('action/func.inc');

if($_POST) $r = $_POST['r'];
else {
	$r = $_GET['r'];
	if($r == '') $r = '0';
}
$s["$r"] = 'selected';

$root = config_get_rootname("wireless.@wifi-iface[$r]");

	if($_POST) {
		$ssid = $_POST['ssid'];
		$mode = $_POST['mode'];

		$cfg['ssid'] = $ssid;
		if(substr($mode, 0, 3) == 'wds') {
			$cfg['mode'] = substr($mode, 3);
			$cfg['wds'] = 1;
		}
		else {
			$cfg['wds'] = 0;
			$cfg['mode'] = $mode;
		}

		$result = 1;

		config_set_array($root, $cfg);
		config_commit('wireless');
		module_restart('network');
	}
	else {
		$cfg = config_get_array($root);
		$ssid = $cfg['ssid'];
		$mode = $cfg['mode'];
		$wds = $cfg['wds'];

		if($wds == '1') $mode = 'wds' . $mode;
	}

	include("head.inc");
?>
<body link="#000000" vlink="#000000" alink="#000000">
<?php
	include("fbegin.inc");
?>
<p class="pgtitle">无线设置: 无线网络设置</p>
<form action="interfaces_vap.php" method="post" enctype="multipart/form-data">
<input type="hidden" name="r" value="<?php echo $r?>"/>
<table width="100%" border="0" cellpadding="0" cellspacing="0">
	<tr>
		<td width="22%"></td>
		<td width="78%" class="vncellt">
			<select style="width:100px" onchange="window.location='interfaces_vap.php?r=' + this.options[this.selectedIndex].value">
				<option value="0" <?php echo $s['0']?>>radio0</option>
				<option value="1" <?php echo $s['1']?>>radio1</option>
				<option value="2" <?php echo $s['2']?>>radio2</option>
			</select>
		</td>
	</tr>
	<?php if(isset($result)) { ?>
	<tr>
		<td width="22%" class="vncellt">&nbsp;</td>
		<td width="78%" class="vncellt">
			修改成功
		</td>
	</tr>
	<?php } ?>
	<tr>
		<td colspan="2" class="listtopic">
			<?php echo $ifname?> 无线网络配置
		</td>
	</tr>

	<tr>
		<td width="22%" class="vncellt">无线网络名</td>
		<td width="78%" class="listr">
			<input type="text" name="ssid" value="<?php echo $cfg['ssid']?>">
		</td>
	</tr>
	<tr>
		<td width="22%" class="vncellt">网络模式</td>
		<td width="78%" class="listr">
			<select name="mode" id="mode">
				<option value="ap">Access Point</option>
				<option value="client">Client</option>
				<option value="wdsap">WDS AP</option>
				<option value="wdsclient">WDS Client</option>
			</select>
		</td>
	</tr>

	<tr>
		<td width="22%" class="vncellt">是否隐藏</td>
		<td width="78%" class="listr">
			<select>
				<option value="">是</option>
				<option value="">否</option>
			</select>
		</td>
	</tr>

	<tr>
		<td width="22%" class="vncellt">客户独立</td>
		<td width="78%" class="listr">
			<select name="">
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
			<input name="Submit" type="submit" class="formbtn" value="确定">
		</td>
	</tr>
</table>
</form>
<script language="javascript">
var mode = '<?php echo $mode;?>';

var o = document.getElementById('mode');
	for(var i = 0; i < o.options.length; i++) {
		if(o.options[i].value == mode) {
			o.selectedIndex = i;
			break;
		}
	}

</script>
<?php
	include("fend.inc");
?>
</body>
</html>

