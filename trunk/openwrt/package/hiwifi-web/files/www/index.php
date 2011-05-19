<?php
	include("head.inc");
?>
<body link="#0000CC" vlink="#0000CC" alink="#0000CC">
<script language="javascript" type="text/javascript">
<!--
	// remote scripting library
	// (c) copyright 2005 modernmethod, inc
	var sajax_debug_mode = false;
	var sajax_request_type = "POST";

	function sajax_debug(text) {
		if (sajax_debug_mode)
			alert("RSD: " + text)
	}
 	function sajax_init_object() {
		sajax_debug("sajax_init_object() called..")
		var A;
		try {
			A=new ActiveXObject("Msxml2.XMLHTTP");
		} catch (e) {
			try {
				A=new ActiveXObject("Microsoft.XMLHTTP");
			} catch (oc) {
				A=null;
			}
		}
		if(!A && typeof XMLHttpRequest != "undefined")
			A = new XMLHttpRequest();
		if (!A)
			sajax_debug("Could not create connection object.");
		return A;
	}

	function sajax_do_call(func_name, args) {
		var i, x, n;
		var uri;
		var post_data;

		uri = "sajax/index.sajax.php";
		if (sajax_request_type == "GET") {
			if (uri.indexOf("?") == -1)
				uri = uri + "?rs=" + escape(func_name);
			else
				uri = uri + "&rs=" + escape(func_name);
			for (i = 0; i < args.length-1; i++)
				uri = uri + "&rsargs[]=" + escape(args[i]);
			uri = uri + "&rsrnd=" + new Date().getTime();
			post_data = null;
		} else {
			post_data = "rs=" + escape(func_name);
			for (i = 0; i < args.length-1; i++)
				post_data = post_data + "&rsargs[]=" + escape(args[i]);
		}

		x = sajax_init_object();
		x.open(sajax_request_type, uri, true);
		if (sajax_request_type == "POST") {
			x.setRequestHeader("Method", "POST " + uri + " HTTP/1.1");
			x.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
		}
		x.onreadystatechange = function() {
			if (x.readyState != 4)
				return;
			sajax_debug("received " + x.responseText);
				var status;
			var data;
			status = x.responseText.charAt(0);
			data = x.responseText.substring(2);
			if (status == "-")
				alert("Error: " + data);
			else
				args[args.length-1](data);
		}
		x.send(post_data);
		sajax_debug(func_name + " uri = " + uri + "/post = " + post_data);
		sajax_debug(func_name + " waiting..");
		delete x;
	}
	//-->
	// wrapper for get_stats
	function x_get_stats() {
		sajax_do_call("get_stats",
			x_get_stats.arguments);
	}

</script>
<script language="javascript">
var ajaxStarted = false;
</script>
<?php
	include("fbegin.inc");
?>
<p class="pgtitle">系统概览</p>

<div id="niftyOutter">
<form action="index.php" method="post">
<table bgcolor="#990000" width="100%" border="0" cellspacing="0" cellpadding="0">
	<tbody>
		<tr>
			<td colspan="2" class="listtopic">系统信息</td>
		</tr>
		<tr>
			<td width="25%" class="vncellt">系统名</td>
			<td width="75%" class="listr">point8.mgmt.HiWiFi.net</td>
		</tr>
		<tr>
			<td width="25%" valign="top" class="vncellt">软件版本</td>
			<td width="75%" class="listr">
				<strong>1.0.1-RELEASE</strong>
				<br />
				built on Sun Dec 6 23:21:36 EST 2011
			</td>
		</tr>
				<tr>
			<td width="25%" class="vncellt">硬件</td>
			<td width="75%" class="listr">Ubiquiti RouterStation Pro</td>
		</tr>
						<tr>
			<td width="25%" class="vncellt">运行时间</td>
			<td width="75%" class="listr"><input style="border: 0px solid white;" size="30" name="uptime" id="uptime" value="00:05" /></td>
		</tr>

		<tr>
			<td width="25%" class="vncellt">CPU利用率</td>
			<td width="75%" class="listr">
				<img src="themes/nervecenter/images/misc/bar_left.gif" height="15" width="4" border="0" align="middle" alt="left bar" /><img src="themes/nervecenter/images/misc/bar_blue.gif" height="15" name="cpuwidtha" id="cpuwidtha" width="0" border="0" align="middle" alt="red bar" /><img src="themes/nervecenter/images/misc/bar_gray.gif" height="15" name="cpuwidthb" id="cpuwidthb" width="100" border="0" align="middle" alt="gray bar" /><img src="themes/nervecenter/images/misc/bar_right.gif" height="15" width="5" border="0" align="middle" alt="right bar" />
				&nbsp;
				<input style="border: 0px solid white;" size="30" name="cpumeter" id="cpumeter" value="(Updating in 5 seconds)" />
			</td>
		</tr>
		<tr>
			<td width="25%" class="vncellt">内存利用率</td>
			<td width="75%" class="listr">
								<img src="themes/nervecenter/images/misc/bar_left.gif" height="15" width="4" border="0" align="middle" alt="left bar" /><img src="themes/nervecenter/images/misc/bar_blue.gif" height="15" name="memwidtha" id="memwidtha" width="36" border="0" align="middle" alt="red bar" /><img src="themes/nervecenter/images/misc/bar_gray.gif" height="15" name="memwidthb" id="memwidthb" width="64" border="0" align="middle" alt="gray bar" /><img src="themes/nervecenter/images/misc/bar_right.gif" height="15" width="5" border="0" align="middle" alt="right bar" />
				&nbsp;
				<input style="border: 0px solid white;" size="30" name="memusagemeter" id="memusagemeter" value="36%" />
			</td>
		</tr>
		<tr>
			<td width="25%" class="vncellt">SWAP交换分区利用率</td>
			<td width="75%" class="listr">
								<img src="themes/nervecenter/images/misc/bar_left.gif" height="15" width="4" border="0" align="middle" alt="left bar" /><img src="themes/nervecenter/images/misc/bar_blue.gif" height="15" width="0" border="0" align="middle" alt="red bar" /><img src="themes/nervecenter/images/misc/bar_gray.gif" height="15" width="100" border="0" align="middle" alt="gray bar" /><img src="themes/nervecenter/images/misc/bar_right.gif" height="15" width="5" border="0" align="middle" alt="right bar" />
				&nbsp;
				<input style="border: 0px solid white;" size="30" name="swapusagemeter" id="swapusagemeter" value="0%" />
			</td>
		</tr>
				<tr>
			<td width="25%" class="vncellt">存储利用率</td>
			<td width="75%" class="listr">
								<img src="themes/nervecenter/images/misc/bar_left.gif" height="15" width="4" border="0" align="middle" alt="left bar" /><img src="themes/nervecenter/images/misc/bar_blue.gif" height="15" width="2" border="0" align="middle" alt="red bar" /><img src="themes/nervecenter/images/misc/bar_gray.gif" height="15" width="98" border="0" align="middle" alt="gray bar" /><img src="themes/nervecenter/images/misc/bar_right.gif" height="15" width="5" border="0" align="middle" alt="right bar" />
				&nbsp;
				<input style="border: 0px solid white;" size="30" name="diskusagemeter" id="diskusagemeter" value="2%" />
			</td>
		</tr>
	</tbody>
</table>
</form>
</div>
<?php
	include("fend.inc");
?>
<script type="text/javascript">
	NiftyCheck();
	Rounded("div#nifty","top","#FFF","#EEEEEE","smooth");
</script>
</body>
</html>
