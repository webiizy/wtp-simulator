<?php

	$telnet = "checked";
	$tport = "23";
	
	$ssh = "checked";
	$sport = "21";
	
	include("head.inc");
?>
<body link="#0000CC" vlink="#0000CC" alink="#0000CC">
<?php
	include("fbegin.inc");
?>

<p class="pgtitle">系统: 高级设置</p>
<form action="system_advanced.php" method="post" name="iform" id="iform">
<p><span class="vexpl"><span class="red"><strong>注意: </strong></span>本页面的设置项是为高级用户准备的, 请确保在设置前了解相关技术.</span></p>

<table width="100%" border="0" cellpadding="6" cellspacing="0">
	<tbody>

		<tr>
			<td colspan="2" valign="top" class="listtopic">Telnet</td>
		</tr>
		<tr>
			<td width="22%" valign="top" class="vncell">&nbsp;</td>
			<td width="78%" class="vtable">
				<input name="enablesshd" type="checkbox" id="enablesshd" value="yes" <?php echo $telnet?> />
				<strong>启用Telnet</strong>
			</td>
		</tr>
		<tr>
			<td width="22%" valign="top" class="vncell">Telnet端口</td>
			<td width="78%" class="vtable">
				<input name="sshport" type="text" id="sshport" value="<?php echo $tport?>"  />
				<br />
				<span class="vexpl">注意: 为空时表示采用缺省值 23</span>
			</td>
		</tr>
		<tr>
			<td width="22%" valign="top" class="vncell"></td>
			<td width="78%" class="vtable">
				<input name="Submit" type="submit" class="formbtn" value="确定" onclick="enable_change(true)" />
			</td>
		</tr>
		<tr>
			<td colspan="2" class="list" height="12">&nbsp;</td>
		</tr>
		
		<tr>
			<td colspan="2" valign="top" class="listtopic">Secure Shell(SSH)</td>
		</tr>
		<tr>
			<td width="22%" valign="top" class="vncell">&nbsp;</td>
			<td width="78%" class="vtable">
				<input name="enablesshd" type="checkbox" id="enablesshd" value="yes" <?php echo $ssh ?>/>
				<strong>启用Secure Shell</strong>
			</td>
		</tr>
		<tr>
			<td width="22%" valign="top" class="vncell">SSH端口</td>
			<td width="78%" class="vtable">
				<input name="sshport" type="text" id="sshport" value="<?php echo $sport?>" />
				<br />
				<span class="vexpl">注意: 为空时表示采用缺省值22</span>
			</td>
		</tr>
		<tr>
			<td width="22%" valign="top" class="vncell"></td>
			<td width="78%" class="vtable">
				<input name="Submit" type="submit" class="formbtn" value="确定" onclick="enable_change(true)" />
			</td>
		</tr>
		</tbody>
</table>
</form>

<script language="JavaScript" type="text/javascript">
<!--
	enable_change(false);
//-->
</script>
<?php
	include("fend.inc");
?>
</body>
</html>
