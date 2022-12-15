<?php
    $current_time = time();
    header('Content-Type: application/json; charset=utf-8');
    $data = date("Y-m-d H:i:s", $current_time);
    echo json_encode($data);
?>