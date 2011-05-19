<?php
	include("head.inc");
?>

<body link="#0000CC" vlink="#0000CC" alink="#0000CC">
<?php
	include("fbegin.inc");
?>
<p class="pgtitle">状态: 无线用户流量监测</p>
<form name="form1" action="status_graph.php" method="get" style="padding-bottom: 10px; margin-bottom: 14px; border-bottom: 1px solid #999999">
用户MAC地址: 00:12:23:34:45:56&nbsp;&nbsp;<input type="button" value="返回" onclick="history.back(-1)"/>
</form>
<div align="center">
	<object data="graph.xml" type="image/svg+xml" width="550" height="275">
		<param name="src" value="graph.xml" />
		你的浏览器不支持SVG，你需要使用Firefox(或Google Chorme, IE8以上)或者下载Adobe SVG插件
	</object>
</div>


<?php
	include("fend.inc");
?>
</body>
</html>
