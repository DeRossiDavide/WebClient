<?php
header('Content-Type: application/json; charset=utf-8');
// Otteniamo l'indirizzo ip del client
$ip = $_SERVER['REMOTE_ADDR'];
$temperature ='0.0';
$umidity = '0.0';
// Ricavo il tempo corrente ma non viene usato
$current_time = time();
$dateTimeField = date("Y-m-d H:i:s", $current_time);
// leggiamo le variabili dal comando POST inviato dal client
if (isset($_POST['ftemp'])) {
    $temperature = $_POST['ftemp'];
}
if (isset($_POST['fpress'])) {
    $umidity = $_POST['fumidity'];
}
if (isset($_POST['ftime'])) {
    $dateTimeField = $_POST['ftime'];
}
// Aggiungiamo il risultato nel file temperature.csv
$filename ="log.csv";
$f = fopen($filename, 'a'); // Aperto in append
// In caso di errore
if ($f === false) {
	die('Error opening the file ' . $filename);
}
// creo la riga da inserire: un array con i dati e poi la funzione fputcsv
$row = [];
array_push($row, $ip , $dateTimeField, strval($temperature)."°C",strval($umidity)."%");
fputcsv($f, $row);
fclose($f);
// confermo al client l'avventua registrazione

$data = "Ok";
echo json_encode($data);
?>