<?php
// Fichier : index.php

$filePath = "temperature.txt";

// Partie pour recevoir et stocker les données POST
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $temperature = isset($_POST['temp']) ? $_POST['temp'] : 'Non spécifiée';
    file_put_contents($filePath, $temperature); // Stocke la température dans un fichier
    echo "Température reçue : " . $temperature;
} else {
    // Partie pour afficher la dernière température stockée
    if (file_exists($filePath)) {
        $lastTemperature = file_get_contents($filePath);
        echo "Dernière température reçue : " . $lastTemperature;
    } else {
        echo "Aucune température enregistrée.";
    }
}


?>

<html>

<body>
    <form action="index.php" method="post">
        <label for="temp">Température :</label><br>
        <input type="text" id="temp" name="temp" value=""><br><br>
        <input type="submit" value="Envoyer">
    </form>
</body>
</html>