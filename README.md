# 🔐 UART Eavesdropping & AES Encryption — Arduino Demo

### Démonstration d’écoute UART & Chiffrement AES — Arduino

-----

## 🇫🇷 Français

### Présentation

Ce projet démontre une vulnérabilité de sécurité au niveau matériel dans les systèmes embarqués : **la communication UART non chiffrée** peut être interceptée par n’importe quel nœud connecté au bus série. Le projet implémente ensuite le **chiffrement AES-128** comme contre-mesure, illustrant le contraste avant/après en temps réel.

Ce projet s’inscrit dans un portfolio plus large dédié à la **cybersécurité automobile**, en référence aux normes **ISO 21434** et **UN R155** pour la sécurité des systèmes embarqués.

### Concept de sécurité

Dans les systèmes embarqués, l’UART (Universal Asynchronous Receiver-Transmitter) est l’un des protocoles de communication les plus utilisés. Par défaut, l’UART transmet les données en **clair** — ce qui signifie que tout appareil physiquement connecté au bus peut lire les données sans authentification ni chiffrement.

Cette vulnérabilité est directement analogue à celles que l’on retrouve dans les réseaux d’ECU automobiles, les appareils IoT et les systèmes de contrôle industriels.

**Attaque démontrée :** Écoute passive du bus UART  
**Défense implémentée :** Chiffrement symétrique AES-128-CBC avec clé partagée

### Matériel

|Composant              |Rôle                    |Quantité|
|-----------------------|------------------------|--------|
|Arduino UNO R3 (ELEGOO)|Émetteur                |1       |
|Arduino UNO R3 (ELEGOO)|Récepteur + moniteur IDS|1       |
|Câbles Dupont (M-M)    |Câblage bus UART        |3       |

### Câblage

```
Arduino #1 (Émetteur)     Arduino #2 (Récepteur)
        TX (Pin 1)  ───►  RX (Pin 0)
        RX (Pin 0)  ◄───  TX (Pin 1)
           GND      ────   GND
```

### Fonctionnement

**Phase 1 — Texte en clair (vulnérable)**  
L’Arduino #1 envoie le message `"HELLO"` via UART chaque seconde. L’Arduino #2 le reçoit et l’affiche en clair. Tout appareil connecté au bus peut lire le message.

**Phase 2 — Chiffré AES-128 (sécurisé)**  
Le même message est chiffré avec AES-128-CBC avant transmission. L’Arduino #2 reçoit le texte chiffré, le déchiffre avec la clé partagée et affiche le message original. Un attaquant ne voit que des octets hexadécimaux inintelligibles.

### Bibliothèques utilisées

- [AESLib by Matej Sychra](https://github.com/suculent/thinx-aes-lib) — Chiffrement AES-128 pour Arduino

### Résultats

|État       |Données sur le bus|Lisible par un attaquant ?|
|-----------|------------------|--------------------------|
|Texte clair|`HELLO`           |✅ Oui                     |
|Chiffré    |`A3 F2 01 7C ...` |❌ Non                     |

### Pertinence par rapport aux normes industrielles

- **ISO 21434** — Ingénierie de la cybersécurité pour les véhicules routiers : ce projet traite la menace d’écoute physique du bus au niveau matériel.
- **UN R155** — Exige des constructeurs qu’ils identifient et atténuent les cybermenaces dans les systèmes de communication des véhicules.
- **IEC 62443** — Sécurité des communications industrielles : la même contre-mesure AES s’applique aux systèmes SCADA et aux systèmes embarqués industriels.

### Compétences démontrées

- Programmation C++ embarqué (Arduino IDE)
- Protocole de communication matérielle : UART/Série
- Cryptographie symétrique : implémentation AES-128-CBC
- Modélisation des menaces de sécurité : identification de la surface d’attaque
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
**Defense implemented:** AES-128-CBC symmetric encryption with shared key

### Hardware

|Component              |Role                  |Quantity|
|-----------------------|----------------------|--------|
|Arduino UNO R3 (ELEGOO)|Sender (transmitter)  |1       |
|Arduino UNO R3 (ELEGOO)|Receiver + IDS monitor|1       |
|Jumper wires (M-M)     |UART bus wiring       |3       |

### Wiring

```
Arduino #1 (Sender)      Arduino #2 (Receiver)
        TX (Pin 1)  ───►  RX (Pin 0)
        RX (Pin 0)  ◄───  TX (Pin 1)
           GND      ────   GND
```

### How It Works

**Phase 1 — Plaintext (Vulnerable)**  
Arduino #1 sends the message `"HELLO"` over UART every second. Arduino #2 receives and displays it in plaintext. Any device connected to the bus can read the message.

**Phase 2 — AES-128 Encrypted (Secure)**  
The same message is encrypted using AES-128-CBC before transmission. Arduino #2 receives the ciphertext, decrypts it using the shared key, and displays the original message. An eavesdropper only sees unintelligible hex bytes.

### Libraries Used

- [AESLib by Matej Sychra](https://github.com/suculent/thinx-aes-lib) — AES-128 encryption for Arduino

### Results

|State    |Data on bus      |Readable by attacker?|
|---------|-----------------|---------------------|
|Plaintext|`HELLO`          |✅ Yes                |
|Encrypted|`A3 F2 01 7C ...`|❌ No                 |

### Relevance to Industry Standards

- **ISO 21434** — Cybersecurity engineering for road vehicles: this project addresses the threat of physical bus eavesdropping at the hardware layer.
- **UN R155** — Requires OEMs to identify and mitigate cyber threats in vehicle communication systems.
- **IEC 62443** — Industrial communication security: the same AES countermeasure applies to SCADA and industrial embedded systems.

### Skills Demonstrated

- Embedded C++ programming (Arduino IDE)
- Hardware communication protocol: UART/Serial
- Symmetric cryptography: AES-128-CBC implementation
- Security threat modeling: attack surface identification
- Embedded system security concepts

-----
## 📁 Repository Structure / Structure du dépôt

```
📦 uart-aes-security
 ┣ 📂 src
 ┃ ┣ 📜 sender_plaintext.ino       # Phase 1 - Plaintext sender
 ┃ ┣ 📜 receiver_plaintext.ino     # Phase 1 - Plaintext receiver
 ┃ ┣ 📜 sender_encrypted.ino       # Phase 2 - AES encrypted sender
 ┃ ┗ 📜 receiver_encrypted.ino     # Phase 2 - AES encrypted receiver
 ┣ 📂 docs
 ┃ ┗ 📜 wiring_diagram.html        # Interactive wiring diagram
 ┗ 📜 README.md
```

-----

## 🔗 Related Projects / Projets connexes

> 🚧 **Coming soon / Bientôt disponible**  
> **CAN Bus Intrusion Detection System** — Arduino + MCP2515  
> Simulating ECU spoofing, replay attacks, and frame injection on a CAN bus network.  
> Référence : ISO 21434 · UN R155 · Automotive Cybersecurity

-----

*Project developed as part of an embedded systems security portfolio targeting positions in automotive and defense cybersecurity.*

*Projet développé dans le cadre d’un portfolio de sécurité des systèmes embarqués, orienté vers des postes en cybersécurité automobile et défense.*
