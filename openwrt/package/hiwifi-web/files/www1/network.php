<?php
include("action/func.inc");

	if($_POST) {
		$ipaddr = $_POST['ipaddr'];
		$netmask = $_POST['netmask'];
		$gateway = $_POST['gateway'];	
		
		system("uci commit network");
		
		$result = 1;
	}
	else {
		$cfg = config_get_array("network.lan");
		
		$ipaddr = $cfg['ipaddr'];	
		$netmask = strlen(preg_replace("/0/", "", decbin(ip2long($cfg['netmask']))));
		$gateway = $cfg['gateway'];
	}

	include("head.inc");
?>
<body link="#0000CC" vlink="#0000CC" alink="#0000CC">
<?php
	include("fbegin.inc");
?>
<p class="pgtitle">网络设置: </p>
<form action="network.php" method="post" name="iform" id="iform">

<table width="100%" border="0" cellpadding="6" cellspacing="0">
	<?php if(isset($result)) { ?>
	<tr>
		<td width="22%" class="vncellt">&nbsp;</td>
		<td width="78%" class="vncellt">
			修改成功
		</td>
	</tr>
	<?php } ?>	
	<tr>
		<td width="22%" valign="top" class="vncellreq">设备模式</td>
		<td width="78%" class="vtable">
			<select name="bridge" class="formfld" id="bridge" disabled>
				<option selected value="bridge">网桥</option>
				<option value="bridge">路由器</option>
			</select>&nbsp;<span class="red"><strong>注意:</strong></span>&nbsp;仅支持"网桥"模式
		</td>
	</tr>
	
	<tr>
		<td width="22%" valign="top" class="vncellreq">IP地址</td>
		<td width="78%" class="vtable">
			<input name="ipaddr" type="text" class="formbtn" value="<?php echo $ipaddr?>"> / 
			<select name="netmask" class="formfld" id="netmask">
				<?php
					for($i = 32; $i >= 8; $i--) {
						if($i == $netmask) {
							echo '<option value="' . $i . '" selected>' . $i . '</option>';
						}
						else {
							echo '<option value="' . $i . '">' . $i . '</option>';
						}
					}
				?>
			</select>
		</td>
	</tr>
	<tr>
		<td width="22%" valign="top" class="vncellreq">网关</td>
		<td width="78%" class="vtable">
			<input name="gateway" type="text" class="formbtn" value="<?php echo $gateway?>">
		</td>
	</tr>
	<tr>
		<td width="22%" valign="top" class="vncellreq"></td>
		<td width="78%" class="vtable">
			<input name="Submit" type="submit" class="formbtn" value="确定">
		</td>
	</tr>
	<tr>
		<td></td>
		<td>
			<span class="red"><strong>注意:</strong></span><br/>
			如果修改了IP地址, 点击"确定"后, 你需要做以下操作
			<ul>
			  <li><span class="vexpl">修改计算机的IP地址(与本设备在同一网段)</span></li>
			  <li><span class="vexpl">重新使用设备的新IP地址进入WEBGUI</span></li>
			</ul>
		</td>
	</tr>
</table>

</form>
<?php
	include("fend.inc");
?>
</body>
</html>
