<?php
	if($_POST) {
		if ($_FILES["firmware"]["error"] > 0) {
			echo "Error: " . $_FILES["firmware"]["error"] . "<br />";
		}
		else
		{
			echo "Upload: " . $_FILES["firmware"]["name"] . "<br />";
			echo "Type: " . $_FILES["firmware"]["type"] . "<br />";
			echo "Size: " . ($_FILES["firmware"]["size"] / 1024) . " Kb<br />";
			echo "Stored in: " . $_FILES["firmware"]["tmp_name"];
		  
			if (file_exists("/tmp/" . $_FILES["firmware"]["name"])) {
				echo $_FILES["firmware"]["name"] . " already exists. ";
			}
			else {
				move_uploaded_file($_FILES["firmware"]["tmp_name"],
									"/tmp/" . $_FILES["firmware"]["name"]);
				echo "Stored in: " . "/tmp/" . $_FILES["firmware"]["name"];
			}
		}
	}

	include("head.inc");
?>
<body link="#0000CC" vlink="#0000CC" alink="#0000CC">
<?php
	include("fbegin.inc");
?>

<p class="pgtitle">系统: 固件升级:</p>
<table width="100%" border="0" cellpadding="6" cellspacing="0">
	<tr>
		<td colspan="2" class="listtopic">固件升级</td>
	</tr>
	<tr>
		<td width="22%" valign="baseline" class="vncell">本地升级</td>
		<td width="78%" class="vtable">
			<form action="system_firmware.php" method="post" enctype="multipart/form-data">
				<input type="file" name="firmware" style="width:300px">
				<p><input type="submit" name="Submit" class="formbtn" value="上传固件"></p>
				<p>选择存储在本地的固件镜像文件, 并点击&quot;上传固件&quot按钮;</p>
			</form>
		</td>
	</tr>
	
	<tr>
		<td width="22%" valign="baseline" class="vncell">网络升级</td>
		<td width="78%" class="vtable">
			
		</td>
	</tr>
	<tr>
		<td colspan="2">
			<span class="vexpl">
			<span class="red"><strong>注意:<br></strong></span>
			<span>升级过程中, 不要进行其它配置操作. 并保持一直停留在本页面, 直到提示升级成功.</span><p>
			<span><a href="http://update.hiwifi.net/">从网络上检查是否存在新固件</a></span></p>
		</td>
	</tr>
</table>
<?php
	include("fend.inc");
?>
</body>
</html>
