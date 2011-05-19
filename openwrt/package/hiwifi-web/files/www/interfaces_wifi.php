<?php
include('action/func.inc');

if($_POST) $r = $_POST['r'];
else {
	$r = $_GET['r'];
	if($r == '') $r = '0';
}
$s["$r"] = 'selected';

$root = 'wireless.radio' . $r;

	if($_POST) {
		$cfg['txpower'] = $_POST['txpower'];
		$cfg['diversity'] = $_POST['diversity'];
		$cfg['rxantenna'] = $_POST['rxantenna'];
		$cfg['txantenna'] = $_POST['txantenna'];
		$cfg['distance'] = $_POST['distance'];

		$cfg['disabled'] = ($_POST['status'] == '1') ? 0: 1;

		config_set_array($root, $cfg);
		config_commit('wireless');
		module_restart('network');
		$result = 1;
	}
	else {
		$cfg = config_get_array($root);
	}

	$hwmode = $cfg['hwmode'];
	$htmode = $cfg['htmode'];

	$disabled = $cfg['disabled'];
	$channel = $cfg['channel'];
	$txpower = $cfg['txpower'];
	$diversity = $cfg['diversity'];
	$rxantenna = $cfg['rxantenna'];
	$txantenna = $cfg['txantenna'];
	$distance = $cfg['distance'];

	if($disabled != '1') $disabled = 'checked';

	include("head.inc");
?>
<body link="#000000" vlink="#000000" alink="#000000">
<script src="javascript/sorttable.js"></script>
<?php
	include("fbegin.inc");
?>
<p class="pgtitle">无线设置: 无线接口</p>
<form action="interfaces_wifi.php" method="post" enctype="multipart/form-data">
<input name="r" type="hidden" value="<?php echo $r;?>">
<table width="100%" border="0" cellpadding="0" cellspacing="0">
	<tr>
		<td width="22%"></td>
		<td width="78%" class="vncellt">
			<select style="width:100px" onchange="window.location='interfaces_wifi.php?r=' + this.options[this.selectedIndex].value">
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
			radio<?php echo $r?> 接口配置
		</td>
	</tr>

	<tr>
		<td width="22%" class="vncellt"></td>
		<td width="78%" class="listr">
			<input type="checkbox" name="status" value='1' <?php echo $disabled;?>/>&nbsp;启用radio<?php echo $r?> 无线接口
		</td>
	</tr>

	<tr>
		<td width="22%" class="vncellt">无线模式</td>
		<td width="78%" class="listr">
			<select name="hwmode" id='hwmode'>
				<option value="11a">802.11a</option>
				<option value="11bg">802.11b/g</option>
				<option value="11g">802.11g only</option>
				<option value="11na">802.11na</option>
				<option value="11ng">802.11ng</option>
			</select>
		</td>
	</tr>
	<tr>
		<td width="22%" class="vncellt">频宽</td>
		<td width="78%" class="listr">
			<select name="htmode" id='htmode'>
				<option value="HT20">HT20</option>
				<option value="HT40">HT40</option>
			</select>
		</td>
	</tr>
	<tr>
		<td width="22%" class="vncellt">无线频道</td>
		<td width="78%" class="listr">
			<select name="channel" id='channel'>
				<option value="01">01 : 2.412 GHz</option>
				<option value="02">02 : 2.417 GHz</option>
				<option value="03">03 : 2.422 GHz</option>
				<option value="04">04 : 2.427 GHz</option>
				<option value="05">05 : 2.432 GHz</option>
				<option value="06">06 : 2.437 GHz</option>
				<option value="07">07 : 2.442 GHz</option>
				<option value="08">08: 2.447 GHz</option>
				<option value="09">09 : 2.452 GHz</option>
				<option value="10">10 : 2.457 GHz</option>
				<option value="11">11 : 2.462 GHz</option>
				<option value="36">36 : 5.18 GHz</option>
				<option value="40">40 : 5.2 GHz</option>
				<option value="44">44 : 5.22 GHz</option>
				<option value="48">48 : 5.24 GHz</option>
				<option value="52">52 : 5.26 GHz</option>
				<option value="56">56 : 5.28 GHz</option>
				<option value="60">60 : 5.3 GHz</option>
				<option value="64">64 : 5.32 GHz</option>
				<option value="100">100 : 5.5 GHz</option>
				<option value="104">104 : 5.52 GHz</option>
				<option value="108">108 : 5.54 GHz</option>
				<option value="112">112 : 5.56 GHz</option>
				<option value="116">116 : 5.58 GHz</option>
				<option value="132">132 : 5.66 GHz</option>
				<option value="136">136 : 5.68 GHz</option>
				<option value="140">140 : 5.7 GHz</option>
				<option value="149">149 : 5.745 GHz</option>
				<option value="153">153 : 5.765 GHz</option>
				<option value="157">157 : 5.785 GHz</option>
				<option value="161">161 : 5.805 GHz</option>
				<option value="165">165 : 5.825 GHz</option>
			</select>
		</td>
	</tr>
	<tr>
		<td width="22%" class="vncellt">多样性</td>
		<td width="78%" class="listr">
			<select>
				<option value="1">启用</option>
				<option value="0">禁用</option>
			</select>
		</td>
	</tr>
	<tr>
		<td width="22%" class="vncellt">接收天线</td>
		<td width="78%" class="listr">
			<select>
				<option value="1">天线1</option>
				<option value="2">天线2</option>
			</select>
		</td>
	</tr>
	<tr>
		<td width="22%" class="vncellt">发送天线</td>
		<td width="78%" class="listr">
			<select>
				<option value="1">天线1</option>
				<option value="2">天线2</option>
			</select>
		</td>
	</tr>
	<tr>
		<td width="22%" class="vncellt">传输功率</td>
		<td width="78%" class="listr">
			<input type="text" name="txpower" value="<?php echo $txpower?>"> dbm
		</td>
	</tr>
	<tr>
		<td width="22%" class="vncellt">传输距离</td>
		<td width="78%" class="listr">
			<input type="text" name="distance" value="<?php echo $distance?>"> 米
		</td>
	</tr>
	<tr>
		<td colspan="2">&nbsp;</td>
	</tr>
	<tr>
		<td width="22%" valign="top">&nbsp;</td>
		<td width="78%">

			<input name="Submit" type="submit" class="formbtn" value="确定" onclick="">
		</td>
	</tr>
</table>
</form>
<script language="javascript">
var hwmode='<?php echo $hwmode?>';
var htmode='<?php echo $htmode?>';
var disabled='<?php echo $disabled?>';
var channel='<?php echo $channel?>';
var txpower='<?php echo $txpower?>';
var diversity='<?php echo $diversity?>';
var rxantenna='<?php echo $rxantenna?>';
var txantenna='<?php echo $txantenna?>';
var distance='<?php echo $distance?>';
</script>
<?php
	include("fend.inc");
?>
</body>
</html>

