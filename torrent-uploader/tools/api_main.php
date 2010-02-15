<?
require_once("include/bittorrent.php");

dbconn(false);

loggedinorreturn();
parked();


if (get_user_class() < UC_UPLOADER)
{
  header("HTTP/1.0 403 Forbidden");
  exit;
}

if ($_REQUEST['get'] == "category") 
{
$cats = genrelist();
foreach ($cats as $row)
	$s .= $row["id"].':'.htmlspecialchars($row["name"]).',';

echo substr($s,0,-1);
}
?>