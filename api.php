<?php
// api.php
header('Content-Type: application/json');

$host = 'louetootest.mysql.db'; // ou l'adresse de votre serveur MySQL
$db   = 'louetootest'; // le nom de votre base de données
$user = 'louetootest'; // votre nom d'utilisateur MySQL
$pass = 'Caramel2000'; // votre mot de passe MySQL
$charset = 'utf8mb4';

$dsn = "mysql:host=$host;dbname=$db;charset=$charset";
$options = [
    PDO::ATTR_ERRMODE            => PDO::ERRMODE_EXCEPTION,
    PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
    PDO::ATTR_EMULATE_PREPARES   => false,
];

$pdo = null;
$connectionStatus = 'Not Connected';

try {
    $pdo = new PDO($dsn, $user, $pass, $options);
    $connectionStatus = 'Connected';
} catch (\PDOException $e) {
    $response = [
        'status' => 'error',
        'message' => 'Échec de la connexion à la base de données: ' . $e->getMessage()
    ];
    echo json_encode($response);
    exit; // Stoppe l'exécution du script en cas d'échec de la connexion
}

if (isset($_GET['time'])) {
    $time = $_GET['time'];

    // Préparation de la requête pour insérer les données
    $stmt = $pdo->prepare("INSERT INTO time_records (time_string) VALUES (:time)");
    $stmt->execute(['time' => $time]);

    $response = [
        'status' => 'success',
        'receivedTime' => $time,
        'message' => 'Heure reçue et enregistrée avec succès.'
    ];
} else {
    $response = [
        'status' => 'error',
        'message' => 'Aucune heure spécifiée.'
    ];
}

echo json_encode($response);
