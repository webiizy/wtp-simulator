<?php
	include("head.inc");
?>
<body link="#0000CC" vlink="#0000CC" alink="#0000CC">
<?php
	include("fbegin.inc");
?>
<p class="pgtitle">诊断: 出厂配置</p>
<?php
	if ($_POST["reboot"] == "true") {
?>
设备将在10秒恢复到出厂配置
<?php
	}
	else {
?>
<form action="diag_defaults.php" method="post">
<input type="hidden" name="reboot" value="true">
	<p><strong>如果你点击 &quot;确定&quot;, 此设备将会: 
	      
		<ul>
		  <li>所以配置将会恢复到出厂配置</li>
		  <li>设备模式将恢复为网桥模式</li>
		  <li>网桥管理IP地址将会重置为192.168.1.1</li>
		  <li>WEBGUI用户名将会重置为'admin', 密码重置为admin</li>
		</ul>
        你确认执行此操作吗?</strong></p>
        <p>
          <input name="Submit" type="submit" class="formbtn" value=" 确定 ">
          <input type="button" class="formbtn" value=" 取消 " onclick="history.back(-1)">
        </p>
</form>
<?php
	}
	include("fend.inc");
?>
</body>
</html>
