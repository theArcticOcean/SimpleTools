<?php
$username = $_GET['username'];
$title = $_GET['title'];

$conn = mysql_connect("localhost","root","19941212") or die("无法连接数据库，请重试");
mysql_select_db("GIS") or die(mysql_error());
$query = "select * from  text WHERE email=\"$username\" and title=\"$title\""; 
$result = mysql_query($query);
$row = mysql_fetch_array($result);
mysql_close();
?>

<form action="editSave.php?username=<?php echo $username ?>&title=<?php echo $title ?>" method="POST">  
标题:  <input type="text" size=28 name="title" value="<?php echo $title ?>"> <br>  
时间:  <input type="text" size=28 name="time" readonly="readonly" value="<?php echo $row['time']; ?>"> <br>
内容:  <br>
<textarea name="context" cols="100" rows="15" ><?php echo $row['context']; ?></textarea><br>  
<input type="submit" name="submit" value="保存"> 