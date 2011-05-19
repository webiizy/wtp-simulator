<?php
	include("head.inc");
?>
<body link="#0000CC" vlink="#0000CC" alink="#0000CC">
<?php
	include("fbegin.inc");
?>
<p class="pgtitle">状态: 无线用户</p>

<table width="100%" cellspacing="0" cellpadding="6" border="0">
<tr><td class="listbg" colspan="9"><font color="white"><strong>当前连接到本设备的无线用户</strong></font></td></tr>
<tr>
<td class="listhdrr">MAC地址</td>
<td class="listhdrr">IP地址</td>
<td class="listhdrr">连接速率</td>
<td class="listhdrr">进/出 字节</td>
<td class="listhdrr">进/出 包数</td>
<td class="listhdrr">进/出 错误数</td>
<td class="listhdrr">连接时长</td>
<td class="listhdrr">无线接口<select><option value="0">所有</option><option value="wifi0">wifi0</option><option value="wifi1">wifi1</option><option value="wifi2">wifi2</option></select></td>
<td class="listhdrr"></td>
</tr>
<tr>
<td class="listr">00:11:22:33:44:55</td>
<td class="listr">192.168.154.2</td>
<td class="listr">300M</td>
<td class="listr">13241234/1324</td>
<td class="listr">30/30</td>
<td class="listr">0/0</td>
<td class="listr">00:10:20</td>
<td class="listr">wifi0</td>
<td class="listr"><a href="status_user_graph.php">监测</a></td>
</tr>
</table>

<?php
	include("fend.inc");
?>
</body>
</html>
