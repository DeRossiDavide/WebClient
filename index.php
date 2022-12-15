<?php
    $current_time = time();
?>
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Benvenuto</title>
</head>
<body>
    <h1>Segnala una temperatura</h1>
    <p>
        Questo è un documento di test, per verificare lo script
    </p>
    <p>
    <?=date('Y-m-d H:i:s', $current_time) ?>
    </p>
    <p>
        <form method="POST" action="sendtempumidity.php">
            <label for="ftemp">Temperature:</label><br>
            <input type="text" id="ftemp" name="ftemp" value="0.0"><br>
            <label for="fumidity">Umidità (%):</label><br>
            <input type="text" id="fumidity" name="fumidity" value="0.0"><br>
            <input type="hidden" id="ftime" name="ftime" value="<?=date('Y-m-d H:i:s', $current_time) ?>"><br><br>
            <input type="submit" value="Invia">

        </form>
    </p>
</body>
</html>