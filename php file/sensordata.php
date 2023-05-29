<?php
//Ambil data dari URL
$dataHumidity = $_GET['humidity'];
$dataSuhu = $_GET['suhu'];
echo "Data dari url :" . $dataHumidity . $dataSuhu;
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "esp";

// Create connection
$conn = mysqli_connect(
    $servername,
    $username,
    $password,
    $dbname
);
// Check connection
if (!$conn) {
    die("Koneksi gagal: " . mysqli_connect_error());
}

$sql = "INSERT INTO datasensor (tglData, suhu, kelembapan) 
 VALUES ( NOW(), $dataSuhu, $dataHumidity);";

mysqli_query($conn, $sql);
mysqli_close($conn);
