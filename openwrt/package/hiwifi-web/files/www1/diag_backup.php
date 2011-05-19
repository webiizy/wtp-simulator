<?php
	include("head.inc");
?>
<body link="#0000CC" vlink="#0000CC" alink="#0000CC">
<?php
	include("fbegin.inc");
?>
<p class="pgtitle">诊断: 备份/恢复</p>

<form action="diag_backup.php" method="post" enctype="multipart/form-data">
<table width="100%" border="0" cellspacing="0" cellpadding="0">
	<tr>
		<td colspan="2"></td>
	</tr>
	
	<tr>
		<td colspan="2" class="listtopic">配置备份</td>
	</tr>
	<tr>
		<td width="22%" valign="baseline" class="vncell">&nbsp;</td>
		<td width="78%" class="vtable">
			<p>点击这个按钮下载当前配置文件.<br /><br />
			<p><input name="Submit" type="submit" class="formbtn" id="download" value="下载当前配置"></p>
		</td>
	</tr>
	<tr>
		<td colspan="2" class="list" height="12">&nbsp;</td>
	</tr>
	<tr>
		<td colspan="2" class="listtopic">配置恢复</td>
	</tr>
	<tr>
		<td width="22%" valign="baseline" class="vncell">&nbsp;</td>
		<td width="78%" class="vtable">
			<p>打开一个本地的配置文件并上传. </p>
			<p><input name="conffile" type="file" class="formfld" id="conffile" size="40"></p>
			<p><input name="Submit" type="submit" class="formbtn" id="restore" value="上传配置"></p>
			<p><strong><span class="red">注意:</span></strong><br />上传配置后, 设备需要重启后才能生效.<br /></p>
		</td>
	</tr>
</table>
</form>
<?php
	include("fend.inc");
?>
</body>
</html>

