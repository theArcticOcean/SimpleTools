<?php
$username = $_GET['username'];
$time = date("Y-m-d"); 						// get the time.
//var_dump($time);

$title = $_POST['title'];
$context = nl2br($_POST["context"]);   // change \n to <br>
$conn = mysql_connect("localhost","root","19941212") or die("无法连接数据库，请重试");
mysql_select_db("GIS") or die(mysql_error());

$sql = "INSERT INTO text VALUES(\"$username\",\"$title\",\"$context\",\"$time\");";
//echo $sql;
mysql_query($sql);
if(mysql_affected_rows() < 0){
	die('Could not update: ' . mysql_error());
}
else {
?>
	<script>
	alert("新建成功. \n马上返回文章列表");
	var url = window.location.href;  
	var folder = url.substring(0,url.lastIndexOf('/'));
	location.href = folder+"/login.php?username="+"<?php echo $username; ?>";
	</script>
<?php
}
mysql_close();
?>
