<?php
include("action/func.inc");

$username = 'root';

$system = config_get_rootname('system.@system[0]');

	if($_POST) {
		$cfg['hostname'] = $_POST['hostname'];
		$cfg['domain'] = $_POST['domain'];

		$cfg['dns1'] = $_POST['dns1'];
		$cfg['dns2'] = $_POST['dns2'];
		$cfg['timezone'] = $_POST['timezone'];

		config_set_array($system, $cfg);
		$result = 1;
	}
	else {
		$cfg = config_get_array($system);
	}

	$hostname = $cfg['hostname'];
	$domain = $cfg['domain'];
	$dns1 = $cfg['dns1'];
	$dns2 = $cfg['dns2'];
	$timezone = $cfg['timezone'];

	include("head.inc");
?>
<body link="#0000CC" vlink="#0000CC" alink="#0000CC">
<?php
	include("fbegin.inc");
?>
<p class="pgtitle">系统: 基本设置</p>
<form action="system.php" method="post">
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
		<td width="22%" valign="top" class="vncellreq">主机名</td>
		<td width="78%" class="vtable"> <input name="hostname" type="text" class="formfld" id="hostname" size="40" value="<?php echo $hostname;?>">
		<br> <span class="vexpl">用于区别本设备的名字<br>
			例. <em>device1</em></span></td>
	</tr>

	<tr>
		<td width="22%" valign="top" class="vncellreq">域</td>
		<td width="78%" class="vtable"> <input name="domain" type="text" class="formfld" id="domain" size="40" value="<?php echo $domain?>">
		<br> <span class="vexpl">例: <em>HiWiFi.net</em> </span></td>
	</tr>

	<tr>
		<td width="22%" valign="top" class="vncell">DNS IP地址</td>
		<td width="78%" class="vtable"> <p>
		<input name="dns1" type="text" class="formfld" id="dns1" size="20" value="<?php echo $dns1; ?>">
		<br/>
		<input name="dns2" type="text" class="formfld" id="dns2" size="20" value="<?php echo $dns2; ?>">
		<br>
		</td>
	</tr>

	<tr>
		<td valign="top" class="vncell">用户名</td>
		<td class="vtable"> <input name="username" readonly type="text" class="formfld" id="username" size="20" value="<?php echo $username?>">
		<br>
		<span class="vexpl">用于访问webGUI的用户名, 更改后旧用户名将不可用</span></td>
	</tr>

	<tr>
		<td width="22%" valign="top" class="vncell">密码</td>
		<td width="78%" class="vtable"> <input name="password" type="password" class="formfld" id="password" size="20" value="<?php echo $sys['password']?>">
		<br> <input name="password2" type="password" class="formfld" id="password2" size="20" value="<?php echo $sys['password2']?>">
		&nbsp;(再输入一遍) <br> <span class="vexpl">设置新密码时, 需要输入两次新密码, 不修改密码时请保留为空.</span></td>
	</tr>

	<tr>
		<td width="22%" valign="top" class="vncell">时区</td>
		<td width="78%" class="vtable">
			<select name="timezone" id="timezone">
				<option value="UTC">UTC</option>
				<option value="Asia/Chongqing" >Asia/Chongqing</option>
			</select> <br> <span class="vexpl"></span></td>
	</tr>

	<tr>
		<td width="22%" valign="top" class="vncell">NTP时间服务器</td>
		<td width="78%" class="vtable"> <input name="timeservers" type="text" class="formfld" id="timeservers" size="40" value="<?php echo $timeservers?>">
		<br> <span class="vexpl">用空格区分多个服务器, 如果输入域名地址请事先设置好DNS服务器IP地址!</span></td>
	</tr>

	<tr>
		<td colspan="2" class="list" height="12">&nbsp;</td>
	</tr>

	<tr>
		<td width="22%" valign="top">&nbsp;</td>
		<td width="78%"> <input name="Submit" type="submit" class="formbtn" value="确定"></td>
	</tr>
</table>
</form>
<?php
	include("fend.inc");
?>
</body>
</html>
