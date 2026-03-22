# 🔐 UART Eavesdropping & AES Encryption — Arduino Demo

### Démonstration d'écoute UART & Chiffrement AES — Arduino

-----

## 🇫🇷 Français

### Présentation

Ce projet démontre une vulnérabilité de sécurité au niveau matériel dans les systèmes embarqués : **la communication UART non chiffrée** peut être interceptée par n'importe quel nœud connecté au bus série. Le projet implémente ensuite le **chiffrement AES-128** comme contre-mesure, illustrant le contraste avant/après en temps réel.

Ce projet s'inscrit dans un portfolio plus large dédié à la **cybersécurité automobile**, en référence aux normes **ISO 21434** et **UN R155** pour la sécurité des systèmes embarqués.

### Concept de sécurité

Dans les systèmes embarqués, l'UART (Universal Asynchronous Receiver-Transmitter) est l'un des protocoles de communication les plus utilisés. Par défaut, l'UART transmet les données en **clair** — ce qui signifie que tout appareil physiquement connecté au bus peut lire les données sans authentification ni chiffrement.

Cette vulnérabilité est directement analogue à celles que l'on retrouve dans les réseaux d'ECU automobiles, les appareils IoT et les systèmes de contrôle industriels.

**Attaque démontrée :** Écoute passive du bus UART  
**Défense implémentée :** Chiffrement symétrique AES-128-CBC avec IV aléatoire transmis en en-tête de paquet

### Matériel

|Composant              |Rôle                    |Quantité|
|-----------------------|------------------------|--------|
|Arduino UNO R3 (ELEGOO)|Émetteur                |1       |
|Arduino UNO R3 (ELEGOO)|Récepteur + moniteur IDS|1       |
|Câbles Dupont (M-M)    |Câblage bus UART        |3       |

### Câblage

```
Arduino #1 (Émetteur)       Arduino #2 (Récepteur)
       Pin 11 (TX)  ───►  Pin 10 (RX)
       Pin 10 (RX)  ◄───  Pin 11 (TX)
          GND       ────     GND
```

> **Pourquoi les broches 10/11 et non TX/RX (0/1) ?**  
> Sur l'Arduino Uno, les broches 0 (RX) et 1 (TX) sont partagées avec la connexion USB. Les utiliser pour la communication inter-Arduino provoque des conflits lors du téléversement (`stk500_getsync` error) et mélange les données de débogage avec les données chiffrées dans le moniteur série. En utilisant `SoftwareSerial` sur les broches 10/11, on sépare proprement les deux canaux : les broches 0/1 restent dédiées au débogage via USB, et les broches 10/11 gèrent exclusivement la communication UART chiffrée entre les deux Arduino.

### Fonctionnement

**Phase 1 — Texte en clair (vulnérable)**  
L'Arduino #1 envoie le message `"HELLO"` via UART chaque seconde. L'Arduino #2 le reçoit et l'affiche en clair. Tout appareil connecté au bus peut lire le message.

**Phase 2 — Chiffré AES-128 CBC avec IV aléatoire (sécurisé)**  
Avant chaque transmission, l'Arduino #1 génère un **IV (vecteur d'initialisation) aléatoire** de 16 octets. Cet IV est envoyé en **en-tête de paquet**, suivi du message chiffré. L'Arduino #2 extrait l'IV de l'en-tête, puis déchiffre le payload avec la clé partagée. Un attaquant ne voit que des octets hexadécimaux différents à chaque transmission, même pour un message identique.

```
Structure du paquet transmis :
[ IV (16 bytes) | Ciphertext (16 bytes) ]
```

### Bibliothèques utilisées

- [AESLib by Matej Sychra](https://github.com/suculent/thinx-aes-lib) — Chiffrement AES-128 pour Arduino
- `SoftwareSerial` (built-in) — UART logiciel sur broches numériques arbitraires

### Résultats

|État       |Données sur le bus               |Lisible par un attaquant ?|
|-----------|---------------------------------|--------------------------|
|Texte clair|`HELLO`                          |✅ Oui                     |
|Chiffré    |`IV: A3 F2 ... \| ENC: 9B 4C ...`|❌ Non (IV différent à chaque fois)|

### Pertinence par rapport aux normes industrielles

- **ISO 21434** — Ingénierie de la cybersécurité pour les véhicules routiers : ce projet traite la menace d'écoute physique du bus au niveau matériel.
- **UN R155** — Exige des constructeurs qu'ils identifient et atténuent les cybermenaces dans les systèmes de communication des véhicules.
- **IEC 62443** — Sécurité des communications industrielles : la même contre-mesure AES s'applique aux systèmes SCADA et aux systèmes embarqués industriels.

### Compétences démontrées

- Programmation C++ embarqué (PlatformIO + Arduino framework)
- Protocole de communication matérielle : UART / SoftwareSerial
- Cryptographie symétrique : AES-128-CBC avec IV aléatoire par message
- Séparation des canaux de communication (debug vs. données chiffrées)
- Modélisation des menaces de sécurité : identification de la surface d'attaque
- Concepts de sécurité des systèmes embarqués

-----

## 🇬🇧 English

### Overview

This project demonstrates a hardware-layer security vulnerability in embedded systems: **unencrypted UART communication** can be intercepted by any node on the same serial bus. The project then implements **AES-128 encryption** as a countermeasure, showing the before/after contrast in real-time.

This project is part of a broader **Automotive Cybersecurity** portfolio, referencing **ISO 21434** and **UN R155** standards for embedded system security.

### Security Concept

In embedded systems, UART (Universal Asynchronous Receiver-Transmitter) is one of the most commonly used communication protocols. However, by default, UART transmits data in **plaintext** — meaning any device physically connected to the bus can read the data without authentication or encryption.

This is directly analogous to vulnerabilities found in automotive ECU networks, IoT devices, and industrial control systems.

**Attack demonstrated:** Passive eavesdropping on UART bus  
**Defense implemented:** AES-128-CBC symmetric encryption with a random IV transmitted as a packet header

### Hardware

|Component              |Role                  |Quantity|
|-----------------------|----------------------|--------|
|Arduino UNO R3 (ELEGOO)|Sender (transmitter)  |1       |
|Arduino UNO R3 (ELEGOO)|Receiver + IDS monitor|1       |
|Jumper wires (M-M)     |UART bus wiring       |3       |

### Wiring

```
Arduino #1 (Sender)         Arduino #2 (Receiver)
      Pin 11 (TX)  ───►  Pin 10 (RX)
      Pin 10 (RX)  ◄───  Pin 11 (TX)
         GND       ────     GND
```

> **Why pins 10/11 instead of the hardware TX/RX (pins 0/1)?**  
> On the Arduino Uno, pins 0 (RX) and 1 (TX) are shared with the USB interface. Using them for Arduino-to-Arduino communication causes upload failures (`stk500_getsync` error) and mixes debug output with encrypted data in the serial monitor. By using `SoftwareSerial` on pins 10/11, both channels are cleanly separated: pins 0/1 remain dedicated to USB debug output, while pins 10/11 handle the encrypted UART communication exclusively.

### How It Works

**Phase 1 — Plaintext (Vulnerable)**  
Arduino #1 sends the message `"HELLO"` over UART every second. Arduino #2 receives and displays it in plaintext. Any device connected to the bus can read the message.

**Phase 2 — AES-128 CBC with Random IV (Secure)**  
Before each transmission, Arduino #1 generates a fresh random **IV (Initialization Vector)** of 16 bytes. This IV is sent as a **packet header**, immediately followed by the encrypted payload. Arduino #2 extracts the IV from the header, then decrypts the payload using the shared key. An eavesdropper only sees different hex bytes on every transmission — even for the same plaintext message.

```
Packet structure:
[ IV (16 bytes) | Ciphertext (16 bytes) ]
```

### Libraries Used

- [AESLib by Matej Sychra](https://github.com/suculent/thinx-aes-lib) — AES-128 encryption for Arduino
- `SoftwareSerial` (built-in) — Software UART on arbitrary digital pins

### Results

|State    |Data on bus                      |Readable by attacker?             |
|---------|---------------------------------|----------------------------------|
|Plaintext|`HELLO`                          |✅ Yes                             |
|Encrypted|`IV: A3 F2 ... \| ENC: 9B 4C ...`|❌ No (IV changes every transmission)|

### Relevance to Industry Standards

- **ISO 21434** — Cybersecurity engineering for road vehicles: this project addresses the threat of physical bus eavesdropping at the hardware layer.
- **UN R155** — Requires OEMs to identify and mitigate cyber threats in vehicle communication systems.
- **IEC 62443** — Industrial communication security: the same AES countermeasure applies to SCADA and industrial embedded systems.

### Skills Demonstrated

- Embedded C++ programming (PlatformIO + Arduino framework)
- Hardware communication protocol: UART / SoftwareSerial
- Symmetric cryptography: AES-128-CBC with per-message random IV
- Communication channel separation (debug vs. encrypted data)
- Security threat modeling: attack surface identification
- Embedded system security concepts

-----

## 📁 Repository Structure

```
📦 uart-aes-security
 ┣ 📂 sender
 ┃ ┣ 📂 src
 ┃ ┃ ┗ 📜 main.cpp          # AES-128 CBC sender with random IV
 ┃ ┗ 📜 platformio.ini
 ┣ 📂 receiver
 ┃ ┣ 📂 src
 ┃ ┃ ┗ 📜 main.cpp          # AES-128 CBC receiver with IV extraction
 ┃ ┗ 📜 platformio.ini
 ┣ 📂 docs
 ┃ ┣ 📂 imges
 ┃ ┣ 📂 videos
 ┃ ┣ 📜 Arduino_AES_TIL.md
 ┃ ┗ 📜 UART AES Security.pdf
 ┗ 📜 README.md
```

-----

## 🔗 Related Projects

> 🚧 **Coming soon**  
> **CAN Bus Intrusion Detection System** — Arduino + MCP2515  
> Simulating ECU spoofing, replay attacks, and frame injection on a CAN bus network.  
> Reference: ISO 21434 · UN R155 · Automotive Cybersecurity

-----

*Project developed as part of an embedded systems security portfolio targeting positions in automotive and defense cybersecurity.*

*Projet développé dans le cadre d'un portfolio de sécurité des systèmes embarqués, orienté vers des postes en cybersécurité automobile et défense.*
