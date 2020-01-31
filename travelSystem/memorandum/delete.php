<?php
$username = $_GET['username'];
$title = $_GET['title'];

$conn = mysql_connect("localhost","root","19941212") or die("无法连接数据库，请重试");
mysql_select_db("GIS") or die(mysql_error());
$query = "delete FROM `text` WHERE email=\"$username\" and title=\"$title\""; 
mysql_query($query);
if(mysql_affected_rows() <= 0){
		die('Could not delete: ' . mysql_error());
}
else 
{	
		printf("Records affected: %d\n", mysql_affected_rows());
		mysql_close($link_identifier = null);
?>
	 <script> 	
	   alert("删除成功!");
		var url = window.location.href;  
		var folder = url.substring(0,url.lastIndexOf('/'));
   	//location.href = folder+"/login.php";
   	location.href=folder+"/login.php?username="+"<?php echo $username ?>";
    </script>
<?php		
}
mysql_close();
?>