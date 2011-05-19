<?php
include("action/func.inc");

	if($_POST) {
		$cfg['start'] = $_POST['start'];
		$cfg['limit'] = $_POST['limit'];
		$cfg['leasetime'] = $_POST['leasetime'];
		$cfg['leasetime'] = $cfg['leasetime'] . 'h';
		$enable = $_POST['enable'];
		$cfg['ignore'] = ($enable == 'yes') ? '0' : '1';
		
		config_set_array('dhcp.lan', $cfg);
		module_restart('dnsmasq');
		$result = 1;
	}
	else {
		$cfg = config_get_array("dhcp.lan");
	}

	$start = $cfg['start'];
	$limit = $cfg['limit'];
	$leasetime = $cfg['leasetime'];
	$leasetime = trim(preg_replace("[^0-9/]","",$leasetime));
	$leasetime = substr($leasetime, 0, (strlen($leasetime)-1));
	$enable = $cfg['ignore'];
	$enable = ($enable == '1') ? '' : 'checked';
	
	$ipaddr = config_get('network.lan.ipaddr');
	$ipaddr = long2ip(ip2long($ipaddr) >> 8 << 8);
	$network = substr($ipaddr, 0, strlen($ipaddr)-1);
	include("head.inc");
?>

<body link="#0000CC" vlink="#0000CC" alink="#0000CC">
<?php
	include("fbegin.inc");
?>
<p class="pgtitle">服务: DHCP服务</p>
<form action="services_dhcp.php" method="post" name="iform" id="iform">

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
		<td colspan="2" valign="top" class="listtopic">DHCP服务</td>
	</tr>

	<tr>
		<td width="22%" valign="top" class="vncellreq">&nbsp;</td>
		<td width="78%" class="vtable">
			<input name="enable" type="checkbox" value="yes" <?php echo $enable;?>>
				<strong>启用DHCP服务</strong>
		</td>
	</tr>

	<tr>
		<td width="22%" valign="top" class="vncellreq">可用网段</td>
		<td width="78%" class="vtable"><?php echo $ipaddr?></td>
	</tr>

	<tr>
		<td width="22%" valign="top" class="vncellreq">网络掩码</td>
		<td width="78%" class="vtable">255.255.255.0</td>
	</tr>

	<tr>
		<td width="22%" valign="top" class="vncellreq">可用范围</td>
		<td width="78%" class="vtable">
			<?php echo $network?><input type="text" style="width:20px" name="start" value="<?php echo $start?>"> -
			<?php echo $network?><input type="text" style="width:25px" name="limit" value="<?php echo $limit?>">
		</td>
	</tr>
<!--
	<tr>
		<td width="22%" valign="top" class="vncell">DNS服务器IP地址</td>
		<td width="78%" class="vtable">
			<input name="dns1" type="text" class="formfld" id="dns1" size="20" value=""><br>
			<input name="dns2" type="text" class="formfld" id="dns2" size="20" value=""><br>
			  注意: 不设置些项时将使用系统缺省DNS服务器.
		</td>
	</tr>
-->
<!--
	<tr>
		<td width="22%" valign="top" class="vncell">网关</td>
		<td width="78%" class="vtable">
			<input name="gateway" type="text" class="formfld" id="gateway" size="20" value="<?php echo $gateway?>"><br>
		</td>
	</tr>
-->
	<tr>
		<td width="22%" valign="top" class="vncell">地址租期</td>
		<td width="78%" class="vtable">
			<input name="leasetime" type="text" class="formfld" id="leasetime" size="10" value="<?php echo $leasetime?>">小时<br>
			客户可使用获取IP地址的最长时间.
		</td>
	</tr>

	<tr>
		<td width="22%" valign="top">&nbsp;</td>
		<td width="78%">
			<input name="if" type="hidden" value="lan">
			<input name="Submit" type="submit" class="formbtn" value="确定" onclick="enable_change(true)">
		</td>
	</tr>

	<tr>
		<td width="22%" valign="top">&nbsp;</td>
		<td width="78%"> <p><span class="vexpl"><span class="red">
			<strong>注意:<br></strong></span>DHCP服务器IP地址可以在<a href="system.php">系统:
			基本设置</a> </span><span class="vexpl">里进行配置.<br>
                            <br>
							DHCP租期表可以在<a href="diag_dhcp_leases.php">状态:
                            DHCP租期表</a> 里查看.<br>
                            </span></p>
		</td>
	</tr>
</table>

<table width="100%" border="0" cellpadding="0" cellspacing="0">
	<tr>
		<td colspan="5" valign="top" class="listtopic">静态地址分配</td>
	</tr>
	<tr>
		<td width="25%" class="listhdrr">MAC地址</td>
		<td width="15%" class="listhdrr">IP地址</td>
		<td width="20%" class="listhdrr">主机名</td>
		<td width="30%" class="listhdr">描述</td>
		<td width="10%" class="list">
			<table border="0" cellspacing="0" cellpadding="1">
			<tr>
				<td valign="middle" width="17"></td>
				<td valign="middle"><a href="services_dhcp_edit.php"><img src="themes/nervecenter/images/icons/icon_plus.gif" width="17" height="17" border="0"></a></td>
			</tr>
			</table>
		</td>
	</tr>

	<tr>
		<td class="list" colspan="4"></td>
		<td class="list">
			<table border="0" cellspacing="0" cellpadding="1">
				<tr>
						<td valign="middle" width="17"></td>
						<td valign="middle"><a href="services_dhcp_edit.php"><img src="themes/nervecenter/images/icons/icon_plus.gif" width="17" height="17" border="0"></a></td>
				</tr>
			</table>
		</td>
	</tr>
</table>
</form>
<script language="JavaScript">
<!--
enable_change(false);
//-->
</script>
<?php
	include("fend.inc");
?>
</body>
</html>
